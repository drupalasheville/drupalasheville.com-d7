(function($) {
  /**
   * Enable the payment method select element.
   */
  Drupal.behaviors.PaymentMethodSelector = {
    attach: function(context) {
	    $('#payment-method-pmid').attr('disabled', false);
    }
  }
})(jQuery);