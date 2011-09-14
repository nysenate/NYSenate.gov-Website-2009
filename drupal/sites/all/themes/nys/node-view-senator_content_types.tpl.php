<?php
// $Id: node.tpl.php,v 1.4 2008/09/15 08:11:49 johnalbin Exp $

/**
 * @file node.tpl.php
 *
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *   theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *   format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *   from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *   theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 */

?>
<?php
// BLOG, PRESS RELEASE, IN THE NEWS, REPORT, LEGISLATION AND VIDEO TEASERS
if (($teaser && ($node->type == 'blog' || $node->type == 'press_release'  || $node->type == 'in_the_news' || $node->type == 'report' || $node->type == 'legislation' || $node->type == 'video' ))): ?>
  <div style="clear:both"></div><div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"><div class="node-inner">
    <div class="committee-updates-description">
      <h3 class="title">
        <?php print l($node->title, 'node/'.$node->nid); ?>
      </h3>
      <?php if ($unpublished): ?>
        <div class="unpublished"><?php print t('Unpublished'); ?></div>
      <?php endif; ?>
      <div class="content">
        <?php if (isset($node->field_video) & $node->field_video[0]['embed'] && $node->field_video[0]['provider'] != 'livestream'): // teasers have inline display of all video except livestream ?>
          <div class="featured_image">
            <?php
              $field_type = 'field_video';
              $system_types = _content_type_info();
              $field = $system_types['fields'][$field_type];
              // To set custom video size, uncomment these lines
              $field['widget']['video_width'] = 265;
              $field['widget']['video_height'] = 200;
              print theme('emvideo_video_video', $field, $node->field_video[0], 'emvideo_embed', $node);
            ?>
          </div>
        <?php elseif ($node->field_feature_image['0']['filepath']): ?>
          <div class="featured_image">
            <?php print theme('imagecache', 'gallery_thumb', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']); ?>
          </div>
        <?php endif; ?>
        <?php print theme('nyss_misc_clean_markup', $node, $content); ?>
      </div>
      <div class="clearboth"></div>
      <?php if ($links): ?>
        <?php print $links; ?>
      <?php endif; ?>
    </div> <!-- /committee-updates-description -->
    <div class="committee-updates-right-infobox">
      <div class="field field-type-date field-field-date">
        <div class="field-items">
          <label><?php print t('Date Posted') ?>:</label>
            <div class="field-item">
              <?php print format_date($created, 'custom','F j, Y'); ?><br />
              <?php print l(t('Read more...'), 'node/' . $node->nid); ?>
            </div>
        </div>
      </div>
    </div> <!-- /committee-updates-right-infobox -->
  </div></div> <!-- /node-inner, /node -->

<?php
// EVENT TEASERS
elseif (($teaser && ($node->type == 'event' ))): ?>
  <div style="clear:both"></div><div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"><div class="node-inner">
    <div class="committee-updates-description">
      <h3 class="title">
        <?php print l(theme('nyss_event_prefixed_title', $node), 'node/'.$node->nid); ?>
      </h3>
      <?php if ($unpublished): ?>
        <div class="unpublished"><?php print t('Unpublished'); ?></div>
      <?php endif; ?>
      <div class="content">
        <?php if (isset($node->field_video) && $node->field_video[0]['embed'] && $node->field_video[0]['provider'] != 'livestream'): // teasers have inline display of all video except livestream ?>
          <div class="featured_image">
            <?php
              $field_type = 'field_video';
              $system_types = _content_type_info();
              $field = $system_types['fields'][$field_type];
              // To set custom video size, uncomment these lines
              $field['widget']['video_width'] = 265;
              $field['widget']['video_height'] = 200;
              print theme('emvideo_video_video', $field, $node->field_video[0], 'emvideo_embed', $node);
            ?>
          </div>
        <?php elseif ($node->field_feature_image['0']['filepath']):?>
          <div class="featured_image">
            <?php print theme('imagecache', 'gallery_thumb', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']); ?>
          </div>
        <?php endif; ?>
        <div class="committee-update-body">
          <?php print check_markup(strip_tags($node->content['body']['#value'], '<p><div><img><a><b><i><strong><em><div><span><table><tr><td><th><tbody><thead>'), 1, TRUE); ?>
        </div>
      </div>
      <div class="clearboth"></div>
      <?php if ($links && $user->uid): ?>
        <?php print $links; ?>
      <?php endif; ?>
    </div> <!-- /committee-updates-description -->
    <div class="committee-updates-right-infobox">
      <div class="field field-type-date field-field-date">
        <div class="field-items">
          <div class="field-item">
            <label><?php print t('Meeting Schedule') ?>:</label>
            <?php 
              $from_date = date_make_date($node->field_date[0]['value'], 'UTC');
              date_timezone_set($from_date, timezone_open(date_get_timezone('site')));// Fix timezone
              $to_date = date_make_date($node->field_date[0]['value2'], 'UTC');
              date_timezone_set($to_date, timezone_open(date_get_timezone('site')));// Fix timezone
              $from_date_string = date_format_date($from_date, 'custom', 'F j');
              $from_time_string = date_format_date($from_date, 'custom', 'g:i A');
              $to_date_string = date_format_date($to_date, 'custom', 'F j');
              $to_time_string = date_format_date($to_date, 'custom', 'g:i A');
              if ($from_date_string == $to_date_string) {
                print '<span class="date-display-start">' . "$from_date_string, $from_time_string" . '</span><span class="date-display-separator"> - </span><span class="date-display-end">' . $to_time_string . '</span>';
              }
              else {
                print '<span class="date-display-start">' . "$from_date_string, $from_time_string" . '</span><span class="date-display-separator"> - </span><span class="date-display-end">' . "$to_date_string, $to_time_string" . '</span>';
              }
            ?><br />
            <?php print l(t('Read more...'), 'node/' . $node->nid); ?>
          </div>
        </div>
      </div>
    </div> <!-- /committee-updates-right-infobox -->
  </div></div> <!-- /node-inner, /node -->

<?php
// REGULAR TEASERS
elseif ($teaser): ?>
  <div style="clear:both"></div>
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"><div class="node-inner">
    <div class="committee-updates-description">
      <h3 class="title">
        <?php print l($node->title, 'node/'.$node->nid); ?>
      </h3>
      <?php if ($unpublished): ?>
        <div class="unpublished"><?php print t('Unpublished'); ?></div>
      <?php endif; ?>
      <?php if ($submitted): ?>
        <div class="meta">
          <?php if ($submitted && in_array($node->type, array('blog', 'report', 'press_release', 'in_the_news'))): ?>
            <div class="submitted">
              <?php print $submitted; ?>
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>
      <div class="content">
        <?php if (isset($node->field_video) && $node->field_video[0]['embed'] && $node->field_video[0]['provider'] != 'livestream'): // teasers have inline display of all video except livestream ?>
          <div class="featured_image">
            <?php
              $field_type = 'field_video';
              $system_types = _content_type_info();
              $field = $system_types['fields'][$field_type];
              // To set custom video size, uncomment these lines
              $field['widget']['video_width'] = 265;
              $field['widget']['video_height'] = 200;
              print theme('emvideo_video_video', $field, $node->field_video[0], 'emvideo_embed', $node);
            ?>
          </div>
        <?php elseif ($node->field_feature_image['0']['filepath']):?>
          <div class="featured_image">
            <?php print theme('imagecache', 'gallery_thumb', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']); ?>
          </div>
        <?php endif; ?>
        <?php print theme('nyss_misc_clean_markup', $node, $content); ?>
      </div>
      <div class="clearboth"></div>
      <?php if ($links): ?>
        <?php print $links; ?>
      <?php endif; ?>
    </div> <!-- /committee-updates-description -->
    <div class="committee-updates-right-infobox">
      <div class="field field-type-date field-field-date">
        <div class="field-items">
          <label><?php print t('Date Posted') ?>:</label>
          <div class="field-item">
            <?php print format_date($created, 'custom','F j, Y'); ?><br />
            <?php print l(t('Read more...'), 'node/' . $node->nid); ?>
          </div>
        </div>
      </div>
    </div> <!-- /committee-updates-right-infobox -->
  </div></div> <!-- /node-inner, /node -->

<?php 
// FULL NODE -- NOT NEEDED, BECAUSE ALL COMMITTEE UPDATE VIEWS SHOW TEASERS
endif; ?>