// $Id$
(function($)
{
var LiveChat =
{
	i18n: {},

	init: function()
	{
		this.i18n();
		this.externalLinks();
		this.toggleForms();
		this.bindFormSubmit();
	},

	i18n: function()
	{
		this.i18n.edit_submit = $('#edit-submit').attr('value');
	},

	externalLinks: function()
	{
		$("#livechat-admin-settings-form a[href^=http]").each(function()
		{
			if(this.href.indexOf(location.hostname) == -1)
			{
				$(this).attr('target', '_blank');
			}
		});
	},

	toggleForms: function()
	{
		var toggleForms = function()
		{
			if ($('#choose_form_0').is(':checked'))
			{
				$('#livechat_already_have').hide();
				$('#livechat_new_account').show();
				$('#edit-name').focus();

				// Update submit button value
				$('#edit-submit').attr('value', 'Create account');
			}
			else if ($('#choose_form_1').is(':checked'))
			{
				$('#livechat_new_account').hide();
				$('#livechat_already_have').show();
				$('#edit-livechat-login').focus();

				// Restore default submit button value
				$('#edit-submit').attr('value', LiveChat.i18n.edit_submit);
			}
			else
			{
				$('#edit-submit').attr('value', 'Reset settings');
			}
		};

		toggleForms();
		$('#choose_form input').click(toggleForms);
	},

	bindFormSubmit: function()
	{
		$('#livechat-admin-settings-form').submit(function()
		{
			if (parseInt($('input[name=license_number]').val()) !== 0 || $('#choose_form_1').is(':checked'))
			{
				return LiveChat.alreadyHaveAccountForm();
			}
			else
			{
				return LiveChat.newLicenseForm();
			}
		});
	},

	alreadyHaveAccountForm: function()
	{
		if (parseInt($('input[name=license_number]').val()) == 0)
		{
			var login = $.trim($('#edit-livechat-login').val());
			if (!login.length)
			{
				$('#edit-livechat-login').focus();
				return false;
			}

			$('#livechat_already_have .ajax_message').removeClass('message').addClass('wait').html('Please wait&hellip;');

			$.getJSON('https://api.livechatinc.com/license/number/'+login+'?callback=?', function(response)
			{
				if (response.error)
				{
					$('#livechat_already_have .ajax_message').removeClass('wait').addClass('message').html('Incorrect LiveChat login.');
					$('#edit-livechat-login').focus();
					return false;
				}
				else
				{
					$('input[name=license_number]').val(response.number);
					$('#livechat-admin-settings-form').submit();
				}
			});

			return false;
		}

		return true;
	},

	newLicenseForm: function()
	{
		if (parseInt($('input[name=license_number]').val()) > 0)
		{
			return true;
		}

		if (this.validateNewLicenseForm())
		{
			$('#livechat_new_account .ajax_message').removeClass('message').addClass('wait').html('Please wait&hellip;');

			// Check if email address is available
			$.getJSON('http://www.livechatinc.com/php/licence_info.php?email='+$('#edit-email').val()+'&jsoncallback=?',
			function(response)
			{
				if (response.response == 'true')
				{
					LiveChat.createLicense();
				}
				else if (response.response == 'false')
				{
					$('#livechat_new_account .ajax_message').removeClass('wait').addClass('message').html('This email address is already in use. Please choose another e-mail address.');
					$('#edit-email').focus();
				}
				else
				{
					$('#livechat_new_account .ajax_message').removeClass('wait').addClass('message').html('Could not create account. Please try again later.');
				}
			});
		}

		return false;
	},

	getWebsite: function()
	{
		return location.href.replace(/admin\/settings\/.*/, '');
	},

	createLicense: function()
	{
		var url;

		$('#livechat_new_account .ajax_message').removeClass('message').addClass('wait').html('Creating new account&hellip;');

		url = 'https://www.livechatinc.com/signup/';
		url += '?name='+encodeURIComponent($('#edit-name').val());
		url += '&email='+encodeURIComponent($('#edit-email').val());
		url += '&password='+encodeURIComponent($('#edit-password').val());
		url += '&website='+encodeURIComponent(this.getWebsite());
		url += '&timezone_gmt='+encodeURIComponent(this.calculateGMT());
		url += '&action=drupal_signup';
		url += '&jsoncallback=?';

		$.getJSON(url, function(data)
		{
			data = parseInt(data.response);
			if (data == 0)
			{
				$('#livechat_new_account .ajax_message').html('Could not create account. Please try again later.').addClass('message').removeClass('wait');
				return false;
			}

			// save new licence number
			$('input[name=license_number]').val(data);
			$('#livechat-admin-settings-form').submit();
		});
	},

	validateNewLicenseForm: function()
	{
		if ($('#edit-name').val().length < 1) {
			alert ('Please enter your full name.');
			$('#edit-name').focus();
			return false;
		}

		if (/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,6}$/i.test($('#edit-email').val()) == false) {
		  alert ('Please enter a valid email address.');
		  $('#edit-email').focus();
		  return false;
		}

		if ($.trim($('#edit-password').val()).length < 6)
		{
			alert('Password must be at least 6 characters long');
			$('#edit-password').focus();
			return false;
		}

		if ($('#edit-password').val() !== $('#edit-password-retype').val())
		{
			alert('Both passwords do not match.');
			$('#edit-password').val('');
			$('#edit-password-retype').val('');
			$('#edit-password').focus();
			return false;
		}

		return true;
	},

	calculateGMT: function()
	{
		var date, dateGMTString, date2, gmt;

		date = new Date((new Date()).getFullYear(), 0, 1, 0, 0, 0, 0);
		dateGMTString = date.toGMTString();
		date2 = new Date(dateGMTString.substring(0, dateGMTString.lastIndexOf(" ")-1));
		gmt = ((date - date2) / (1000 * 60 * 60)).toString();

		return gmt;
	}
};

$(document).ready(function()
{
	LiveChat.init();
});

})(jQuery);