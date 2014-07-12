(function ($) {

  var $masthead2014 = $('.mast-head-2014 .background'),
      $mastheadtitle2014 = $('.mast-head-2014 .text'),
      $logo2014 = $('.logo2014'),
      $body = $(document),
      $bodyHeight = $body.height();
  
  $(window).scroll(function () {
  
      var scrollTopValue = $body.scrollTop(),
          scrollTopDivBodyHeight = scrollTopValue / $bodyHeight;
          
      if(scrollTopValue <= 0){
        
        var mastBlur = -(scrollTopValue * 0.3)+'px';
        
        var titleSize = 1 + -(scrollTopValue * 0.01);
        
        var logoSize = (223 - (scrollTopValue * 0.9));
        var logoLeft = (20 + (scrollTopValue * 0.5));
        
        console.log(logoLeft);
        
        $masthead2014.css({
          'background-size': (100 - (scrollTopValue * 0.5)) + '%',
          '-webkit-filter': 'blur(' + mastBlur + ')',
          '-moz-filter': 'blur(' + mastBlur + ')',
          '-o-filter': 'blur(' + mastBlur + ')',
          '-ms-filter': 'blur(' + mastBlur + ')',
          'filter': 'blur(' + mastBlur + ')'
        });
        
        $mastheadtitle2014.css({
          'font-size': titleSize + 'em',
        });
        
        $logo2014.css({
          'background-size': logoSize + 'px',
          'width': logoSize + 12 + 'px',
          'height': logoSize + 12 + 'px',
          'left': logoLeft + 'px'
        }); 
      }     
  });
})(jQuery);
