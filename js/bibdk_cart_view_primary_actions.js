(function ($) {
    Drupal.deSelectAll = function () {
        var element = $('.table input[type=checkbox]');
        var items = element.length;
        var selected = 0;

        element.each(function () {
            if (this.checked) {
                selected++;
            }
        });

        if (selected === items) {
            element.each(function () {
                this.checked = false;
            });
        } else {
            element.each(function () {
                this.checked = true;
            });
        }
        Drupal.deActivateDeleteAllBtn();
    };

    Drupal.deActivateDeleteAllBtn = function () {
        var selected = 0;
        var element = $('.table input[type=checkbox]');
        var deleteAllBtn = $('.cart-view-delete-selected');
        element.each(function () {
            if (this.checked) {
                selected++;
            }
        });

        if (selected !== 0) {
            deleteAllBtn.removeClass('inactive');
            $('.cart-action-btn').removeClass('inactive');
        } else {
            deleteAllBtn.addClass('inactive');
            $('.cart-action-btn').addClass('inactive');
        }
    };

    Drupal.deleteSelected = function () {
        var element = $('.table input[type=checkbox]');

        var items = [];
        var elements = [];

        element.each(function () {
            if (this.checked) {
                items.push(this.value);
                elements.push(this);
                this.checked = false;
            }
        });
        $('.cart-view-delete-selected').addClass('inactive');

        $.ajax({
            url:Drupal.settings.basePath + 'cart/ajax/deleteitems',
            type:'POST',
            data:{
                pids:items
            },
            dataType:'json',
            success:function (data) {
                if(data.error){
                    alert(Drupal.t('error_please_refresh_page_and_try_again', null, {context:'bibdk_cart'}));
                } else {
                    $('.cart-view-delete-selected').removeClass('ajax-progress');
                    $('.cart-view-delete-selected').text(Drupal.t('delete_selected', null, {context:'bibdk_cart'}));
                    elements.forEach(function(element) {
                        $(element).closest('tr').remove();
                    });

                    $('.cartcount').text(data.cartcount);
                }
            }
        });
    };

    Drupal.behaviors.cart = {
        attach:function (context) {
            $('.cart-view-mark-all', context).click(function (e) {
                e.preventDefault();
                Drupal.deSelectAll();
            });

            $('.table input[type=checkbox]', context).click(function (e) {
                Drupal.deActivateDeleteAllBtn();
            });

            $('.cart-view-delete-selected', context).click(function (e) {
                e.preventDefault();
                if ($(this).hasClass('inactive')) {
                    return false;
                } else {
                    Drupal.deleteSelected();
                    $(this).addClass('ajax-progress');
                    $(this).html('<span class="throbber">&nbsp;</span>');
                    return false;
                }
            });
        }
    };
}(jQuery));
