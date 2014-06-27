(function($) {

/**
 * Provide a Drupal-specific wrapper for JUSH Framework.
 */
Drupal.behaviors.bootstrap_affix = {
  attach: function(context, settings) {
	    $('#myAffix').affix({
		    offset: {
		       top: Drupal.settings.offset_top
		      ,bottom: Drupal.settings.offset_bottom
		  }
		});
	}
}

})(jQuery)
