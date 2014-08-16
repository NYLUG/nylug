<?php
/**
 * @file
 * Feeds parser class for FeedsMeetupVenueParser.
 */

/**
 * Class definition for Meetup Venue Parser.
 *
 * Parses XML feeds returned from Meetup API venue call
 */
class FeedsMeetupVenueParser extends FeedsMeetupParserBase {

  /**
   * Add the extra mapping sources provided by this parser.
   */
  public function getMappingSources() {
    return parent::getMappingSources() + array(
      'name' => array(
        'name' => t('Venue name'),
        'description' => t('Venue name.'),
      ),
      'id' => array(
        'name' => t('Venue ID'),
        'description' => t('Meetup venue unique ID.'),
      ),
      'address_1' => array(
        'name' => t('Address line 1'),
      ),
      'address_2' => array(
        'name' => t('Address line 2'),
      ),
      'city' => array(
        'name' => t('City'),
      ),
      'zip' => array(
        'name' => t('Zip'),
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
        'description' => t('The cumulative rating of the venue.'),
      ),
      'rating_count' => array(
        'name' => t('Rating count'),
        'description' => t('The number of times the venue has been rated.'),
      ),
      'email' => array(
        'name' => t('Email'),
      ),
      'fax' => array(
        'name' => t('Fax'),
      ),
      'phone' => array(
        'name' => t('Phone'),
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
        'address_1' => (string) $entry->address_1,
        'address_2' => (string) $entry->address_2,
        'city' => (string) $entry->city,
        'zip' => (string) $entry->zip,
        'state' => (string) $entry->state,
        'country' => (string) $entry->country,
        'lat' => (string) $entry->lat,
        'lon' => (string) $entry->lon,
        'rating' => (string) $entry->rating,
        'rating_count' => (string) $entry->rating_count,
        'email' => (string) $entry->email,
        'fax' => (string) $entry->fax,
        'phone' => (string) $entry->phone,
      );

      // Populate the FeedsFetcherResult object with the parsed results.
      $result->items[] = $item;
    }
    return $result;
  }
}
