(function ($) {

    Drupal.cartResponse = function (data) {
        if(data.error){
            alert(Drupal.t('error_refresh_page_and_try_again', null, null));
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
    };

    Drupal.addRemoveItem = function (element) {
        var pid = $(element).attr('data-pid');
        /* Add throbber*/
        $(element).addClass('ajax-progress');
        $(element).html('<span class="throbber">&nbsp;</span>');

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
        $('.cartcount').text(cartcount);
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
        }
    };
}(jQuery));
