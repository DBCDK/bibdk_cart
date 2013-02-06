(function ($) {

    /** Insert adhl results */
    Drupal.addRecommendation = function (adhl) {
        if (adhl.error)
            $('.recommendation-load[data-pid=' + adhl.pid + ']').replaceWith(adhl.error);
        if (adhl.list)
            $('.recommendation-load[data-pid=' + adhl.pid + ']').replaceWith(adhl.list);
            $('.recommendation-more[data-pid=' + adhl.pid + ']').removeClass('visuallyhidden')
    },
        Drupal.loadRecommendation = function (element) {
            var pid = $(element).attr('data-pid');
            /* Add throbber*/
            $(element).addClass('ajax-progress');
            $(element).html('<span class="throbber">&nbsp;</span>');

            /* Call ajax */
            var request = $.ajax({
                url:Drupal.settings.basePath + 'cart/ajax',
                type:'POST',
                data:{
                    pid:pid,
                    more:'true'
                },
                dataType:'json',
                success:Drupal.addRecommendation
            });
        }
    /** Get holdingstatus via ajax */
    Drupal.behaviors.recommendation = {

        attach:function (context) {
            $('.recommendation-load', context).each(function (i, element) {
                Drupal.loadRecommendation(element);
            });
        },
        detach:function (context) {

        }
    };

}(jQuery));

