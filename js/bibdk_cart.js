(function ($) {

    var checkbox;

  Drupal.cartResponse = function (data) {
        if(data.error){
            alert(Drupal.t('error_refresh_page_and_try_again', {}, {context:'bibdk_cart:error'}));
        }

        if (data.saved === 1) {
            $('.link-add-basket[data-pid=' + data.pid + ']').text(Drupal.t('remove_item_from_cart', {}, {context:'bibdk_cart'}));
        } else {
            $('.link-add-basket[data-pid=' + data.pid + ']').text(Drupal.t('add_item_to_cart', {}, {context:'bibdk_cart'}));
            Drupal.updateCartview(data.classid);
        }

        if (data.cartcount) {
            Drupal.updateCartcount(data.cartcount);
        }

    Drupal.setCheckboxState(data);
    };

  Drupal.setCheckboxState = function(data){
    if(checkbox !== null){
      if(data.saved === 1){
        $(checkbox).attr('checked', true);
      } else {
        $(checkbox).attr('checked', false);
      }
      $(checkbox).removeAttr('disabled');
      checkbox = null;
    }
  };

    Drupal.addRemoveItem = function (element) {
        var pid = $(element).attr('data-pid');
        /* Add throbber*/
        $(element).addClass('ajax-progress');
        $(element).html('<span class="throbber">&nbsp;</span>');

      Drupal.doUpdateCart(pid);
    };

  Drupal.addRemoveItemCheckbox = function(element){
    //var elem = $(element);
    checkbox = element;
    $(element).attr('disabled','disabled');
    var pid = $(element).attr('data-pid');

    Drupal.doUpdateCart(pid);
  };

  Drupal.doUpdateCart = function(pid){
    var request = $.ajax({
      url:Drupal.settings.basePath + 'cart/ajax',
      type:'POST',
      data:{
        pid:pid
      },
      dataType:'json',
      success:Drupal.cartResponse
    });
  };

    Drupal.updateCartcount = function (cartcount) {
        var text = Drupal.formatPlural(cartcount, '1 item in cart', '@count items in cart');
        $('.cartcount').text(text);
    };

    Drupal.updateCartview = function (id) {
        var cid = '.cart-item-id-' + id;
        $(cid).remove();
    };

    Drupal.behaviors.cart = {
        attach:function (context) {
            $('.link-add-basket', context).click(function () {
                Drupal.addRemoveItem($(this));
            });

            $('.cart-checkbox', context).click(function(){
              Drupal.addRemoveItemCheckbox($(this));
            });
        }
    };
}(jQuery));
