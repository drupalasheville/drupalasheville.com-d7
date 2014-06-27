<div class="bootstrap-panel panel <?php print (isset($settings['context_class'])) ? $settings['context_class'] : 'panel-default'; ?>">
	<?php if (!empty($settings['region_title'])): ?>
		<div class="pane-title panel-heading">
			<?php ($settings['use_title']) ? print "<h3 class='panel-title'>" . $settings['region_title'] . "</h3>" : print "<h3>" . $settings['region_title'] . "</h3>"; ?>
		</div>
	<?php endif ?>
	<?php if ($settings['panel_body']): ?>
		<div class="pane-content panel-body">
			<?php print render($content); ?>
		</div>
	<?php else: ?>
		<?php print render($content); ?>
	<?php endif ?>
	<?php if ($settings['use_footer']): ?>
		<div class="panel-footer">
			<?php (!empty($settings['footer_content'])) ? print $settings['footer_content'] : ''; ?>
		</div>
	<?php endif ?>
</div>