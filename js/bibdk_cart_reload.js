(function ($) {
    Drupal.behaviors.updateCart = {
        attach: function(context){
            $(window).unload(function(){
                window.opener.location.reload(false);
            });
        }
    }
}(jQuery));
