<?php
/**
 * @file
 * Feeds parser class for FeedsMeetupEventParser.
 */

/**
 * Class definition for Meetup Event Parser.
 *
 * Parses XML feeds returned from Meetup API event call
 */
class FeedsMeetupEventParser extends FeedsMeetupParserBase {

  /**
   * Add the extra mapping sources provided by this parser.
   */
  public function getMappingSources() {
    return parent::getMappingSources() + array(
      'title' => array(
        'name' => t('Event title'),
        'description' => t('Event title.'),
      ),
      'id' => array(
        'name' => t('Event ID'),
        'description' => t('Meetup event unique ID.'),
      ),
      'event_timestamp' => array(
        'name' => t('Event time (timestamp)'),
      ),
      'event_datetime' => array(
        'name' => t('Event time (datetime)'),
      ),
      'utc_offset' => array(
        'name' => t('UTC offset'),
        'description' => t('Offset of timestamps from UTC.'),
      ),
      'updated_timestamp' => array(
        'name' => t('Updated on (timestamp)'),
      ),
      'updated_datetime' => array(
        'name' => t('Updated on (datetime)'),
      ),
      'published_timestamp' => array(
        'name' => t('Published on (timestamp)'),
      ),
      'published_datetime' => array(
        'name' => t('Published on (datetime)'),
      ),
      'description' => array(
        'name' => t('Description'),
      ),
      'event_url' => array(
        'name' => t('Event URL'),
        'description' => t('The URL of the event.'),
      ),
      'rsvp_yes' => array(
        'name' => t('"Yes" RSVP count'),
      ),
      'rsvp_maybe' => array(
        'name' => t('"Maybe" RSVP count'),
      ),
      'waitlist' => array(
        'name' => t('Waitlist count'),
      ),
      'headcount' => array(
        'name' => t('Headcount'),
      ),
      'group_name' => array(
        'name' => t('Group name'),
        'description' => t('The name of the hosting Meetup group.'),
      ),
      'group_url' => array(
        'name' => t('Group URL'),
        'description' => t('The URL of the hosting Meetup group.'),
      ),
      'group_id' => array(
        'name' => t('Group ID'),
        'description' => t('The ID of the hosting Meetup group.'),
      ),
      'group_pronoun' => array(
        'name' => t('Group pronoun'),
        'description' => t('The pronoun the hosting Meetup group uses to describe its members.'),
      ),
      'venue_name' => array(
        'name' => t('Venue name'),
      ),
      'venue_id' => array(
        'name' => t('Venue ID'),
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
      'how_to_find_us' => array(
        'name' => t('How to find us'),
      ),
      'fee_type' => array(
        'name' => t('Fee type'),
      ),
      'fee_amount' => array(
        'name' => t('Fee amount'),
      ),
      'fee_description' => array(
        'name' => t('Fee description'),
      ),
      'fee_currency' => array(
        'name' => t('Fee currency'),
      ),
      'fee_required' => array(
        'name' => t('Fee required'),
      ),
      'fee_accepts' => array(
        'name' => t('Fee methods accepted'),
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
        'title' => (string) $entry->name,
        'id' => (string) $entry->id,
        'event_url' => (string) $entry->event_url,
        'description' => (string) $entry->description,
        'headcount' => (string) $entry->headcount,
        'how_to_find_us' => (string) $entry->how_to_find_us,
        'waitlist' => (string) $entry->waitlist_count,
        'rsvp_yes' => (string) $entry->yes_rsvp_count,
        'rsvp_maybe' => (string) $entry->maybe_rsvp_count,
        'group_id' => (string) $entry->group->id,
        'group_name' => (string) $entry->group->name,
        'group_pronoun' => (string) $entry->group->who,
        'group_url' => 'http://www.meetup.com/' . (string) $entry->group->urlname,
        'utc_offset' => _feeds_meetup_msToSeconds((string) $entry->utc_offset),
        'event_datetime' => date('Y-m-d H:i:s', _feeds_meetup_msToSeconds((string) $entry->time)),
        'event_timestamp' => _feeds_meetup_msToSeconds((string) $entry->time),
        'updated_datetime' => date('Y-m-d H:i:s', _feeds_meetup_msToSeconds((string) $entry->updated)),
        'updated_timestamp' => _feeds_meetup_msToSeconds((string) $entry->updated),
        'published_datetime' => date('Y-m-d H:i:s', _feeds_meetup_msToSeconds((string) $entry->created)),
        'published_timestamp' => _feeds_meetup_msToSeconds((string) $entry->created),
      );

      // Extract venue details if a venue is specified.
      if (isset($entry->venue)) {
        $venue_name = (isset($entry->venue->name)) ? (string) $entry->venue->name : '';
        $venue_id = (isset($entry->venue->id)) ? (string) $entry->venue->id : '';
        $address_1 = (isset($entry->venue->address_1)) ? (string) $entry->venue->address_1 : '';
        $address_2 = (isset($entry->venue->address_2)) ? (string) $entry->venue->address_2 : '';
        $city = (isset($entry->venue->city)) ? (string) $entry->venue->city : '';
        $zip = (isset($entry->venue->zip)) ? (string) $entry->venue->zip : '';
        $state = (isset($entry->venue->state)) ? (string) $entry->venue->state : '';
        $country = (isset($entry->venue->country)) ? (string) $entry->venue->country : '';
        $lat = (isset($entry->venue->lat)) ? (string) $entry->venue->lat : '';
        $lon = (isset($entry->venue->lon)) ? (string) $entry->venue->lon : '';

        $item += array(
          'venue_name' => (string) $venue_name,
          'venue_id' => (string) $venue_id,
          'address_1' => (string) $address_1,
          'address_2' => (string) $address_2,
          'city' => (string) $city,
          'zip' => (string) $zip,
          'state' => (string) $state,
          'country' => (string) $country,
          'lat' => (string) $lat,
          'lon' => (string) $lon,
        );
      }

      // Extract fee details if a fee is specified.
      if (isset($entry->fee)) {
        $fee_type = (isset($entry->fee->label)) ? (string) $entry->fee->label : '';
        $fee_required = (isset($entry->fee->required)) ? (string) $entry->fee->required : '';
        $fee_amount = (isset($entry->fee->amount)) ? (string) $entry->fee->amount : '';
        $fee_currency = (isset($entry->fee->currency)) ? (string) $entry->fee->currency : '';
        $fee_accepts = (isset($entry->fee->accepts)) ? (string) $entry->fee->accepts : '';
        $fee_description = (isset($entry->fee->description)) ? (string) $entry->fee->description : '';

        $item += array(
          'fee_type' => (string) $fee_type,
          'fee_required' => (string) $fee_required,
          'fee_amount' => (string) $fee_amount,
          'fee_currency' => (string) $fee_currency,
          'fee_accepts' => (string) $fee_accepts,
          'fee_description' => (string) $fee_description,
        );
      }

      // Populate the FeedsFetcherResult object with the parsed results.
      $result->items[] = $item;
    }
    return $result;
  }
}
