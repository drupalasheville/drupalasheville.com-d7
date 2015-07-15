COMMERCE STRIPE
---------------

Commerce Stripe integrates Stripe with Drupal Commerce payment and checkout
system. This module will fully integrate the Stripe to Drupal Commerce in
that way that clients can make payments straight in the shop in PCI-compliant
way without leaving the actual shop page. Stripe is a simple way to accept
payments online. With Stripe you can accept Visa, MasterCard, American Express,
Discover, JCB, and Diners Club cards directly on your store.


INSTALLING COMMERCE STRIPE MODULE
-------------------------------------

1. Download latest module from http://drupal.org/project/commerce_stripe

2. Download Libraries module from http://drupal.org/project/libraries

3. Enable Commerce Stripe and Libraries modules as usual: /admin/modules

4. Download Stripe library from https://github.com/stripe/stripe-php and
   extract it to sites/all/libraries/stripe-php
   NOTE: you must use stripe-php version 1.17.1 or higher for the Commerce Card On File integration to work.


CONFIGURING PAYMENT METHOD
--------------------------

1. Create an account at https://stripe.com/

2. Insert your API keys at the Stripe configuration page
   admin/commerce/config/payment-methods/manage/commerce_payment_commerce_stripe
   Remember to test the functionality with the test keys before going live!


CREDITS
-------

Commerce Stripe integration has been written by:

Ilari Mäkelä - https://drupal.org/user/726092
Avi Goldberg - https://drupal.org/user/2565920
