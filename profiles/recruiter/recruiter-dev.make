; recruiter profile make file
core = 7.x
api = 2

;  -  Modules  -

; Main modules
projects[ctools] = 1

projects[entity] = 1.x-dev

projects[field_collection] = 1
projects[profile2] = 1
projects[context] = 3

projects[message] = 1.x-dev

projects[rules] = 2

projects[views] = 3

projects[views_bulk_operations] = 3.x-dev

; Features
projects[features] = 1

projects[diff] = 2
projects[strongarm] = 2

;Search API
projects[search_api] = 1

projects[search_api_solr] = 1.x-dev

projects[search_api_saved_searches] = 1

projects[facetapi] = 1.x-dev

;Field types
projects[addressfield] = 1
projects[email] = 1
projects[date] = 2
projects[link] = 1
projects[term_level] = 1.x-dev

projects[entityreference] = 1

;Taxonomy utils
projects[taxonomy_csv] = 5
projects[taxonomy_manager] = 1
projects[content_taxonomy] = 1
projects[autocomplete_deluxe] = 1.x-dev
projects[rules_autotag] = 1

projects[synonyms] = 1.x-dev

;Misc
projects[colorbox] = 1

projects[rules_link] = 1.x-dev

projects[field_permissions] = 1
projects[pathauto] = 1
projects[token] = 1

projects[flag][download][type] = git
projects[flag][download][branch] = 7.x-2.x
; Flag any entity http://drupal.org/node/1035410
projects[flag][patch][] = "http://drupal.org/files/flag_entity2_0.patch"
; Flag entity properties http://drupal.org/node/1315850
projects[flag][patch][] = "http://drupal.org/files/flag_entity_properties_0.patch"
; Flag Add views handler for flag entity links http://drupal.org/node/1362298
projects[flag][patch][] = "http://drupal.org/files/flag_views_entity_handler_1.patch"

projects[mailsystem] = 2

projects[mimemail] = 1.x-dev 

projects[role_export] = 1

;Recruiter Features
projects[recruiter_features] = 1.x-dev


;  -  Libraries  -

;Library for accessing solr servers
libraries[SolrPhpClient][download][type] = "get"
libraries[SolrPhpClient][download][url] = "http://solr-php-client.googlecode.com/files/SolrPhpClient.r60.2011-05-04.tgz"
libraries[SolrPhpClient][directory_name] = "SolrPhpClient"
libraries[SolrPhpClient][destination] = "modules/search_api_solr/"

; Also add the colorbox library.
libraries[colorbox][download][type] = "get"
libraries[colorbox][download][url] = "http://jacklmoore.com/colorbox/colorbox.zip"
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][destination] = "libraries"

