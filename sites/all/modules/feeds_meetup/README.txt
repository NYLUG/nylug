Feeds: Meetup
============

A Meetup feed parser for Drupal, extending the Feeds and Feeds XPath Parser
modules.

Features
========

- Import Meetup XML feeds
  - Events
  - Groups
  - Venues

Requirements
============

- Job Scheduler
  http://drupal.org/project/job_scheduler
- Feeds
  http://drupal.org/project/feeds
- CTools 7.x-1.x
  http://drupal.org/project/ctools
- Drupal 7.x
  http://drupal.org/project/drupal
  
Useful Modules
===============

- Media Feeds
  http://drupal.org/project/media_feeds
- Location Feeds
  http://drupal.org/project/location_feeds

Installation
============

- Install Feeds and Feeds: Meetup.
- Make sure cron is correctly configured http://drupal.org/cron
- Go to admin/structure/feeds/ to create your Meetup feed importers.
- Go to import/ to select your Meetup feed importer.
- Enter the Meetup API URL desired for importing.
  eg, https://api.meetup.com/2/[METHOD].xml/?key=[KEY]&sign=true
- Return import/ to import data.
