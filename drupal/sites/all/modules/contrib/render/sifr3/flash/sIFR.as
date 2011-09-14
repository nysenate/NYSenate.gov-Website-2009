/*****************************************************************************
scalable Inman Flash Replacement (sIFR) version 3.

Copyright 2006 – 2008 Mark Wubben, <http://novemberborn.net/>

Older versions:
* IFR by Shaun Inman
* sIFR 1.0 by Mike Davidson, Shaun Inman and Tomas Jogin
* sIFR 2.0 by Mike Davidson, Shaun Inman, Tomas Jogin and Mark Wubben

See also <http://novemberborn.net/sifr3> and <http://wiki.novemberborn.net/sifr3>.

This software is licensed and provided under the CC-GNU LGPL.
See <http://creativecommons.org/licenses/LGPL/2.1/>
*****************************************************************************/

import SifrStyleSheet;
import flash.external.*;

class sIFR {
  public static var DEFAULT_TEXT                 = 'Rendered with sIFR 3, revision 436<br><strong>Rendered with sIFR 3, revision 436</strong><br><em>Rendered with sIFR 3, revision 436</em><br><strong><em>Rendered with sIFR 3, revision 436</em></strong>';
  public static var VERSION_WARNING              = 'Movie (436) is incompatible with sifr.js (%s). Use movie of %s.<br><strong>Movie (436) is incompatible with sifr.js (%s). Use movie of %s.</strong><br><em>Movie (436) is incompatible with sifr.js (%s). Use movie of %s.</em><br><strong><em>Movie (436) is incompatible with sifr.js (%s). Use movie of %s.</em></strong>';
  public static var CSS_ROOT_CLASS               = 'sIFR-root';
  public static var DEFAULT_WIDTH                = 300;
  public static var DEFAULT_HEIGHT               = 100;
  public static var DEFAULT_ANTI_ALIAS_TYPE      = 'advanced';
  public static var MARGIN_LEFT                  = -3;
  public static var PADDING_BOTTOM               = 5; // Extra padding to make sure the movie is high enough in most cases.
  public static var LEADING_REMAINDER            = 2; // Flash uses the specified leading minus 2 as the applied leading, so we increment by 2

  public static var MIN_FONT_SIZE                = 6;
  public static var MAX_FONT_SIZE                = 126;
  // Minimal height of the Flash movie. This height is required in order to detect incorrect Stage height in the
  // scaling calculations. JavaScript sets the size of the Flash movie to 0px by 0px, but at least Opera makes this
  // 1px by 1px. With 1000% page zoom this would get to 10px, but the highest I saw was 8px. Seems safe enough to have
  // the min height at 10px then.
  public static var MIN_HEIGHT                   = 10;
  public static var ALIASING_MAX_FONT_SIZE       = 48;
  public static var VERSION                      = '436';
  
  //= Holds CSS properties and other rendering properties for the Flash movie.
  //  *Don't overwrite!*
  public static var styles:SifrStyleSheet        = new SifrStyleSheet();
  //= Allow sIFR to be run from the filesystem
  public static var fromLocal:Boolean            = true;
  //= Array containing domains for which sIFR may render text. Used to prevent
  //  hotlinking. Use `*` to allow all domains.
  public static var domains:Array                = [];
  //= Whether kerning is enabled by default. This can be overriden from the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002811.html>.
  public static var defaultKerning:Boolean       = true;
  //= Default value which can be overriden from the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002788.html>.
  public static var defaultSharpness:Number      = 0;
  //= Default value which can be overriden from the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002787.html>.
  public static var defaultThickness:Number      = 0;
  //= Default value which can be overriden from the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002732.html>.
  public static var defaultOpacity:Number        = -1; // Use client settings
  //= Default value which can be overriden from the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002788.html>.
  public static var defaultBlendMode:Number      = -1; // Use cliest settings
  //= Overrides the grid fit type as defined on the client side.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002444.html>.
  public static var enforcedGridFitType:String   = null;
  //= If `true` sIFR won't override the anti aliasing set in the Flash IDE when exporting.
  //  Thickness and sharpness won't be affected either.
  public static var preserveAntiAlias:Boolean    = false;
  //= If `true` sIFR will disable anti-aliasing if the font size is larger than `ALIASING_MAX_FONT_SIZE`.
  //  This setting is *independent* from `preserveAntiAlias`.
  public static var conditionalAntiAlias:Boolean = true;
  //= Sets the anti alias type. By default it's `DEFAULT_ANTI_ALIAS_TYPE`.
  //  See also <http://livedocs.macromedia.com/flash/8/main/wwhelp/wwhimpl/common/html/wwhelp.htm?context=LiveDocs_Parts&file=00002733.html>.
  public static var antiAliasType:String         = null;
  //= Flash filters can be added to this array and will be applied to the text field.
  public static var filters:Array                = [];
  //= A mapping from the names of the filters to their actual objecs, used when transforming
  //  filters defined on the client. You can add additional filters here so they'll be supported
  //  when defined on the client.
  public static var filterMap:Object             = {
    DisplacementMapFilter : flash.filters.DisplacementMapFilter,
    ColorMatrixFilter     : flash.filters.ColorMatrixFilter,
    ConvolutionFilter     : flash.filters.ConvolutionFilter,
    GradientBevelFilter   : flash.filters.GradientBevelFilter,
    GradientGlowFilter    : flash.filters.GradientGlowFilter,
    BevelFilter           : flash.filters.BevelFilter,
    GlowFilter            : flash.filters.GlowFilter,
    BlurFilter            : flash.filters.BlurFilter,
    DropShadowFilter      : flash.filters.DropShadowFilter
  };

  private static var instance;
  private static var menu;
  private static var menuItems = [];
  
  private var textField;
  private var content;
  private var forceSingleLine;
  private var fontSize;
  private var tuneWidth;
  private var tuneHeight;
  private var primaryLink;
  private var primaryLinkTarget;
  
  public var realHeight;
  public var renderHeight;
  public var firstResize = true;
  

  
  //= Sets the default styles for `sIFR.styles`. This method is called
  //  directly in `sifr.fla`, before options are applied.
  public static function setDefaultStyles() {
    sIFR.styles.parseCSS([
      '.', CSS_ROOT_CLASS, ' { color: #000000; }',
      'strong { display: inline; font-weight: bold; } ',
      'em { display: inline; font-style: italic; }',
      'a { color: #0000FF; text-decoration: underline; }',
      'a:hover { color: #0000FF; text-decoration: none; }'
    ].join(''));
  }
  
  //= Validates the domain sIFR is being used on.
  //  Returns `true` if the domain is valid, `false` otherwise.  
  public static function checkDomain():Boolean {
    if(sIFR.domains.length == 0) return true;

    var domain = (new LocalConnection()).domain();
    for(var i = 0; i < sIFR.domains.length; i++) {
      var match = sIFR.domains[i];
      if(match == '*' || match == domain) return true;

      var wildcard = match.lastIndexOf('*');
      if(wildcard > -1) {
        match = match.substr(wildcard + 1);
        var matchPosition = domain.lastIndexOf(match);
        if(matchPosition > -1 && (matchPosition + match.length) == domain.length) return true;
      }
    }
    
    return false;
  }
  
  public static function checkLocation():Boolean {
    return _root._url.indexOf('?') == -1;
  }
  
  //= Runs sIFR. Called automatically.
  public static function run(delayed) {
    // Flash version older than 9,0,115 under IE incorrectly approach the Flash movie, breaking ExternalInterface.
    // sIFR has a workaround, but this workaround cannot be applied until the Flash movie has been added to the document,
    // which usually causes the ActionScript to run and set up ExternalInterface. Delaying for a couple milliseconds
    // gives the JavaScript time to set up the workaround.
    if(_root.delayrun == 'true' && !delayed) {
      var interval;
      interval = setInterval(
        function() {
          clearInterval(interval);
          sIFR.run(true);
        }, 200);
        
      return;
    }
    
    // Have to set up the menu items first!
    menuItems.push(
      new ContextMenuItem("Follow link", function() { getURL(sIFR.instance.primaryLink, sIFR.instance.primaryLinkTarget) }),
      new ContextMenuItem("Open link in new window", function() { getURL(sIFR.instance.primaryLink, "_blank") })
    );
    
    var holder       = _root.holder;
    var content      = DEFAULT_TEXT;
    var checkVersion = true;
    if(checkLocation() && checkDomain()) content = unescapeUnicode(_root.content);
    if(content == 'undefined' || content == '') {
      var resetting = ExternalInterface.call('sIFR.__resetBrokenMovies');
      if(resetting) return;
      content      = DEFAULT_TEXT;
      checkVersion = false;
    }
    
    if(checkVersion && _root.version != VERSION) content = VERSION_WARNING.split('%s').join(_root.version);
    
    // Sets stage parameters
    Stage.scaleMode = 'noscale';
    Stage.align = 'TL';

    menu = new ContextMenu();
    menu.hideBuiltInItems();
    _root.menu = menu;
    
    // Other parameters
    var opacity = parseInt(_root.opacity, 10);
    if(!isNaN(opacity)) holder._alpha = sIFR.defaultOpacity == -1 ? opacity : sIFR.defaultOpacity;
    else holder._alpha = 100;
    _root.blendMode = sIFR.defaultBlendMode == -1 ? _root.blendmode : sIFR.defaultBlendMode;

    sIFR.instance = new sIFR(holder.txtF, content);
    Key.addListener({onKeyDown: function() { sIFR.instance.blur() }});
    Mouse.addListener({onMouseWheel: function() { sIFR.instance.blur() }});
    Stage.addListener({onResize: function() { sIFR.instance.onResize(); }});
    if(_root.selectable == 'false') Mouse.addListener({onMouseDown: function() { sIFR.instance.blur() }});
    if(_root.cursor == 'arrow') _root.holder.useHandCursor = false;

    ExternalInterface.addCallback('replaceText', sIFR.instance, sIFR.instance.replaceText);
    ExternalInterface.addCallback('calculateRatios', sIFR.instance, sIFR.instance.calculateRatios);
    ExternalInterface.addCallback('resize', sIFR.instance, sIFR.instance.resize);
    ExternalInterface.addCallback('scaleMovie', sIFR.instance, sIFR.instance.repaint);
    ExternalInterface.addCallback('changeCSS', sIFR.instance, sIFR.instance.changeCSS);
  }
  
  private static function eval(str) {
    var as;

    if(str.charAt(0) == '{') { // Ah, we need to create an object
      as = {};
      str = str.substring(1, str.length - 1);
      var $ = str.split(',');
      for(var i = 0; i < $.length; i++) {
        var $1 = $[i].split(':');
        as[$1[0]] = sIFR.eval($1[1]);
      }
    } else if(str.charAt(0) == '"') { // String
      as = str.substring(1, str.length - 1);
    } else if(str == 'true' || str == 'false') { // Boolean
      as = str == 'true';
    } else { // Float
      as = parseFloat(str);
    }
    
    return as;
  }
  
  private static function unescapeUnicode(str) {
    var result = [];
    var escapees = str.split('%');
    
    for(var i = 0; i < escapees.length; i++) {
      var escapee = escapees[i];
      if(i > 0 || str.charAt(0) == '%') {
        var hex = escapee.charAt(0) == 'u' ? escapee.substr(1, 4) : escapee.substr(0, 2);
        result.push(String.fromCharCode(parseInt(hex, 16)), escapee.substr(escapee.charAt(0) == 'u' ? 5 : 2));
      } else result.push(escapee);
    }

    return result.join('');
  }
  
  private function applyFilters() {
    var $filters = this.textField.filters;
    $filters = $filters.concat(sIFR.filters);
    
    var $ = unescapeUnicode(_root.flashfilters).split(';'); // name,prop:value,...;
    for(var i = 0; i < $.length; i++) {
      var $1 = $[i].split(',');
      
      var newFilter = new sIFR.filterMap[$1[0]]();
      for(var j = 1; j < $1.length; j++) {
        var $2 = $1[j].split(':');
        newFilter[$2[0]] = sIFR.eval(unescapeUnicode($2[1]));
      }
      
      $filters.push(newFilter);
    }

    this.textField.filters = $filters;
  }
  
  private function applyBackground() {
    if(!_root.background) return;
    
    var background = _root.createEmptyMovieClip('backgroundClip', 10);
    var loader = new MovieClipLoader();
    loader.addListener({onLoadInit: function() { background.setMask(_root.holder) }});
    loader.loadClip("/projectfiles/img.jpg", background);
  }
  
  private function setTextFieldSize(width, height) {
    textField._width = tuneWidth + (isNaN(width) ? DEFAULT_WIDTH : width);
    textField._height = tuneHeight + (isNaN(height) ? DEFAULT_HEIGHT : height);
  }
  
  private function sIFR(textField, content) {
    sIFR.instance = this; // Need to set it right now, because it's used in closures later
    
    this.textField = textField;
    this.content   = content;
    
    this.primaryLink       = unescapeUnicode(_root.link);
    this.primaryLinkTarget = unescapeUnicode(_root.target);

    var offsetLeft         = parseInt(_root.offsetleft, 10);
    textField._x           = MARGIN_LEFT + (isNaN(offsetLeft) ? 0 : offsetLeft);
    var offsetTop          = parseInt(_root.offsettop, 10);
    if(!isNaN(offsetTop)) textField._y += offsetTop;
    
    tuneWidth = parseInt(_root.tunewidth, 10);
    if(isNaN(tuneWidth)) tuneWidth = 0;
    tuneHeight = parseInt(_root.tuneheight, 10);
    if(isNaN(tuneHeight)) tuneHeight = 0;
    
    this.renderHeight     = parseInt(_root.renderheight, 10);
    this.setTextFieldSize(parseInt(_root.width, 10), parseInt(this.renderHeight, 10));
    this.forceSingleLine  = _root.forcesingleline == 'true';
    textField.wordWrap    = _root.preventwrap != 'true';
    textField.selectable  = _root.selectable == 'true';
    textField.gridFitType = sIFR.enforcedGridFitType || _root.gridfittype;

    this.applyFilters();
    this.applyBackground();

    this.fontSize = parseInt(_root.size, 10);
    if(isNaN(this.fontSize)) this.fontSize = 26;

    this.setStyles(unescapeUnicode(_root.css), false);
    
    if(!sIFR.preserveAntiAlias && (sIFR.conditionalAntiAlias && this.fontSize < ALIASING_MAX_FONT_SIZE
    || !sIFR.conditionalAntiAlias)) {
      textField.antiAliasType = (_root.antialiastype != '' ? _root.antialiastype : sIFR.antiAliasType) || DEFAULT_ANTI_ALIAS_TYPE;      
    }

    if(!sIFR.preserveAntiAlias || !isNaN(parseInt(_root.sharpness, 10))) {
      textField.sharpness = parseInt(_root.sharpness, 10);
    }
    if(isNaN(textField.sharpness)) textField.sharpness = sIFR.defaultSharpness;

    if(!sIFR.preserveAntiAlias || !isNaN(parseInt(_root.thickness, 10))) {
      textField.thickness = parseInt(_root.thickness, 10);
    }
    if(isNaN(textField.thickness)) textField.thickness = sIFR.defaultThickness;
    
    textField._parent._xscale = textField._parent._yscale = 100;
    
    this.setupEvents();
    this.write(content);
    this.repaint();
  }
  
  private static function call(method) {
    var args = Array.prototype.slice.call(arguments, 1);
    args.unshift('sIFR.replacements["' + _root.id + '"].' + method);
    return ExternalInterface.call.apply(ExternalInterface, args);
  }
  
  private function repaint() {
    if(this.forceSingleLine) {
      this.textField._width = 50000;
      // 50 000 is a bit too much, filters won't work at that size etc. Therefore we size it down to the text width, and
      // a bit of margin.
      this.textField._width = this.textField.textWidth + 500;
    }
    
    var leadingFix = this.isSingleLine() ? sIFR.styles.latestLeading : 0;
    
    // Flash wants to scroll the movie by one line, by adding the fontSize to the
    // textField height this is no longer happens. We also add the absolute tuneHeight,
    // to prevent a negative value from triggering the bug. We won't send the fake
    // value to the JavaScript side, though.
    textField._height = Math.max(MIN_HEIGHT, textField.textHeight + PADDING_BOTTOM + tuneHeight - leadingFix) + this.fontSize + Math.abs(tuneHeight);
    this.realHeight = Math.floor(textField._height - this.fontSize - Math.abs(tuneHeight));
    var width = _root.fitexactly == 'true' ? textField.textWidth + tuneWidth : null;

    this.doScale(function() {
      // Store in a local variable to deal with synchronous interaction with JavaScript.
      var firstResize = sIFR.instance.firstResize;
      sIFR.instance.firstResize = false;
      sIFR.call('resizeFlashElement', sIFR.instance.realHeight, width, firstResize);
      sIFR.instance.renderHeight = sIFR.instance.realHeight;
    });
  }
  
  private function write(content) {
    this.textField.htmlText = ['<p class="', CSS_ROOT_CLASS, '">', 
                                content, '</p>'
                              ].join('');
  }
  
  private function isSingleLine() {
    return Math.round((this.textField.textHeight - sIFR.styles.latestLeading) / this.fontSize) == 1;
  }
  
  public function doScale(callback) {
    if(this.validScale()) return this.scale(callback);

    var self = this;
    this.textField._parent.onEnterFrame = function() {
      if(!self.validScale()) return;
      delete self.textField._parent.onEnterFrame;
      self.scale(callback);
    }
  }

  //= Scales the text field to the new scale of the Flash movie itself.
  public function scale(callback) {
    this.textField._parent._xscale = this.textField._parent._yscale = this.calculateScale();
    if(callback) callback();
  }
  
  public function calculateScale() {
    return 10 * Math.round(10 * Stage.height / this.renderHeight);
  }
  
  public function validScale() {
    return Stage.height >= 10 && this.calculateScale() >= 20;
  }
  
  public function onResize() {
    if(!this.validScale()) return;
    
    var oldZoom = this.textField._parent._xscale;
    var zoom    = this.calculateScale();
    
    this.scale();
    if(oldZoom != zoom) sIFR.call('resizeAfterScale');
  }
  
  private function calculateRatios() {
    var strings = ['x', 'x<br>x', 'x<br>x<br>x', 'x<br>x<br>x<br>x'];
    var results = {};
    
    this.setTextFieldSize(1000, 1000);

    for(var i = 1; i <= strings.length; i++) {
      var size = MIN_FONT_SIZE;

      this.write(strings[i - 1]);
      while(size < MAX_FONT_SIZE) {
        var rootStyle = sIFR.styles.getStyle('.sIFR-root') || {};
        rootStyle.fontSize = size;
        sIFR.styles.setStyle('.sIFR-root', rootStyle);
        this.textField.styleSheet = sIFR.styles;
        this.repaint();
        var ratio = (this.realHeight - PADDING_BOTTOM - tuneHeight) / i / size;
        if(!results[size]) results[size] = ratio;
        else results[size] = ((i - 1) * results[size] + ratio) / i;
        size++;
      }
    }

    var ratios = [];

    // Here we round the ratios to two decimals and try to create an optimized array of ratios 
    // to be used by sIFR.
    // lastRatio is the ratio we are currently optimizing
    var lastRatio = roundDecimals(results[MIN_FONT_SIZE], 2);
    for(var size = MIN_FONT_SIZE + 1; size < MAX_FONT_SIZE; size++) {
      var ratio = roundDecimals(results[size], 2);
      
      // If the lastRatio is different from the previous ratio, and from the current ratio, 
      // try to see if there's at least a 1px difference between the two. If so, store the 
      // lastRatio with the previous size, then optimize the current ratio.
      if(lastRatio != results[size - 1] && lastRatio != ratio && Math.abs(Math.round(size * ratio) - Math.round(size * lastRatio)) >= 1) {
        ratios.push(size -1, lastRatio);
        lastRatio = ratio;
      }
    }

    // Add the last optimized ratio as the default ratio.
    ratios.push(lastRatio);

    ExternalInterface.call('sIFR.debug.__ratiosCallback', _root.id, ratios);
  }
  
  private function roundDecimals(value, decimals) {
    return Math.round(value * Math.pow(10, decimals)) / Math.pow(10, decimals);
  }
  
  public function replaceText(content) {
    this.content = unescapeUnicode(content);
    this.setupEvents();
    this.write(this.content);
    this.repaint();
  }
  
  public function resize(height) {
    this.setTextFieldSize(height, this.realHeight);
    this.repaint();
  }
  
  public function changeCSS(css) {
    this.setStyles(unescapeUnicode(css), true);
    this.repaint();
  }
  
  private function contentIsLink() {
    return this.content.indexOf('<a ') == 0 && this.content.indexOf('<a ') == this.content.lastIndexOf('<a ')
      && this.content.indexOf('</a>') == this.content.length - 4;
  }
  
  private function setupEvents() {
    if(_root.fixhover == 'true' && this.contentIsLink()) {
      
      this.textField._parent.onRollOver = function() { 
        sIFR.call('fireEvent', 'onRollOver');
      };
      
      this.textField._parent.onRollOut  = function() { 
        sIFR.instance.fixHover();
        sIFR.call('fireEvent', 'onRollOut');
      };
      
      this.textField._parent.onRelease  = function() {
        sIFR.call('fireEvent', 'onRelease');
        getURL(sIFR.instance.primaryLink, sIFR.instance.primaryLinkTarget);
      };
      
      menu.customItems = menuItems;
    } else {
      if(_root.events == 'true') {
        this.textField._parent.onRollOver = function() { sIFR.call('fireEvent', 'onRollOver') };
        this.textField._parent.onRollOut  = function() { sIFR.call('fireEvent', 'onRollOut') };
        this.textField._parent.onRelease  = function() { sIFR.call('fireEvent', 'onRelease') };
      } else {
        if(_root.cursor == 'pointer') this.textField._parent.onRelease = function() {};
        else delete this.textField._parent.onRelease;
        delete this.textField._parent.onRollOver;
        delete this.textField._parent.onRollOut;
      }
      
      menu.customItems = [];
    }
  }
  
  private function fixHover() {
    this.write('');
    this.write(this.content);
  }
  
  public function blur() {
    switch(Key.getCode()) {
      case Key.SHIFT:
      case Key.CONTROL:
        break;
      default:
        sIFR.call('blurFlashElement');
    }
  }
  
  private function setStyles(css, reset) {
    if(reset) {
      sIFR.styles = new SifrStyleSheet();
      sIFR.setDefaultStyles();
    }
    
    sIFR.styles.fontSize = this.fontSize;
    // Set font-size and other styles
    sIFR.styles.parseCSS(css);
    
    var rootStyle = sIFR.styles.getStyle('.sIFR-root') || {};
    rootStyle.fontSize = this.fontSize; // won't go higher than 126!
    sIFR.styles.setStyle('.sIFR-root', rootStyle);
    this.textField.styleSheet = sIFR.styles;
  }
}
