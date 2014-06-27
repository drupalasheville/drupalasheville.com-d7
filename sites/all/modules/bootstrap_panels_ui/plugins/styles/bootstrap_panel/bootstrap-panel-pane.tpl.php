<div class="bootstrap-panel panel <?php print (isset($settings['context_class'])) ? $settings['context_class'] : 'panel-default'; ?>">
<?php if (isset($content->title)): ?>
	<div class="pane-title panel-heading">
		<?php ($settings['use_title']) ? print "<h3 class='panel-title'>" . $content->title . "</h3>" : print "<h3>" . $content->title . "</h3>"; ?>
	</div>
<?php endif ?>
	<?php if ($settings['panel_body']): ?>
	<div class="pane-content panel-body">
	<?php endif ?>
		<?php print render($content->content); ?>
	<?php if ($settings['panel_body']): ?>
		</div>
	<?php endif ?>
	<?php if ($settings['use_footer']): ?>
		<div class="panel-footer">
			<?php (isset($settings['footer_content'])) ? print $settings['footer_content'] : ''; ?>
		</div>
	<?php endif ?>
</div>