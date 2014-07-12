/**
 * @file
 * Javascript to generate Stripe token in PCI-compliant way.
 */

(function ($) {
  Drupal.behaviors.stripe = {
    attach: function (context, settings) {
      if (settings.stripe.fetched == null) {
        settings.stripe.fetched = true;

        $('#commerce-checkout-form-checkout #edit-continue, #commerce-checkout-form-review #edit-continue').live('click', function(event) {

          // Prevent the Stripe actions to be triggered if Stripe is not selected.
          if ($('#edit-commerce-payment-payment-method-commerce-stripecommerce-payment-commerce-stripe').is(':checked')) {
            // Do not fetch the token if cardonfile is enabled and the customer has selected an existing card.
            if ($('.form-item-commerce-payment-payment-details-cardonfile').length > 0 &&
              $("input[type='radio'][name='commerce_payment[payment_details][cardonfile]']:checked").val() != 'new') {

              return;
            }

            $(this).addClass('auth-processing');

            // Prevent the form from submitting with the default action.
            event.preventDefault();

            // Show progress animated gif (needed for submitting after first error).
            $('.checkout-processing').show();

            // Disable the submit button to prevent repeated clicks.
            $('.form-submit').attr("disabled", "disabled");

            Stripe.setPublishableKey(settings.stripe.publicKey);

            var cardValues = {
              number: $('[id^=edit-commerce-payment-payment-details-credit-card-number]').val(),
              cvc: $('[id^=edit-commerce-payment-payment-details-credit-card-code]').val(),
              exp_month: $('[id^=edit-commerce-payment-payment-details-credit-card-exp-month]').val(),
              exp_year: $('[id^=edit-commerce-payment-payment-details-credit-card-exp-year]').val(),
              name: $('[id^=edit-commerce-payment-payment-details-credit-card-owner]').val()
            };

            // Check if the optional address fields are present in
            // the form and include them in the token if so.
            var optionalFields = {
              address_line1: 'edit-customer-profile-billing-commerce-customer-address-und-0-thoroughfare',
              address_line2: 'edit-customer-profile-billing-commerce-customer-address-und-0-premise',
              address_ciy: 'edit-customer-profile-billing-commerce-customer-address-und-0-locality',
              address_state: 'edit-customer-profile-billing-commerce-customer-address-und-0-administrative-area',
              address_zip: 'edit-customer-profile-billing-commerce-customer-address-und-0-postal-code',
              address_country: 'edit-customer-profile-billing-commerce-customer-address-und-0-country'
            };

            for (var stripeName in optionalFields) {
              if (optionalFields.hasOwnProperty(stripeName)) {
                var formInputElement = $('[id^=' + optionalFields[stripeName] + ']');
                if (formInputElement) {
                  cardValues[stripeName] = formInputElement.val();
                }
              }
            }

            Stripe.createToken(cardValues, Drupal.behaviors.stripe.stripeResponseHandler);

            // Prevent the form from submitting with the default action.
            return false;
          }
        });
      }
    },

    stripeResponseHandler: function (status, response) {
      if (response.error) {
        $(this).removeClass('auth-processing');

        // Show the errors on the form.
        $("div.payment-errors").html($("<div class='messages error'></div>").html(response.error.message));

        // Enable the submit button to allow resubmission.
        $('.form-submit').removeAttr("disabled");
        // Hide progress animated gif.
        $('.checkout-processing').hide();
      }
      else {
        var form$ = $("#commerce-checkout-form-checkout, #commerce-checkout-form-review");
        // Token contains id, last4, and card type.
        var token = response['id'];
        // Insert the token into the form so it gets submitted to the server.
        form$.append("<input type='hidden' name='stripeToken' value='" + token + "'/>");
        $btnTrigger = $('.form-submit.auth-processing').eq(0);
        var trigger$ = $("<input type='hidden' />").attr('name', $btnTrigger.attr('name')).attr('value', $btnTrigger.attr('value'));
        form$.append(trigger$);

        // And submit.
        form$.get(0).submit();
      }
    }
  }
})(jQuery);
