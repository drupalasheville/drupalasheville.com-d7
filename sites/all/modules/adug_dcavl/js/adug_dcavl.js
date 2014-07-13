/**
 * @file
 * Documentation missing.
 */

(function ($) {
    Drupal.behaviors.adug_dcavl = {
        attach: function (context, settings) {

            $("#edit-ticket-registrant input[type='text']").focusout(function() {
                if ($(this).val() != '') {
                    var sourceID = $(this).attr('id');
                    var sourceVal = $(this).val();
                    var destID = '';
                    if (sourceID == 'edit-ticket-registrant-ticket-user-registrant-email') {
                        destID = 'edit-ticket-registrationnew-0-ticket-user-registration-email0';
                    }
                    if (sourceID == 'edit-ticket-registrant-field-profile-first-und-0-value') {
                        destID = 'edit-ticket-registrationnew-0-field-profile-first-und-0-value';
                    }
                    if (sourceID == 'edit-ticket-registrant-field-profile-last-und-0-value') {
                        destID = 'edit-ticket-registrationnew-0-field-profile-last-und-0-value';
                    }
                    if (destID != '') {
                        $('#'+destID).val(sourceVal);
                    }

                }
            })

            var link = '<a href="#" class="location-types-clear">Clear</a>';
            // Add clear button
            if ($('.location-types-clear').length == 0) {
                $("#edit-field-location-type-tid-wrapper label[for='edit-field-location-type-tid']").after(' (' + link + ')');
            }
            // Make clear button work
            $('a.location-types-clear').click(function() {
                event.preventDefault();
                event.stopPropagation();
                // Unselect all the checkboxes
                $(this)
                    .siblings('.views-widget')
                    .find('.form-item input:checkbox').each(function() {
                        $(this).attr('checked', false);
                    })
                    .end()

                    // attr() doesn't trigger a change event, so we do it ourselves. But just on
                    // one checkbox otherwise we have many spinning cursors
                    .find('input[type=checkbox]:first').change()
                ;
            })
        }
    };
}(jQuery));
