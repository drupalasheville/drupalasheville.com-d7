/**
 * @file
 * Ticket type remove script.
 */

(function ($) {
  Drupal.behaviors.ticketTypeRemove = {

    attach: function(context, settings) {
      // Remove the click events.
      var events = $(".field-widget-ticket-type input[name$='_remove_button']").data('events');
      $(".field-widget-ticket-type input[name$='_remove_button']").unbind('click');
      // Insert a confirmation.
      $(".field-widget-ticket-type input[name$='_remove_button']").click(function(event) {
        if (confirm('Removing this ticket type will delete all associated registrations. Are you sure you want to remove it?')) {
          // Run the original events.
          $.each(events.click, function() {
            this.handler();
          });
        }
        else {
          // Prevent other events.
          event.stopImmediatePropagation();
          event.preventDefault();
        }
      });
    }

  };
}(jQuery));
