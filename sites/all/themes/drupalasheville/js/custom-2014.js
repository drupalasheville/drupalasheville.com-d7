(function ($) {

  var $masthead2014 = $('.mast-head-2014 .background'),
      $mastheadtitle2014 = $('.mast-head-2014 .title2014'),
      $logo2014 = $('.logo2014'),
      $body = $(document),
      $bodyHeight = $body.height();
  
  $(window).scroll(function () {
  
      var scrollTopValue = $body.scrollTop(),
          scrollTopDivBodyHeight = scrollTopValue / $bodyHeight;
          
      if(scrollTopValue <= 0){
        
        var mastBlur = -(scrollTopValue * 0.3)+'px';
        
        var titleSize = 3 + -(scrollTopValue * 0.01);
        
        var logoSize = (223 - (scrollTopValue * 0.9)) + 'px';
        
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
          'padding-left': logoSize
        });
        
        $logo2014.css({
          'background-size': logoSize,
          'width': logoSize,
          'height': logoSize
        });
        
      }
      
      
      
          
          
          
  });

  $(document).ready(function(){

    

  });
})(jQuery);