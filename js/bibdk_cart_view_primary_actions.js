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
        } else {
            deleteAllBtn.addClass('inactive');
        }
    };

    Drupal.behaviors.cart = {
        attach:function (context) {
            $('.cart-view-mark-all', context).click(function (e) {
                e.preventDefault();
                Drupal.deSelectAll();
            });
            $('.table input[type=checkbox]', context).click(function () {
                Drupal.deActivateDeleteAllBtn();
            });
        }
    };
}(jQuery));
