<?php
/**
 * Implements base_settings_form()
 */
function bosa_attendees_pane_settings_form($checkout_pane) {
  $form = array();
  return $form;
}

/**
 * Implements base_checkout_form()
 */
function bosa_attendees_pane_checkout_form($form, $form_state, $checkout_pane, $order) {
  $checkout_form = array();
  $line_item_ids = array();

  // Loop over line_items and check if they require attendee names.
  if($order->commerce_line_items){
    foreach($order->commerce_line_items[LANGUAGE_NONE] as $key => $line_item){
      if(_bosa_attendees_lineitem_needs_attendees($line_item['line_item_id'])){
        $line_item_ids[] = $line_item['line_item_id'];
      }
    }
  }

  error_log(print_r($line_item_ids, 1));

  // Build form for line_items
  // If there are any line_items that require names
  if(!empty($line_item_ids)){
    foreach($line_item_ids as $line_item_id){
      $checkout_form[$line_item_id] = array_shift(bosa_attendees_get_form_for_lineitem($line_item_id));
    }
  }

  return $checkout_form;
}

/**
 * Implements base_checkout_form_submit()
 */
function bosa_attendees_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  foreach($form_state['values']['bosa_attendees'] as $line_item_id => $attendees){
    $line_item = commerce_line_item_load($line_item_id);
    // Use entity_metadata_wrapper to set attendees on line_item,
    // tried with commerce_save on the obj, but didnt always work !?
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

    $line_item_wrapper->field_bosa_attendees_list->set(serialize($attendees));
    $line_item_wrapper->save();;
  }
}
