<?php

/**
 * @file
 * Default rule configurations for Checkout.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rooms_notification_default_rules_configuration() {
  // Store the customer profile entity info for use in default rules.
  $customer_profile_entity_info = entity_get_info('commerce_customer_profile');

  $rules = array();

  // Add a reaction rule to send order e-mail upon checkout completion.
  $rule = rules_reaction_rule();

  $rule->label = t('Send an order notification to site-mail with Booking and Customer details.');
  $rule->tags = array('Commerce Checkout');
  $rule->active = TRUE;

  $rule
    ->event('commerce_checkout_complete')
    ->action('mail', array(
      'to:select' => 'site:mail',
      'subject' => t('Order [commerce-order:order-number] at [site:name]'),
      'message' => t("There is an new order [commerce-order:order-number] at [site:name].\n\nBooking Details :\n\n[commerce-order:rooms-order-details]\n\nCustomer Details : \n\n- Name : [commerce-order:rooms-order-customer-name]\n- Country : [commerce-order:rooms-order-customer-country]\n- Location : [commerce-order:rooms-order-customer-location]\n- Postal Code : [commerce-order:rooms-order-customer-postal-code]\n- Thoroughfare : [commerce-order:rooms-order-customer-thoroughfare]\n- Administrative Area : [commerce-order:rooms-order-customer-administrative-area]\n\nYou can find the status of the order and further info at:\n\n[commerce-order:customer-url]\n\n"),
      'from' => '',
    ));

  // Adjust the weight so this rule executes after the order has been updated to
  // the proper user account.
  $rule->weight = 4;

  $rules['rooms_email_notification'] = $rule;

  return $rules;
}
