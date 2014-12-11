
/**
 * @file
 * This file contains the jquery functions.
 * functionality of select-all/clear-all option for checkboxes.
 */

/**
 * This function adds option for select all/clear all checkboxes.
 */
// Register some functions with the drupal abstraction of jquery
Drupal.behaviors.export_roles_permissions= function (context)  {
  var select_link = '<a href="javacript:void(0);" class="op_select_all">Select all</a> | ';
  var clear_link = '<a href="javacript:void(0);"  class="op_clear_all">Clear all</a>';
  $('.checkbox-bulk-operation').each(function () {
    var element = $(this);
    $(this).prepend(clear_link);
    $('.op_clear_all', element).click(function(event){
      $('input[type=checkbox]', element).each(function() {
        this.checked = false;
      })
    });
    $(this).prepend(select_link);
    $('.op_select_all', element).click(function(){
      $('input[type=checkbox]', element).each(function() {
        this.checked = true;
      })
    });
  });
};
