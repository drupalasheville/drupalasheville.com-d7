(function($) {
  /**
   * Refresh this window's opener's payment references.
   */
  $(document).ready(function() {
    if (window.opener && window.opener.Drupal.PaymentreferenceRefreshButtons) {
      window.opener.Drupal.PaymentreferenceRefreshButtons();
    }
  });

  /**
   * Convert "close this window" messages to links.
   */
  Drupal.behaviors.PaymentreferenceWindowCloseLink = {
    attach: function(context) {
      $('span.paymentreference-window-close').each(function() {
        $(this).replaceWith('<a href="#" class="paymentreference-window-close">' + this.innerHTML + '</a>');
      });
      $('a.paymentreference-window-close').bind('click', function() {
        window.opener.focus();
        window.close();
      });
    }
  }

  /**
   * Refresh all payment references.
   */
  Drupal.PaymentreferenceRefreshButtons = function() {
    $('.paymentreference-refresh-button').each(function() {
      if (!Drupal.settings.PaymentreferencePaymentAvailable[Drupal.settings.ajax[this.id].wrapper]) {
        $(this).trigger('mousedown');
      }
    });
  }

  /**
   * Set an interval to refresh all payment references.
   */
  setInterval(Drupal.PaymentreferenceRefreshButtons, 30000);
})(jQuery);