jQuery(function($) {
    var asg_priceNoticeTimout = [];
	$('.asg_price_timestamp_detail').hover(
        function() {
            clearTimeout(asg_priceNoticeTimout[$(this).attr('data-id')]);

            var $this = $(this);
            var $tooltip = $('.asg_price_timestamp_detail-text', this);
            var $window = $(window);
            var offset = $this.offset();

            $tooltip.css('left', offset.left - $window.scrollLeft())
                .css('top', offset.top + $this.height() - $window.scrollTop())
                .fadeIn()
                .css('display', 'block');
        },
        function() {
            asg_priceNoticeTimout[$(this).attr('data-id')] = setTimeout('jQuery("#' + this.id + ' .asg_price_timestamp_detail-text").fadeOut();', 1000);
            //$('.asg_price_timestamp_detail-text', this).fadeOut('slow');
        }
    );

    $('.asg-vid-item').click(function(event) {
        event.preventDefault();
        $(this).closest('.asg-vid-playlist').find('.asg-vid-iframe')
            .attr('src', $(this).attr('data-src'));
    });
    $('.asg-arrow-right').click(function (event) {
        event.preventDefault();
        $(this).closest('.asg-vid-playlist').find('.asg-vid-list-container')
            .stop()
            .animate({
                scrollLeft: '+=336'
            }, 750);
    });
    $('.asg-arrow-left').click(function (event) {
        event.preventDefault();
        $(this).closest('.asg-vid-playlist').find('.asg-vid-list-container')
            .stop()
            .animate({
                scrollLeft: '-=336'
            }, 750);
    });
});