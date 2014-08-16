<?php
/**
 * @file
 * Feeds parser class for FeedsMeetupParserBase.
 */

/**
 * Class definition for Meetup Parser.
 *
 * Parses XML feeds returned from Meetup API calls
 */
class FeedsMeetupParserBase extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $meetup_feed = $fetcher_result->getRaw();
    $result = new FeedsParserResult();

    // @see common_syndication_parser_parse()
    if (!defined('LIBXML_VERSION') || (version_compare(phpversion(), '5.1.0', '<'))) {
      @$sxml = simplexml_load_string($meetup_feed, NULL);
    }
    else {
      @$sxml = simplexml_load_string($meetup_feed, NULL, LIBXML_NOERROR | LIBXML_NOWARNING | LIBXML_NOCDATA);
    }

    // Got malformed XML?
    if ($sxml === FALSE || is_null($sxml)) {
      throw new Exception(t('FeedsMeetupParserBase: Malformed XML source.'));
    }

    // Parse Meetup XML.
    $result = $this->parseMeetup($sxml, $source, $fetcher_result);

    return $result;
  }
}
