(function($){
  Drupal.behaviors.bosa_attendees = {
    attach: function(context, settings){
      $("[id*='name-1-reuse']").each(function(){
        $checkbox = $(this);
        if($checkbox.attr('checked')){
          $checkbox.parent().parent().find("[id$='name-1']").attr('readonly', true);
        }
      });

      $("#edit-customer-profile-billing-commerce-customer-address-und-0-name-line").bind('keyup', function(){
        $("[id*='edit-bosa-attendees-'][readonly]").val($(this).val());
      });

      $("[id*='name-1-reuse']").bind('click', function(){
        $checkbox = $(this);
        if($checkbox.attr('checked')){
          $checkbox.parent().parent().find("[id$='name-1']").attr('readonly', true);
        }
        else {
          $checkbox.parent().parent().find("[id$='name-1']").attr('readonly', false);
        }
      });
    }
  };
}(jQuery));
