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
  //// FRONT PAGE TABBED BLOCK NODES : HAPPENING NOW... BLOCK
  $flag = flag_get_flag('suppress_featured_image') or die('no "suppress_featured_image" flag defined');
  if ($teaser): ?>
    <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
      <div class="node-inner">

        <h3 class="title">
          <?php print l($node->title, 'node/'.$node->nid); ?>
        </h3>

        <?php if ($unpublished): ?>
          <div class="unpublished"><?php print t('Unpublished'); ?></div>
        <?php endif; ?>

        <?php if ($submitted): ?><!-- don't show terms in teaser view -->
          <div class="meta">
            <?php if ($submitted): ?>
              <div class="submitted">
                <?php print $submitted; ?>
              </div>
            <?php endif; ?>
          </div>
        <?php endif; ?>

        <div class="content">

          <?php if (!($flag->is_flagged($node->nid)) && $node->field_feature_image['0']['filepath']):?>
          <div class="featured_image">
              <?php
            print theme('imagecache', 'teaser_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
            ?>
          </div>
          <?php endif; ?>

          <?php print theme('nyss_misc_clean_markup', $node, $content); ?>
          <?php print l(t('Read more...'), 'node/' . $node->nid); ?>
        </div>

        <?php if ($links): ?>
          <?php print $links; ?>
        <?php endif; ?>

    </div>
  </div> <!-- /node-inner, /node -->

  <?php else: ?>
  <?php // FULL NODE ?>
    <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
      <div class="node-inner">
        <?php 
          $relationships = theme('nyss_misc_node_relationships', $node, array('senator', 'district', 'initiative', 'issue'));
          if ($submitted || $terms || $relationships): ?>
          <div class="meta">
            <?php if ($terms || $relationships): ?>
              <div class="terms">
                <?php
                  print $relationships;
                  $terms = str_replace('<label>Issues</label>', '<label>' . t('Related issues') . ': </label>', $terms);
                  print $terms; ?>
              </div>
            <?php endif; ?>
          </div>
        <?php endif; ?>

        <div class="share_links">
          <div class="inner">
            <h3><?php print t('Share This:'); ?></h3>
            <?php print $service_links ?>
          </div>
        </div>

        <div class="content">
          <?php if (!($flag->is_flagged($node->nid)) && $node->field_feature_image['0']['filepath']):?>
            <?php print l(theme('imagecache', 'full_node_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']), $node->field_feature_image[0]['data']['url'], array('html'=>'true')); ?>
            <?php print $field_feature_image_rendered; ?>
          <?php endif; ?>
          <?php print $content; ?>
          <?php print $field_video_rendered; ?>
        </div>

        <?php if ($links): ?>
          <?php print $links; ?>
        <?php endif; ?>

      </div>
    </div> <!-- /node-inner, /node -->
  <?php endif; ?>
