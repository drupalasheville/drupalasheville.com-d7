<?php
/**
 * @file
 * Template for default Bootopoly Brown.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display brown clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <?php if ($content['slider'] || $content['slidergutter']) : ?>
    <div class="row">
      <div class="col-md-8 slider panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['slider']; ?>
        </div>
      </div>
      <div class="col-md-4 sidebar-gutter panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['slidergutter']; ?>
        </div>
      </div>
    </div>
  <?php endif; ?>
  <div class="row">
    <div class="col-md-4 column1 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['column1']; ?>
      </div>
    </div>
    <div class="col-md-4 column2 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['column2']; ?>
      </div>
    </div>
    <div class="col-md-4 column3 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['column3']; ?>
      </div>
    </div>
  </div>
  <?php if ($content['footercolumn1'] || $content['footercolumn2'] || $content['footercolumn3']) : ?>
  <div class="row">
    <div class="col-md-4 footer-column1 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['footercolumn1']; ?>
      </div>
    </div>
    <div class="col-md-4 footer-column2 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['footercolumn2']; ?>
      </div>
    </div>
    <div class="col-md-4 footer-column3 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['footercolumn3']; ?>
      </div>
    </div>
</div><!-- /.brown -->
