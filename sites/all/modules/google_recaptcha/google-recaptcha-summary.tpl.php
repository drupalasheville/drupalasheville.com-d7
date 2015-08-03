<?php

/**
 * @file
 *  for "Summary" admin page.
 *
 * Available variables
 * - $public_key: Google reCAPTCHA public key
 * - $secret_key: Google reCAPTCHA secret key
 * - $statistics['status']: Is statistics collects or not
 * - $statistics['requests']: Count of all requests to Google servers
 * - $statistics['success']: Count correct filled reCAPTCHA
 * - $statistics['fails']: Count incorrect filled (or not filled) reCAPTCHA
 */
?>

<p>
<b><?php print t('Public key'); ?>:</b> <?php print empty($public_key) ? t('It seems that You are not define Google reCAPTCHA public key for this site yet. You can do it <a href="@administer-page-for-defining-google-recaptcha-keys">here >></a>', array('@administer-page-for-defining-google-recaptcha-keys' => '/admin/config/spam_protection/google_recaptcha/keys')) : $public_key ?><br/>
<b><?php print t('Secret key'); ?>:</b> <?php print empty($public_key) ? t('It seems that You are not define Google reCAPTCHA secret key for this site yet. You can do it <a href="@administer-page-for-defining-google-recaptcha-keys">here >></a>', array('@administer-page-for-defining-google-recaptcha-keys' => '/admin/config/spam_protection/google_recaptcha/keys')) : $secret_key ?>
</p>

<?php if ($statistics['status'] == 1): ?>
    <h2><?php print t('Statistics') ?></h2>
    <p><?php print t('Requests: @count', array('@count' => $statistics['requests'])); ?><br/>
    <?php print t('Responses: @count', array('@count' => $statistics['success'] + $statistics['fails'])); ?><br/>
    <?php print t('Success: @count', array('@count' => $statistics['success'])); ?><br/>
    <?php print t('Fails: @count', array('@count' => $statistics['fails'])); ?></p>
    <div class="description"><?php print t('
        <em>Description.</em> Every request to Google server will increment these values appropriately.<br/>
        "Requests" is equal protected form submissions.<br/>
        "Success" is equal correct filled reCAPTCHA and "fails" is equal incorrect filled (or not filled) reCAPTCHA.<br/>
        "Responses" - this count of all answers from Google servers (sum of "success" and "fails").
    '); ?></div>
<?php endif; ?>

<h2><?php print t('Help'); ?></h2>
<p><?php print t('To create public and secret keys for this site and get exhaustive information about how Google reCAPTCHA service work You may on the <a href="@google-recaptcha-official-site" target="_blank">official site</a>.', array('@google-recaptcha-official-site' => 'https://www.google.com/recaptcha')); ?></p>




