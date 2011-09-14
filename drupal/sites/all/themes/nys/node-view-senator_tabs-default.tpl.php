<?php // dpm($node); ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix">
	<div class="node-inner">
	  
	  <h3 class="title">
			<?php print l($node->title, 'node/'.$node->nid); ?>
		</h3>

		<?php if ($unpublished): ?>
			<div class="unpublished"><?php print t('Unpublished'); ?></div>
		<?php endif; ?>

		<?php if ($submitted): ?><!-- don't show terms except when viewing the full node -->
			<div class="meta">
				<?php if ($submitted && in_array($node->type, array('blog', 'report'))): ?>
					<div class="submitted">
					<?php print $submitted; ?>
					</div>
				<?php endif; ?>
			</div>
		<?php endif; ?>

		<div class="content">
			<?php if ($node->field_feature_image['0']['filepath'] && !$node->field_video['0']['view']):?>
				<div class="featured_image">
					<?php
					print theme('imagecache', 'teaser_featured_image', $node->field_feature_image['0']['filepath'], $node->field_feature_image['0']['data']['description'], $node->field_feature_image['0']['data']['description']);
					?>
				</div>
			<?php endif; ?>
			<div class="teaser <?php if ($node->field_video['0']['view']) {print 'with-video';}?>">
			  <?php print $content; ?>
				<?php print l(t('Read more...'), 'node/'.$node->nid, array('attributes' => array('class' => 'read_more')))?>			  
			</div>
		</div>

		<?php if ($links && $user->uid): ?>
			<?php print $links; ?>
		<?php endif; ?>

	</div>
</div> <!-- /node-inner, /node -->
