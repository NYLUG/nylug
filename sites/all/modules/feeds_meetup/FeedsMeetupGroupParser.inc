<?php
/**
 * @file
 * Feeds parser class for FeedsMeetupGroupParser.
 */

/**
 * Class definition for Meetup Group Parser.
 *
 * Parses XML feeds returned from Meetup API group call
 */
class FeedsMeetupGroupParser extends FeedsMeetupParserBase {

  /**
   * Add the extra mapping sources provided by this parser.
   */
  public function getMappingSources() {
    return parent::getMappingSources() + array(
      'name' => array(
        'name' => t('Group name'),
        'description' => t('Group name.'),
      ),
      'id' => array(
        'name' => t('Group ID'),
        'description' => t('Meetup group unique ID.'),
      ),
      'url' => array(
        'name' => t('Group URL'),
        'description' => t('The URL of the group.'),
      ),
      'urlname' => array(
        'name' => t('Group URL name'),
        'description' => t('The machine name Meetup uses to refer to the group.'),
      ),
      'pronoun' => array(
        'name' => t('Group pronoun'),
        'description' => t('The pronoun the group uses to describe its members.'),
      ),
      'city' => array(
        'name' => t('City'),
      ),
      'state' => array(
        'name' => t('State'),
      ),
      'country' => array(
        'name' => t('Country'),
      ),
      'lat' => array(
        'name' => t('Latitude'),
      ),
      'lon' => array(
        'name' => t('Longitude'),
      ),
      'rating' => array(
        'name' => t('Rating'),
        'description' => t('The cumulative rating of the group.'),
      ),
      'members' => array(
        'name' => t('Member count'),
      ),
      'visibility' => array(
        'name' => t('Visibility'),
      ),
      'join_mode' => array(
        'name' => t('Join mode'),
      ),
      'description' => array(
        'name' => t('Description'),
      ),
      'created_timestamp' => array(
        'name' => t('Created on (timestamp)'),
      ),
      'created_datetime' => array(
        'name' => t('Created on (datetime)'),
      ),
      'timezone' => array(
        'name' => t('Timezone'),
      ),
      'topics_name' => array(
        'name' => t('Topics'),
      ),
      'topics_machine' => array(
        'name' => t('Topics (machine names)'),
      ),
      'topics_id' => array(
        'name' => t('Topics (IDs)'),
      ),
      'category' => array(
        'name' => t('Category'),
      ),
      'category_machine' => array(
        'name' => t('Category (machine name)'),
      ),
      'category_id' => array(
        'name' => t('Category (ID)'),
      ),
      'topics_machine' => array(
        'name' => t('Topics (machine names)'),
      ),
      'topics_id' => array(
        'name' => t('Topics (IDs)'),
      ),
      'organizer_name' => array(
        'name' => t('Organizer name'),
      ),
      'organizer_id' => array(
        'name' => t('Organizer ID'),
      ),
      'group_photo' => array(
        'name' => t('Group photo link'),
      ),
      'group_photo_highres' => array(
        'name' => t('Group photo link (high res)'),
      ),
      'group_photo_thumb' => array(
        'name' => t('Group photo link (thumbnail)'),
      ),
      'group_photo_id' => array(
        'name' => t('Group photo ID'),
      ),
    );
  }

  /**
   * Parse Meetup XML feed.
   *
   * @param SimpleXMLElement $sxml
   *   Meetup XML feed.
   * @param FeedsSource $source
   *   Metadata regarding Meetup XML feed.
   * @param FeedsFetcherResult $fetcher_result
   *   Return value.
   */
  protected function parseMeetup(SimpleXMLElement $sxml, FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    // XML was parsed successfully, so we can begin to process items.
    $result = new FeedsParserResult();
    $fetcher_result->title = (string) $sxml->head->title;
    $fetcher_result->description = (string) $sxml->head->description;
    $fetcher_result->link = (string) $sxml->head->url;

    // Iterate over entries in feed.
    foreach ($sxml->xpath('//item') as $entry) {
      $item = array(
        'name' => (string) $entry->name,
        'id' => (string) $entry->id,
        'url' => (string) $entry->link,
        'urlname' => (string) $entry->urlname,
        'pronoun' => (string) $entry->who,
        'city' => (string) $entry->city,
        'state' => (string) $entry->state,
        'country' => (string) $entry->country,
        'lat' => (string) $entry->lat,
        'lon' => (string) $entry->lon,
        'description' => (string) $entry->description,
        'rating' => (string) $entry->rating,
        'members' => (string) $entry->members,
        'visibility' => (string) $entry->visibility,
        'join_mode' => (string) $entry->join_mode,
        'created_datetime' => date('Y-m-d H:i:s', _feeds_meetup_msToSeconds((string) $entry->created)),
        'created_timestamp' => _feeds_meetup_msToSeconds((string) $entry->created),
        'timezone' => (string) $entry->timezone,
        'organizer_id' => (string) $entry->organizer->member_id,
        'organizer_name' => (string) $entry->organizer->name,
      );

      // Extract category details if category is specified.
      if (isset($entry->category)) {
        $category = (isset($entry->category->name)) ? (string) $entry->category->name : '';
        $category_machine = (isset($entry->category->shortname)) ? (string) $entry->category->shortname : '';
        $category_id = (isset($entry->category->id)) ? (string) $entry->category->id : '';

        $item += array(
          'category' => (string) $category,
          'category_machine' => (string) $category_machine,
          'category_id' => (string) $category_id,
        );
      }

      // Extract group photo details if group photo is specified.
      if (isset($entry->group_photo)) {
        $group_photo = (isset($entry->group_photo->photo_link)) ? (string) $entry->group_photo->photo_link : '';
        $group_photo_highres = (isset($entry->group_photo->highres_link)) ? (string) $entry->group_photo->highres_link : '';
        $group_photo_thumb = (isset($entry->group_photo->thumb_link)) ? (string) $entry->group_photo->thumb_link : '';
        $group_photo_id = (isset($entry->group_photo->id)) ? (string) $entry->group_photo->id : '';

        $item += array(
          'group_photo_id' => (string) $group_photo_id,
          'group_photo' => (string) $group_photo,
          'group_photo_thumb' => (string) $group_photo_thumb,
          'group_photo_highres' => (string) $group_photo_highres,
        );
      }

      // Extract topic details if topics are specified.
      if (isset($entry->topics)) {
        $topics_name = array();
        $topics_machine = array();
        $topics_id = array();

        foreach ($entry->topics->topics_item as $topic) {
          $topic_name = (isset($topic->name)) ? (string) $topic->name : '';
          $topic_machine = (isset($topic->urlkey)) ? (string) $topic->urlkey : '';
          $topic_id = (isset($topic->id)) ? (string) $topic->id : '';

          $topics_name[] = $topic_name;
          $topics_machine[] = $topic_machine;
          $topics_id[] = $topic_id;
        }

        $item += array(
          'topics_name' => $topics_name,
          'topics_machine' => $topics_machine,
          'topics_id' => $topics_id,
        );
      }

      // Populate the FeedsFetcherResult object with the parsed results.
      $result->items[] = $item;
    }
    return $result;
  }
}
