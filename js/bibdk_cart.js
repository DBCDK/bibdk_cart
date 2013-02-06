(function ($) {

    Drupal.cartResponse = function (data) {
        console.log(data);
        if (data.saved) {
            $('.link-add-basket[data-pid=' + data.pid + ']').text(Drupal.t('remove_item_from_cart', null, null));
        } else {
            $('.link-add-basket[data-pid=' + data.pid + ']').text(Drupal.t('add_item_to_cart', null, null));
        }
    }

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
    }


    Drupal.behaviors.cart = {
        attach:function (context) {
            $('.link-add-basket', context).click(function () {
                Drupal.addRemoveItem($(this));
            });
        }
    }
}(jQuery));
