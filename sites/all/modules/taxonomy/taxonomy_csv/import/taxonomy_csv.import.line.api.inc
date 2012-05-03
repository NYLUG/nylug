<?php

/**
 * @file
 * Process import of a csv line, i.e. of a term or a list of terms.
 */

/**
 * Process the import of items.
 *
 * @param $line
 *   Array which contains items of a cleaned and checked csv line.
 * @param $options
 *   An associative array of import options:
 *   - import_format  : see _taxonomy_csv_values('import_format')
 *   - keep_order     : boolean. keep order of imported terms or not (default)
 *   - vocabulary     : vocabulary object where to import terms into
 *   - existing_items : see _taxonomy_csv_values('import_option')
 *   // Specific to relations import:
 *   - relations_create_subrelations: boolean.
 *   - relations_all_vocabularies   : boolean.
 * @param $previous_items
 *   (Optional) Cleaned and checked previous imported line names and tids array.
 *   Needed with some contents as one term array structure or Taxonomy manager.
 *   Specificities:
 *   - def_links:
 *       'name' and 'tid' arrays contain sub-arrays 'vocabulary' and 'term' with
 *       imported identifiant as key and name or tid/vid as value in order to
 *       allow duplicate names import and use of number identifiants.
 * @param $terms_count
 *   (Optional integer) Total of imported terms (duplicate included) is needed
 *   to set weight of terms and to keep order of items, if wished.
 *
 * @return Result array:
 *   'name' => array of imported terms names,
 *   'tid'  => array of imported terms tids,
 *   'msg'  => array of message codes,
 *   'terms_count' => number of imported terms.
 */
function taxonomy_csv_line_import($line, $options, $previous_items = array(), $terms_count = 0) {
  // Define default values.
  $result = array(
    'name' => array(),
    'tid'  => array(),
    'msg'  => array(),
    'terms_count' => $terms_count,
  );

  // Only count check because function variables are already checked.
  if (count($line)) {
    switch ($options['import_format']) {
      case TAXONOMY_CSV_FORMAT_ALONE_TERMS:
      case TAXONOMY_CSV_FORMAT_SYNONYMS:
      case TAXONOMY_CSV_FORMAT_DEFINITIONS:
      case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
      case TAXONOMY_CSV_FORMAT_WEIGHTS:
        $term = (object) array(
          'name'     => $line[0],
          'vid'      => $options['vocabulary']->vid,
          'format'   => $options['filter_format'],
          'language' => $options['language'],
          'vocabulary_machine_name' => $options['vocabulary']->machine_name,
        );
        // Weight is not set above in order to keep existing one if it exists.
        // It's replaced below with weights and definitions formats.
        ++$terms_count;
        if ($options['keep_order']) {
          $term->weight = $terms_count;
        }

        switch ($options['import_format']) {
          case TAXONOMY_CSV_FORMAT_SYNONYMS:
            $term->field_term_synonym = _taxonomy_csv_field_create_text(array_slice($line, 1), $options['language'], $options['filter_format_custom']);
            break;

          case TAXONOMY_CSV_FORMAT_DEFINITIONS:
            if (isset($line[1]) && $line[1]) {
              $term->weight = $line[1];
            }
            $term->description = _taxonomy_csv_set_line_break($line[2]);
            $term->field_term_synonym = _taxonomy_csv_field_create_text(array_slice($line, 3), $options['language'], $options['filter_format_custom']);
            break;

          case TAXONOMY_CSV_FORMAT_DESCRIPTIONS:
            $term->description = _taxonomy_csv_set_line_break($line[1]);
            break;

          case TAXONOMY_CSV_FORMAT_WEIGHTS:
            if (isset($line[1]) && $line[1]) {
              $term->weight = $line[1];
            }
            break;
        }
        // Import term then store result. No check because only one term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        $error = _taxonomy_csv_line_result($result, $current_result, $terms_count);
        break;

      case TAXONOMY_CSV_FORMAT_CUSTOM_FIELDS:
        $term = (object) array(
          'vid'      => $options['vocabulary']->vid,
          'format'   => $options['filter_format'],
          'language' => $options['language'],
          'vocabulary_machine_name' => $options['vocabulary']->machine_name,
        );
        // Weight is not set above in order to keep existing one if it exists.
        ++$terms_count;
        if ($options['keep_order']) {
          $term->weight = $terms_count;
        }

        // Import normal fields according custom format.
        foreach ($options['custom_format'] as $key => $field_name) {
          switch ($field_name) {
            case 'tid' :
            case 'name' :
            case 'format' :
            case 'language' :
            case 'weight' :
            case 'i18n_tsid' :
            case 'guid' :
              $term->{$field_name} = $line[$key];
              break;
            case 'description' :
              $term->description = _taxonomy_csv_set_line_break($line['description']);
              break;
            // Never used, because rejected during start check.
            // case 'vid' :
            // case 'vocabulary_machine_name' :
            // Others are processed with hook taxonomy_csv_taxonomy_term_presave.
            default:
              if (!isset($_SESSION['taxonomy_csv_import']['fields'][$field_name])) {
                $current_result['msg'] = 341; // Non existing field.
                break 2;
              }
          }
        }

        // Remember line (currently, a hook is used to import custom fields).
        $_SESSION['taxonomy_csv_import']['line'] = $line;

        // Import term then store result. No check because only one term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        $error = _taxonomy_csv_line_result($result, $current_result, $terms_count);
        break;

      case TAXONOMY_CSV_FORMAT_DEFINITION_LINKS:
        // 1. Keep previous imported vocabularies and terms.
        $result['name'] = $previous_items['name'];
        $result['tid']  = $previous_items['tid'];

        // 2. Define main term to be imported.
        $term = (object) array(
          'name'        => $line[0],
          'description' => _taxonomy_csv_set_line_break($line[3]),
          'format'      => $options['filter_format'],
          'language'    => $options['language'],
          'weight'      => $line[4],
          'parent'      => array(),
          'field_term_synonym' => _taxonomy_csv_field_create_text(array_slice($line, 9, $line[5]), $options['language'], $options['filter_format_custom']),
          'field_term_relation' => array(),
        );
        // Weight is not set above in order to keep existing one if it exists.
        ++$terms_count;
        if ($options['keep_order']) {
          $term->weight = $terms_count;
        }

        // 3. Prepare links. Zero character ids have been already removed.
        $parents_names  = array_slice($line, 9 + $line[5], $line[6]);
        $children_names = array_slice($line, 9 + $line[5] + $line[6], $line[7]);
        $related_names  = array_slice($line, 9 + $line[5] + $line[6] + $line[7], $line[8]);
        $related_vocs   = array_slice($line, 9 + $line[5] + $line[6] + $line[7] + $line[8], $line[8]);

        // 4. Prepare vocabularies.
        // Set default vocabulary if no vocabulary is used.
        if (!$line[2]) {
          $line[2] = 0;
        }

        // Add empty related vocabularies if they are fewer than related names.
        $related_vocs = array_pad($related_vocs, count($related_names), $line[2]);

        // If a related vocabulary is undefined, it's the main term one.
        foreach ($related_vocs as $key => $value) {
          if (!$value) {
            $related_vocs[$key] = $line[2];
          }
        }

        // Check if main and related vocabularies are already in memory.
        $vocabularies = $related_vocs;
        $vocabularies[] = $line[2];
        $vocabularies = array_unique($vocabularies);

        foreach ($vocabularies as $id) {
          // Empty vocabulary identifiant is saved too, so it can't be empty.
          if (!$id) {
            $id = $line[2];
          }

          // Vocabulary is unknown.
          if (!isset($result['name']['vocabulary'][$id])) {
            // If no vocabulary is defined, the destination option is used.
            if (!$id) {
              $name = _taxonomy_csv_import_vocabulary_prepare($options, FALSE);
              $vocabulary = (array) taxonomy_csv_vocabulary_load_name($name);
              if ($options['vocabulary_target'] != 'existing') {
                $result['msg'][] = 610; // Info new vocabulary.
              }
            }

            // If a vocabulary is defined, the destination option is not used:
            // if vocabulary exists, it is used always, else it is autocreated.
            else {
              // Get the vid from the id if it's a name.
              $vid = (is_numeric($id) && ctype_digit($id)) ?
                // $id is a vocabulary id.
                $id :
                // $id is a vocabulary name.
                taxonomy_csv_vocabulary_get_id($id);

              // Check if vocabulary exists, then use it or create a new one.
              $vocabulary = (array) taxonomy_vocabulary_load($vid);

              if (!isset($vocabulary['vid'])) {
                $vocabulary = (array) taxonomy_csv_thesaurus_create($id);
                $result['msg'][] = 610; // Info new vocabulary.

                // Check external formats. Use it only if it works.
                $funcname = "_taxonomy_csv_import_vocabulary_prepare_{$options['import_format']}";
                if (taxonomy_csv_format_check($options['import_format'], $funcname)) {
                  $funcname($vocabulary);
                }
              }
            }
            // Remember imported vocabulary.
            $result['name']['vocabulary'][$id] = $vocabulary['name'];
            $result['tid']['vocabulary'][$id]  = $vocabulary['vid'];
          }
        }
        // Update main term with vocabulary id.
        $term->vid = $vid = $result['tid']['vocabulary'][$line[2]];

        // 5. Import each parent and check result.
        $tids = array();
        foreach ($parents_names as $key => $id) {
          // Check if term is already imported.
          if (!isset($result['name']['term'][$id])) {
            $unsaved_term = (object) array(
              'name' => $id,
              'vid'  => $vid,
              'format'   => $options['filter_format'],
              'language' => $options['language'],
            );
            $current_result = taxonomy_csv_term_import($unsaved_term, $options['existing_items']);
            $result['name']['term'][$id] = $current_result['name'];
            $result['tid']['term'][$id]  = $current_result['tid'];
            $result['msg'] = array_merge($result['msg'], $current_result['msg']);
            if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
              break 2;
            }
          }
          $tids[] = $result['tid']['term'][$id];
        }
        // Update main term with parents ids.
        $term->parent = ($tids) ?
          array_combine($tids, $tids) :
          array(0);

        // 6. Import each related term and check result.
        $tids = array();
        foreach ($related_names as $key => $id) {
          // Check if term is already imported or not.
          if (isset($result['name']['term'][$id])) {
            // Check vocabulary: need update if it changes (by line approach).
            $temp_term = taxonomy_term_load($result['tid']['term'][$id]);
            $temp_vocabulary = (!$related_vocs[$key]) ?
                // There is no vocabulary identifiant, so use main term vid.
                $vid :
                // There is a vocabulary identifiant, so use it.
                $result['tid']['vocabulary'][$related_vocs[$key]];
            // Vocabulary change is unadvised if term has links, but possible.
            if ($temp_term->vid != $temp_vocabulary) {
              $unsaved_term = (object) array(
                'name' => $result['name']['term'][$id],
                'vid'  => $temp_vocabulary,
                'format'   => $options['filter_format'],
                'language' => $options['language'],
              );
              $current_result = taxonomy_csv_term_import($unsaved_term, $options['existing_items']);
              $result['name']['term'][$id] = $current_result['name'];
              $result['tid']['term'][$id]  = $current_result['tid'];
              $result['msg'] = array_merge($result['msg'], $current_result['msg']);
              if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
                break 2;
              }
              $result['msg'][] = 511; // Notice: Update not recommended.
            }
          }
          else {
            $unsaved_term = (object) array(
              'name' => $id,
              'vid'  => (!$related_vocs[$key]) ?
                  // There is no vocabulary identifiant, so use main term vid.
                  $vid :
                  // There is a vocabulary identifiant, so use it.
                  $result['tid']['vocabulary'][$related_vocs[$key]],
              'format'   => $options['filter_format'],
              'language' => $options['language'],
            );
            $current_result = taxonomy_csv_term_import($unsaved_term, $options['existing_items']);
            $result['name']['term'][$id] = $current_result['name'];
            $result['tid']['term'][$id]  = $current_result['tid'];
            $result['msg'] = array_merge($result['msg'], $current_result['msg']);
            if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
              break 2;
            }
          }
          $tids[] = $result['tid']['term'][$id];
        }
        // Update main term with related ids.
        $related_tids = $tids;
        $term->field_term_relation = _taxonomy_csv_field_create_taxonomy_term_reference($tids, $options['language']);

        // 7. Import main term and check result.
        // If main term has an identifiant, pre-import it with this identifiant
        // in order to get a specific tid in case of duplicate.
        if ($line[1] != '') {
          // If term is already imported, simply update it with tid.
          if (isset($result['tid']['term'][$line[1]])) {
            $term->tid = $result['tid']['term'][$line[1]];
          }
          // Pre-import is needed only when name and identifiant are different.
          elseif (drupal_strtolower($line[0]) != drupal_strtolower($line[1])) {
            $unsaved_term = (object) array(
              'name' => $line[1],
              'vid'  => $term->vid,
              'format'   => $term->format,
              'language' => $term->language,
            );
            $current_result = taxonomy_csv_term_import($unsaved_term, $options['existing_items']);
            $result['name']['term'][$line[1]] = $current_result['name'];
            $result['tid']['term'][$line[1]]  = $current_result['tid'];
            $result['msg'] = array_merge($result['msg'], $current_result['msg']);
            if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
              break;
            }
            $term->tid = $current_result['tid'];
          }
        }

        // Import main term.
        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        // Complete the term with the term id in case it's not been fulled.
        $term->tid = $current_result['tid'];
        // Save with name if identifiant was not set (else, it's already saved).
        if ($line[1] == '') {
          $result['name']['term'][$line[0]] = $current_result['name'];
          $result['tid']['term'][$line[0]]  = $current_result['tid'];
        }
        else {
          $result['name']['term'][$line[1]] = $current_result['name'];
          $result['tid']['term'][$line[1]]  = $current_result['tid'];
        }

        $result['msg'] = array_merge($result['msg'], $current_result['msg']);
        if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
          break;
        }

        // 8. Import each child with main term as parent and check result.
        $parent_tid = $current_result['tid'];
        $tids = array();
        foreach ($children_names as $key => $id) {
          // No check because parent is added even if term is already imported.
          $unsaved_term = (object) array(
            'name'     => $id,
            'vid'      => $vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'parent'   => array($parent_tid => $parent_tid),
          );
          // Update term with tid and true name if known.
          if (isset($result['name']['term'][$id])) {
            $unsaved_term->name = $result['name']['term'][$id];
            $unsaved_term->tid  = $result['tid']['term'][$id];
          }
          // Import term then store and check result.
          // Don't check tid == parent_tid because duplicates have been removed.
          $current_result = taxonomy_csv_term_import($unsaved_term, $options['existing_items']);
          $result['name']['term'][$id] = $current_result['name'];
          $result['tid']['term'][$id]  = $current_result['tid'];
          $result['msg'] = array_merge($result['msg'], $current_result['msg']);
          if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
            break 2;
          }
        }

        // 9. Set relations for related terms and check result. Unlike Drupal 6,
        // relation field is linked only in one way. So, an update is needed.
        foreach ($related_tids as $key => $tid) {
          $unsaved_term = (object) array(
            'tid'      => $tid,
            'name'     => $result['name']['term'][$related_names[$key]],
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'field_term_relation' => _taxonomy_csv_field_create_taxonomy_term_reference($term->tid, $options['language']),
          );
          $current_result = taxonomy_csv_term_import($unsaved_term, TAXONOMY_CSV_EXISTING_UPDATE);
          // Terms are already memorised.
          $result['msg'] = array_merge($result['msg'], $current_result['msg']);
          if (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
            break 2;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_FLAT:
        foreach ($line as $term_name) {
          $term = (object) array(
            'name'     => $term_name,
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
          );
          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          // Import term then store and check result.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break 2;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_TREE_STRUCTURE:
        // Same process, except when term is imported.
      case TAXONOMY_CSV_FORMAT_POLYHIERARCHY:
        // 1. Check if one term or partial line format is used in order to
        // virtually complete line with previous line.
        // Find first non empty item as line can be full, partial or one term.
        for ($first = 0; ($first < count($line)) && empty($line[$first]); $first++) {
        }
        // Else, line is full. As with one term import, imported items on
        // previous line can be bypassed if lines are ordered. So, look for
        // first different item.
        // This check shouldn't be done with IGNORE_ALL, currently not
        // implemented because it's useless.
        if (!$first) {
          for ($first = 0;
            ($first < count($line) - 1)
              && ($first < count($previous_items['name']))
              && ($line[$first] == $previous_items['name'][$first]);
            $first++) {
          }
        }

        // 2. Remove and remember surabondant previous items for next line.
        if ($first) {
          $result['name'] = $previous_items['name'] = array_slice($previous_items['name'], 0, $first);
          $result['tid']  = $previous_items['tid']  = array_slice($previous_items['tid'], 0, $first);
          $result['msg'][] = 683; // Previous line term.

          // Set root or previous ancestor name and id.
          $parent_name = $previous_items['name'][$first - 1];
          $parent_tid  = $previous_items['tid'][$first - 1];
        }
        // Item is the first on the line: it's a root term.
        else {
          $parent_name = '';
          $parent_tid  = 0;
        }

        // 3. Import each new term then store and check result.
        for ($c = $first; $c < count($line); $c++) {
          $term = (object) array(
            'name'     => $line[$c],
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
            'parent'   => array($parent_tid => $parent_tid),
          );
          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          switch ($options['import_format']) {
            case TAXONOMY_CSV_FORMAT_TREE_STRUCTURE:
              // With TAXONOMY_CSV_EXISTING_IGNORE, parent terms (so all
              // terms but the last on this line) are always updated because
              // they are successive parents of a child.
              $current_result = ($options['existing_items'] == TAXONOMY_CSV_EXISTING_IGNORE && ($c < count($line) - 1)) ?
                  taxonomy_csv_term_import($term, TAXONOMY_CSV_EXISTING_IGNORE_PREVIOUS, FALSE, $parent_tid) :
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, $parent_tid);
              break;

            case TAXONOMY_CSV_FORMAT_POLYHIERARCHY:
              // Check direct duplicates: in Drupal, a term can't be its parent.
              $current_result = ($term->name == $parent_name) ?
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, $parent_tid) :
                  taxonomy_csv_term_import($term, $options['existing_items'], FALSE, NULL);
              break;
          }
          $parent_name = $current_result['name'];
          $parent_tid  = $current_result['tid'];
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break 2;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_PARENTS:
        // 1. Import parents using a recursive call and check result.
        if (count($line) > 1) {
          $options_temp = $options;
          $options_temp['import_format'] = TAXONOMY_CSV_FORMAT_FLAT;
          $result = taxonomy_csv_line_import(array_slice($line, 1), $options_temp, $terms_count);
          $terms_count = $result['terms_count'];
          if (_taxonomy_csv_worst_message($result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
            break;
          }
        }

        // 2. Import main term and store result.
        // Don't check tid == parent_tid because duplicates have been removed.
        $term = (object) array(
          'name'     => $line[0],
          'vid'      => $options['vocabulary']->vid,
          'format'   => $options['filter_format'],
          'language' => $options['language'],
          'vocabulary_machine_name' => $options['vocabulary']->machine_name,
          'parent'   => array($result['tid'] => $result['tid']),
        );
        // Weight is not set above in order to keep existing one if it exists.
        ++$terms_count;
        if ($options['keep_order']) {
          $term->weight = $terms_count;
        }

        $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
        // No check because only one term.
        // Use array_unshift in order to keep $line order of items.
        array_unshift($result['name'], $current_result['name']);
        array_unshift($result['tid'], $current_result['tid']);
        $result['msg'] = array_merge($result['msg'], $current_result['msg']);
        $result['terms_count'] = $terms_count;
        break;

      case TAXONOMY_CSV_FORMAT_CHILDREN:
        // 1. Import main term then store and check result.
        $options_temp = $options;
        $options_temp['import_format'] = TAXONOMY_CSV_FORMAT_ALONE_TERMS;
        $result = taxonomy_csv_line_import(array($line[0]), $options_temp, $terms_count);
        $terms_count = $result['terms_count'];
        if (_taxonomy_csv_worst_message($result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE) {
          break;
        }
        // Remember tid of main term.
        $parent_tid = $result['tid'][0];

        // 2. Import children.
        foreach (array_slice($line, 1) as $value) {
          $term = (object) array(
            'name'     => $value,
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
            'parent'   => array($parent_tid => $parent_tid),
          );
          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          // Import term then store and check result.
          // Don't check tid == parent_tid because duplicates have been removed.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break 2;
          }
        }
        break;

      case TAXONOMY_CSV_FORMAT_RELATIONS:
        // Each related term should exist before first column term can be
        // related to it (need of its tid). Next, process relations and
        // eventually subrelations.
        // So with a line A,B,C,D,E..., creates A, BA, CA(B), DA(BC), EA(BCD)...
        // as it's the fatest way to create one or all relations even if items
        // don't exist.
        // As use of name is only for first column, need to keep previous tids
        // matching names in $previous_relations ([name] <=> [tid]).
        $previous_relations = array();
        foreach ($line as $key => $term) {
          $term = (object) array(
            'name'     => $line[$key],
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
            'field_term_relation' => _taxonomy_csv_field_create_taxonomy_term_reference(array_slice($previous_relations, 0, ($options['relations_create_subrelations']) ? $key : $key != 0), $options['language']),
          );
          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          // @todo Set an 'ignore all' option.
          // For second and next terms, update merge related terms in order to
          // keep previous relations, as option is only for first column term.
          $current_term_import_option = ($key == 0) ?
            $options['existing_items'] :
            TAXONOMY_CSV_EXISTING_UPDATE;
          $current_result = taxonomy_csv_term_import($term, $current_term_import_option, $options['relations_all_vocabularies'], NULL);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break 2;
          }

          $previous_relations[$current_result['name']] = $current_result['tid'];
        }

        // Unlike Drupal 6, relation field is linked only in one way. So, an
        // update is needed.
        $terms = $options['relations_create_subrelations'] ?
          $previous_relations :
          array($line[0] => $previous_relations[$line[0]]);

        foreach ($terms as $name => $tid) {
          // Remove relation to itself.
          $relations = $previous_relations;
          unset($relations[$name]);
          $relations = array_values($relations);

          $term = (object) array(
            'tid'      => $tid,
            'name'     => $name,
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => $options['language'],
            'field_term_relation' => _taxonomy_csv_field_create_taxonomy_term_reference($relations, $options['language']),
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
          );

          $current_result = taxonomy_csv_term_import($term, TAXONOMY_CSV_EXISTING_UPDATE, $options['relations_all_vocabularies'], NULL);
          // Terms are already memorised.
          $result['msg'] = array_merge($result['msg'], $current_result['msg']);
        }
        break;

      case TAXONOMY_CSV_FORMAT_TRANSLATE_TERMS:
        if (!module_exists('i18n_taxonomy')) {
          $result['msg'][] = 360; // Translation error.
          break;
        }

        // If i18n mode is I18N_MODE_LOCALIZE, then localizes directly.
        if ($options['vocabulary']->i18n_mode == I18N_MODE_LOCALIZE) {
          // 1. Import main term then store and check result.
          $term = (object) array(
            'name'     => $line[0],
            'vid'      => $options['vocabulary']->vid,
            // Other formats aren't allowed for translation of the description.
            'format'   => 'plain_text',
            // With this i18n mode, language of main term is always undefined,
            // whatever the vocabulary language is.
            'language' => 'und',
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
          );
          if (isset($line[2]) && $line[2]) {
            $term->description = _taxonomy_csv_set_line_break($line[2]);
          }

          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          // Import term then store result.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break;
          }

          // 2. Create localization.
          $result_translation = i18n_string_translation_update(
            array('taxonomy', 'term', $current_result['tid'], 'name'),
            $line[1],
            $options['language'],
            $line[0]
          );
          if (!$result_translation) {
            $result['msg'][] = 360; // Translation error.
            break;
          }

          if (isset($line[3]) && $line[2] && $line[3]) {
            $result_translation = i18n_string_translation_update(
              array('taxonomy', 'term', $current_result['tid'], 'description'),
              $line[3],
              $options['language'],
              $line[2]
            );
            if (!$result_translation) {
              $result['msg'][] = 360; // Translation error.
              break;
            }
          }
        }

        // If i18n mode is I18N_MODE_TRANSLATE or I18N_MODE_MULTIPLE, then
        // imports terms and creates a translation set for them.
        elseif (($options['vocabulary']->i18n_mode == I18N_MODE_TRANSLATE) || ($options['vocabulary']->i18n_mode == I18N_MODE_MULTIPLE)) {
          // 1. Prepare main term.
          $term = (object) array(
            'name'     => $line[0],
            'vid'      => $options['vocabulary']->vid,
            'format'   => $options['filter_format'],
            'language' => language_default('language'),
            'vocabulary_machine_name' => $options['vocabulary']->machine_name,
          );
          if (isset($line[2]) && $line[2]) {
            $term->description = _taxonomy_csv_set_line_break($line[2]);
          }
          // Weight is not set above in order to keep existing one if it exists.
          ++$terms_count;
          if ($options['keep_order']) {
            $term->weight = $terms_count;
          }

          // Import term then store result.
          $current_result = taxonomy_csv_term_import($term, $options['existing_items']);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break;
          }
          // Needed to get term with tid and eventual tsid.
          $term = taxonomy_term_load($current_result['tid']);

          // 2. Use translation set of the term if it exists, else create it.
          $translation_set = ($term->i18n_tsid) ?
            i18n_translation_set_load($term->i18n_tsid) :
            i18n_translation_set_create('taxonomy_term', $options['vocabulary']->machine_name);

          $translation_set->add_item($term, $term->language);

          // 3. Check if the term is already translated in order to update,
          // replace or ignore it.
          $existing_terms = $translation_set->get_translations();
          $translated_term = new stdClass;
          if (isset($existing_terms[$options['language']])) {
            switch ($options['existing_items']) {
              case TAXONOMY_CSV_EXISTING_UPDATE:
              case TAXONOMY_CSV_EXISTING_UPDATE_REPLACE:
                $translated_term = $existing_terms[$options['language']];
                // As the term is already loaded, we simply save it without search
                // another.
                $options['existing_items'] = TAXONOMY_CSV_EXISTING_IGNORE;
                break;
              case TAXONOMY_CSV_EXISTING_IGNORE:
                break;
            }
          }

          // 4. Complete or create the translated term, then import it.
          $translated_term->name = $line[1];
          $translated_term->vid  = $options['vocabulary']->vid;
          $translated_term->format = $options['filter_format'];
          $translated_term->language = $options['language'];
          $translated_term->vocabulary_machine_name = $options['vocabulary']->machine_name;
          if (isset($line[3]) && $line[2] && $line[3]) {
            $translated_term->description = _taxonomy_csv_set_line_break($line[3]);
          }

          // Import term then store result.
          $current_result = taxonomy_csv_term_import($translated_term, $options['existing_items']);
          if (_taxonomy_csv_line_result($result, $current_result, $terms_count)) {
            break;
          }
          // Needed to get a term with tid.
          $translated_term = taxonomy_term_load($current_result['tid']);

          // 5. Update or create the translation set.
          // Remove is needed to avoid errors when a translated term is
          // updated.
          $translation_set->remove_language($translated_term->language);
          $translation_set->add_item($translated_term, $translated_term->language);

          $translation_set->save(TRUE);
        }

        // Else error.
        else {
          $result['msg'][] = 361; // Translation of vocabulary error.
        }
        break;

      default:
        // Check external formats. Use it only if it works.
        $funcname = "taxonomy_csv_line_import_{$options['import_format']}";
        if (taxonomy_csv_format_check($options['import_format'], $funcname)) {
          $result = $funcname($line, $options, $previous_items, $terms_count);
        }
        else {
          $result['msg'][] = 306; // Error unknown import format.
        }
    }
  }
  else {
    $result['msg'][] = 685; // No term to process.
  }

  return $result;
}

/**
 * Helper to merge results with current result.
 *
 * @return
 *   TRUE if the result contains an error. Result is passed by reference.
 */
function _taxonomy_csv_line_result(&$result, $current_result, $terms_count) {
  $result['name'][] = $current_result['name'];
  $result['tid'][]  = $current_result['tid'];
  $result['msg'] = array_merge($result['msg'], $current_result['msg']);
  $result['terms_count'] = $terms_count;
  return (_taxonomy_csv_worst_message($current_result['msg']) < TAXONOMY_CSV_PROCESS_NOTICE);
}

/**
 * Update or create a term with the given name in the given vocabulary and
 * given parent.
 *
 * @param $term
 *   A term object to import. Term contains:
 *   - 'name'        => term name string,
 *   and eventually, matching options:
 *   - 'tid'         => term id,
 *   - 'vid'         => the vocabulary id where to import,
 *   - 'description' => description string,
 *   - 'format'      => the filter format of the description,
 *   - 'language'    => the language id of the term,
 *   - 'weight'      => weight integer,
 *   - 'parent'      => array of first level parent tids,
 *   // Specific thesaurus fields.
 *   - 'field_term_synonym'  => field array of synonyms terms names strings,
 *   - 'field_term_relation' => field array of related tids,
 * @param $existing_items
 *   (Optional) Type of import on existing terms. Default to ignore and create.
 * @param $all_vocabularies
 *   (Optional) Boolean. Search in all vocabularies or only in $term->vid
 *   vocabulary (default), which need to be set. Used with relations import.
 * @param $parent_tid
 *   (Optional) The direct parent term id where to restrict search.
 *   Used for structure import. Default to NULL (no parent restriction).
 * @param $import_format
 *   (Optional) Name of import format. Needed only with formats with specific
 *   fields.
 *
 * @return array
 *    'name' => term name,
 *    'tid'  => term id,
 *    'msg'  => messages array.
 */
function taxonomy_csv_term_import($term, $existing_items = TAXONOMY_CSV_EXISTING_IGNORE, $all_vocabularies = FALSE, $parent_tid = NULL, $import_format = '') {
  $messages = array();

  // Basic check to avoid notices when "Check lines" option is disabled.
  if ($term->name == '') {
    $term->tid = 0;
    $messages[] = 432; // Warning line contains an empty term.
  }
  else {
    switch ($existing_items) {
      case TAXONOMY_CSV_EXISTING_UPDATE:
        $existing_term = taxonomy_csv_term_find($term, $all_vocabularies, $parent_tid);
        if ($existing_term) {
          // Update only fields that are set. Other fields are not changed.
          foreach ($term as $key => $value) {
            // Custom fields arrays: they are not simple array.
            if ($key == 'field_term_synonym') {
              _taxonomy_csv_field_update_text($key, $term, $existing_term);
            }
            elseif ($key == 'field_term_relation') {
              _taxonomy_csv_field_update_taxonomy_term_reference($key, $term, $existing_term);
            }
            // Arrays: merge existing and new items.
            // Only used for parent in standard taxonomy of Drupal 7.
            elseif (is_array($value) && isset($existing_term->{$key})) {
              $term->{$key} = array_unique(array_merge($existing_term->{$key}, $value));
            }
            // Else simply use new key: no merge is possible and useful for
            // string, numeric or boolean fields.
            // Description was an exception in previous version, but this
            // exception is removed for simplicity and real use of this module.
            // An option may be added if needed.
          }
          // Existing fields of existing term should be kept even if they have
          // not been set in new term.
          $term = (object) array_merge((array) $existing_term, (array) $term);
        }
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE_PREVIOUS:
        // Doesn't ignore, but use previous parents.
      case TAXONOMY_CSV_EXISTING_UPDATE_REPLACE:
        $existing_term = taxonomy_csv_term_find($term, $all_vocabularies, $parent_tid);
        if ($existing_term) {
          // All fields are replaced by new ones. Other existing fields of
          // existing term should be kept even if they are not set in new term.
          $term = (object) array_merge((array) $existing_term, (array) $term);
        }
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE:
        break;

      case TAXONOMY_CSV_EXISTING_IGNORE_ALL:
        // Ignore even existing terms in additional columns.
        // @todo IGNORE_ALL
        break;
    }

    // Finish to set the term to avoid NULL. Format and language are set before.
    if (!isset($term->description)) {
      $term->description = '';
    }
    // Save regularly formatted term.
    // Return either SAVED_NEW, SAVED_UPDATED or FALSE (no change).
    $result = taxonomy_term_save($term);

    // If there are specific fields, save them.
    $funcname = "taxonomy_csv_term_import_$import_format";
    if (taxonomy_csv_format_check($import_format, $funcname)) {
      $result_temp = $funcname($term);
    }

    $messages[] = ($result == SAVED_NEW) ? 691 : 692; // Saved or updated.

    // Save hook messages.
    if (isset($_SESSION['taxonomy_csv_import']['messages']) && (count($_SESSION['taxonomy_csv_import']['messages']) > 0)) {
      foreach ($_SESSION['taxonomy_csv_import']['messages'] as $value) {
        $messages[] = $value;
      }
      $_SESSION['taxonomy_csv_import']['messages'] = array();
    }
  }

  return array(
    'name' => $term->name,
    'tid'  => $term->tid,
    'msg'  => $messages,
  );
}

/**
 * Helper to build a standard text field from a simple string or an array.
 *
 * @todo To be removed (as other helpers) by using of Field api (but slower).
 * @todo Fields internationalization. Should be compatible with the i18n mode of
 *   the vocabulary.
 *
 * @param $value
 *   A string or an array to convert.
 * @param $language
 *   (Optional). Language to use. Default is 'und' (undefined).
 * @param $format
 *   (Optional). Format of the field. Default to NULL (fixed plain text).
 *
 * @return
 *   Formatted field array.
 */
function _taxonomy_csv_field_create_text($value, $language = 'und', $format = NULL) {
  // Currently, i18n of term custom fields is not supported.
  $language = 'und';

  $field = array();
  if (!is_array($value) && !empty($value)) {
    $value = array($value);
  }

  if ($format == 'none') {
    $format = NULL;
  }

  foreach ($value as $item) {
    if ($item !== '') {
      $field[] = array(
        'value' => $item,
        'format' => $format,
        'safe_value' => ($format) ?
          check_markup($item, $format, $language) :
          check_plain($item),
      );
    }
  }

  return ($field) ?
    array($language => $field) :
    array();
}

/**
 * Helper to build a standard term reference field from a string or an array.
 *
 * @param $value
 *   A string or an array to convert.
 * @param $language
 *   (Optional). Language to use. Default is 'und' (undefined).
 *
 * @return
 *   Formatted field array.
 */
function _taxonomy_csv_field_create_taxonomy_term_reference($value, $language = 'und') {
  // Currently, i18n of term custom fields is not supported.
  $language = 'und';

  $field = array();
  if (!is_array($value) && !empty($value)) {
    $value = array($value);
  }

  foreach ($value as $item) {
    if ($item) {
      $field[]['tid'] = $item;
    }
  }

  return ($field) ?
    array($language => $field) :
    array();
}

/**
 * Helper to convert an internal array field to a standard text field.
 *
 * @param $field_name
 *   Field to update.
 * @param $term
 * @param $existing_term
 *
 * @return
 *   Nothing: $term object is passed by reference.
 */
function _taxonomy_csv_field_update_text($field_name, $term, $existing_term) {
  // Complete term if there are already items.
  if (is_array($existing_term->{$field_name}) && !empty($existing_term->$field_name)) {
    $new_field = $term->{$field_name};
    $term->{$field_name} = $existing_term->$field_name;
    $field = &$term->{$field_name};
    foreach ($new_field as $field_language => $array) {
      // Don't update if new field is empty.
      if (!empty($array)) {
        // Update the value for that language.
        if (isset($field[$field_language])) {
          // Don't use array_merge or array_merge_recursive to avoid duplicates.
          $existing = array();
          foreach ($field[$field_language] as &$value) {
            $existing[] = &$value['value'];
          }
          foreach ($array as &$new_value) {
            // Avoid duplicates and avoid to append an empty item.
            if (!in_array($new_value['value'], $existing) && ($new_value['value'] !== '')) {
              $field[$field_language][] = $new_value;
            }
          }
        }
        // Value for this language is not set, so complete term directly.
        else {
          foreach ($array as &$new_value) {
            // Avoid to append an empty item.
            if ($new_value['value'] !== '') {
              $field[$field_language][] = $new_value;
            }
          }
        }
      }
    }
  }
  // Else nothing to do: term contains already new field.
}

/**
 * Helper to convert an internal array field to a standard term reference field.
 *
 * @param $field_name
 *   Field to update.
 * @param $term
 * @param $existing_term
 *
 * @return
 *   Nothing: $term object is passed by reference.
 */
function _taxonomy_csv_field_update_taxonomy_term_reference($field_name, $term, $existing_term) {
  // Complete term if there are already items.
  if (is_array($existing_term->{$field_name}) && !empty($existing_term->$field_name)) {
    $new_field = $term->{$field_name};
    $term->{$field_name} = $existing_term->$field_name;
    $field = &$term->{$field_name};
    foreach ($new_field as $field_language => $array) {
      // Don't update if new field is empty.
      if (!empty($array)) {
        // Update the value for that language.
        if (isset($field[$field_language])) {
          // Don't use array_merge or array_merge_recursive to avoid duplicates.
          $existing = array();
          foreach ($field[$field_language] as &$value) {
            $existing[] = &$value['tid'];
          }
          foreach ($array as &$new_value) {
            // Avoid duplicates and avoid to append an empty item.
            if (!in_array($new_value['tid'], $existing) && ($new_value['tid'] != 0)) {
              $field[$field_language][] = $new_value;
            }
          }
        }
        // Value for this language is not set, so complete term directly.
        else {
          foreach ($array as &$new_value) {
            // Avoid to append an empty item.
            if ($new_value['tid'] != 0) {
              $field[$field_language][] = $new_value;
            }
          }
        }
      }
    }
  }
  // Else nothing to do: term contains already new field.
}

/**
 * Helper to convert an internal repetitive field to a standard text field.
 *
 * @param $term
 *   A taxonomy term object with custom fields.
 * @param $field_name
 * @param $language
 *
 * @return
 *   Nothing: $term object is passed by reference.
 */
function _taxonomy_csv_line_replace_field_text($term, $field_name, $language = 'und') {
  if (isset($term->{$field_name}) && is_array($term->$field_name)) {
    $field = array();
    foreach ($term->{$field_name} as $value) {
      $field[] = array(
        'value' => $value,
        'format' => NULL,
        'safe_value' => check_plain($value),
      );
    }
    $term->{$field_name}[$language] = $field;
  }
}
