/*****************************************************************************
scalable Inman Flash Replacement (sIFR) version 3, revision 436.

Copyright 2006 – 2008 Mark Wubben, <http://novemberborn.net/>

Older versions:
* IFR by Shaun Inman
* sIFR 1.0 by Mike Davidson, Shaun Inman and Tomas Jogin
* sIFR 2.0 by Mike Davidson, Shaun Inman, Tomas Jogin and Mark Wubben

See also <http://novemberborn.net/sifr3> and <http://wiki.novemberborn.net/sifr3>.

This software is licensed and provided under the CC-GNU LGPL.
See <http://creativecommons.org/licenses/LGPL/2.1/>
*****************************************************************************/

var sIFR = new function() {
  var self = this;

  var ClassNames  = {
    ACTIVE    : 'sIFR-active',
    REPLACED  : 'sIFR-replaced',
    IGNORE    : 'sIFR-ignore',
    ALTERNATE : 'sIFR-alternate',
    CLASS     : 'sIFR-class',
    LAYOUT    : 'sIFR-layout',
    FLASH     : 'sIFR-flash',
    FIX_FOCUS : 'sIFR-fixfocus',
    DUMMY     : 'sIFR-dummy'
  };
  
  ClassNames.IGNORE_CLASSES = [ClassNames.REPLACED, ClassNames.IGNORE, ClassNames.ALTERNATE];
  
  this.MIN_FONT_SIZE        = 6;
  this.MAX_FONT_SIZE        = 126;
  this.FLASH_PADDING_BOTTOM = 5;
  this.VERSION              = '436';

  this.isActive             = false;
  this.isEnabled            = true;
  this.fixHover             = true;
  this.autoInitialize       = true;
  this.setPrefetchCookie    = true;
  this.cookiePath           = '/';
  this.domains              = [];
  this.forceWidth           = true;
  this.fitExactly           = false;
  this.forceTextTransform   = true;
  this.useDomLoaded         = true;
  this.useStyleCheck        = false;
  this.hasFlashClassSet     = false;
  this.repaintOnResize      = true;
  this.replacements         = [];
  
  var elementCount          = 0; // The number of replaced elements.
  var isInitialized         = false;

  function Errors() {
    this.fire = function(id) {
      if(this[id + 'Alert']) alert(this[id + 'Alert']);
      throw new Error(this[id]);
    };
  
    this.isFile      = 'sIFR: Did not activate because the page is being loaded from the filesystem.';
    this.isFileAlert = 'Hi!\n\nThanks for using sIFR on your page. Unfortunately sIFR couldn\'t activate, because it was loaded '
                        + 'directly from your computer.\nDue to Flash security restrictions, you need to load sIFR through a web'
                        + ' server.\n\nWe apologize for the inconvenience.';
  };
  
  function Util(sIFR) {
    function capitalize($) {
      return $.toLocaleUpperCase();
    }
    
    this.normalize = function(str) {
      // Replace linebreaks and &nbsp; by whitespace, then normalize.
      // Flash doesn't support no-breaking space characters, hence they're replaced by a normal space.
      return str.replace(/\n|\r|\xA0/g, Util.SINGLE_WHITESPACE).replace(/\s+/g, Util.SINGLE_WHITESPACE);
    };
    
    this.textTransform = function(type, str) {
      switch(type) {
        case 'uppercase':
          return str.toLocaleUpperCase();
        case 'lowercase':
          return str.toLocaleLowerCase();
        case 'capitalize':
          return str.replace(/^\w|\s\w/g, capitalize);
      }
      return str;
    };
    
    this.toHexString = function(str) {
      if(str.charAt(0) != '#' || str.length != 4 && str.length != 7) return str;
      
      str = str.substring(1);
      return '0x' + (str.length == 3 ? str.replace(/(.)(.)(.)/, '$1$1$2$2$3$3') : str);
    };
    
    this.toJson = function(obj, strFunc) {
      var json = '';
  
      switch(typeof(obj)) {
        case 'string':
          json = '"' + strFunc(obj) + '"';
          break;
        case 'number':
        case 'boolean':
          json = obj.toString();
          break;
        case 'object':
          json = [];
          for(var prop in obj) {
            if(obj[prop] == Object.prototype[prop]) continue;
            json.push('"' + prop + '":' + this.toJson(obj[prop]));
          }
          json = '{' + json.join(',') + '}';
          break;
      }
  
      return json;
    };
  
    this.convertCssArg = function(arg) {
      if(!arg) return {};
      if(typeof(arg) == 'object') {
        if(arg.constructor == Array) arg = arg.join('');
        else return arg;
      }
  
      var obj = {};
      var rules = arg.split('}');
  
      for(var i = 0; i < rules.length; i++) {
        var $ = rules[i].match(/([^\s{]+)\s*\{(.+)\s*;?\s*/);
        if(!$ || $.length != 3) continue;
  
        if(!obj[$[1]]) obj[$[1]] = {};
  
        var properties = $[2].split(';');
        for(var j = 0; j < properties.length; j++) {
          var $2 = properties[j].match(/\s*([^:\s]+)\s*\:\s*([^;]+)/);
          if(!$2 || $2.length != 3) continue;
          obj[$[1]][$2[1]] = $2[2].replace(/\s+$/, '');
        }
      }
  
      return obj;
    };
  
    this.extractFromCss = function(css, selector, property, remove) {
      var value = null;
  
      if(css && css[selector] && css[selector][property]) {
        value = css[selector][property];
        if(remove) delete css[selector][property];
      }
  
      return value;
    };
    
    this.cssToString = function(arg) {
      var css = [];
      for(var selector in arg) {
        var rule = arg[selector];
        if(rule == Object.prototype[selector]) continue;
  
        css.push(selector, '{');
        for(var property in rule) {
          if(rule[property] == Object.prototype[property]) continue;
          var value = rule[property];
          if(Util.UNIT_REMOVAL_PROPERTIES[property]) value = parseInt(value, 10);
          css.push(property, ':', value, ';');
        }
        css.push('}');
      }
  
      return css.join('');
    };
  
    this.escape = function(str) {
      return escape(str).replace(/\+/g, '%2B');
    };
    
    this.encodeVars = function(vars) {
      return vars.join('&').replace(/%/g, '%25');
    };
    
    this.copyProperties = function(from, to) {
      for(var property in from) {
        if(to[property] === undefined) to[property] = from[property];
      }
      return to;
    };
    
    this.domain = function() {
      var domain = '';
      // When trying to access document.domain on a Google-translated page with Firebug, I got an exception. 
      // Try/catch to be safe.
      try { domain = document.domain } catch(e) {};
      return domain;
    };
    
    this.domainMatches = function(domain, match) {
      if(match == '*' || match == domain) return true;
  
      var wildcard = match.lastIndexOf('*');
      if(wildcard > -1) {
        match = match.substr(wildcard + 1);
        var matchPosition = domain.lastIndexOf(match);
        if(matchPosition > -1 && (matchPosition + match.length) == domain.length) return true;
      }
      
      return false;
    };
    
    this.uriEncode = function(s) {
      return encodeURI(decodeURIComponent(s));  // Decode first, in case the URI was already encoded.
    };
    
    this.delay = function(ms, func, scope) {
      var args = Array.prototype.slice.call(arguments, 3);
      setTimeout(function() { func.apply(scope, args) }, ms);
    };
  };
  
  Util.UNIT_REMOVAL_PROPERTIES = {leading: true, 'margin-left': true, 'margin-right': true, 'text-indent': true};
  Util.SINGLE_WHITESPACE       = ' ';
  
  
  function DomUtil(sIFR) {
    var self = this;
    
    function getDimensionFromStyle(node, property, offsetProperty)
    {
      var dimension = self.getStyleAsInt(node, property, sIFR.ua.ie);
      if(dimension == 0) {
        dimension = node[offsetProperty];
        for(var i = 3; i < arguments.length; i++) dimension -= self.getStyleAsInt(node, arguments[i], true);
      }
      return dimension;
    }
    
    this.getBody = function() {
      return document.getElementsByTagName('body')[0] || null;
    };
    
    this.querySelectorAll = function(selector) {
      return window.parseSelector(selector);
    };
  
    this.addClass = function(name, node) {
      if(node) node.className = ((node.className || '') == '' ? '' : node.className + ' ') + name;
    };
    
    this.removeClass = function(name, node) {
      if(node) node.className = node.className.replace(new RegExp('(^|\\s)' + name + '(\\s|$)'), '').replace(/^\s+|(\s)\s+/g, '$1');
    };
  
    this.hasClass = function(name, node) {
      return new RegExp('(^|\\s)' + name + '(\\s|$)').test(node.className);
    };
    
    this.hasOneOfClassses = function(names, node) {
      for(var i = 0; i < names.length; i++) {
        if(this.hasClass(names[i], node)) return true;
      }
      return false;
    };
    
    this.ancestorHasClass = function(node, name) {
      node = node.parentNode;
      while(node && node.nodeType == 1) {
        if(this.hasClass(name, node)) return true;
        node = node.parentNode;
      }
      return false;
    };
  
    this.create = function(name, className) {
      var node = document.createElementNS ? document.createElementNS(DomUtil.XHTML_NS, name) : document.createElement(name);
      if(className) node.className = className;
      return node;
    };
    
    this.getComputedStyle = function(node, property) {
      var result;
      if(document.defaultView && document.defaultView.getComputedStyle) {
        var style = document.defaultView.getComputedStyle(node, null);
        result = style ? style[property] : null;
      } else {
        if(node.currentStyle) result = node.currentStyle[property];
      }
      return result || ''; // Ensuring a string.
    };
  
    this.getStyleAsInt = function(node, property, requirePx) {
      var value = this.getComputedStyle(node, property);
      if(requirePx && !/px$/.test(value)) return 0;
      return parseInt(value) || 0;
    };
    
    this.getWidthFromStyle = function(node) {
      return getDimensionFromStyle(node, 'width', 'offsetWidth', 'paddingRight', 'paddingLeft', 'borderRightWidth', 'borderLeftWidth');
    };
  
    this.getHeightFromStyle = function(node) {
      return getDimensionFromStyle(node, 'height', 'offsetHeight', 'paddingTop', 'paddingBottom', 'borderTopWidth', 'borderBottomWidth');
    };
  
    this.getDimensions = function(node) {
      var width  = node.offsetWidth;
      var height = node.offsetHeight;
      
      if(width == 0 || height == 0) {
        for(var i = 0; i < node.childNodes.length; i++) {
          var child = node.childNodes[i];
          if(child.nodeType != 1) continue;
          width  = Math.max(width, child.offsetWidth);
          height = Math.max(height, child.offsetHeight);
        }
      }
      
      return {width: width, height: height};
    };
    
    this.getViewport = function() {
      return {
        width:  window.innerWidth  || document.documentElement.clientWidth  || this.getBody().clientWidth,
        height: window.innerHeight || document.documentElement.clientHeight || this.getBody().clientHeight
      };
    };
    
    this.blurElement = function(element) {
      try {
        element.blur();
        return;
      } catch(e) {};
      
      // Move the focus to an input element, and then destroy it.
      var input = this.create('input');
      input.style.width  = '0px';
      input.style.height = '0px';
      element.parentNode.appendChild(input);
      input.focus();
      input.blur();
      input.parentNode.removeChild(input);
    };
  };
  
  DomUtil.XHTML_NS = 'http://www.w3.org/1999/xhtml';
  
  function UserAgentDetection(sIFR) {
    var ua              = navigator.userAgent.toLowerCase();
    var product         = (navigator.product || '').toLowerCase();
    var platform        = navigator.platform.toLowerCase();
  
    this.parseVersion = UserAgentDetection.parseVersion;
  
    this.macintosh        = /^mac/.test(platform);
    this.windows          = /^win/.test(platform);
    this.linux            = /^linux/.test(platform);
    this.quicktime        = false;
  
    this.opera            = /opera/.test(ua);
    this.konqueror        = /konqueror/.test(ua);
    this.ie               = false/*@cc_on || true @*/;
    this.ieSupported      = this.ie         && !/ppc|smartphone|iemobile|msie\s5\.5/.test(ua)/*@cc_on && @_jscript_version >= 5.5 @*/
    this.ieWin            = this.windows    && this.ie/*@cc_on && @_jscript_version >= 5.1 @*/;
    this.windows          = this.windows    && (!this.ie || this.ieWin);
    this.ieMac            = this.macintosh  && this.ie/*@cc_on && @_jscript_version < 5.1 @*/;
    this.macintosh        = this.macintosh  && (!this.ie || this.ieMac);
    this.safari           = /safari/.test(ua);
    this.webkit           = !this.konqueror && /applewebkit/.test(ua);
    this.khtml            = this.webkit     || this.konqueror;
    this.gecko            = !this.khtml     && product == 'gecko';
                          
    this.ieVersion        = this.ie         && /.*msie\s(\d\.\d)/.exec(ua)           ? this.parseVersion(RegExp.$1) : '0';
    this.operaVersion     = this.opera      && /.*opera(\s|\/)(\d+\.\d+)/.exec(ua)   ? this.parseVersion(RegExp.$2) : '0';
    this.webkitVersion    = this.webkit     && /.*applewebkit\/(\d+).*/.exec(ua)     ? this.parseVersion(RegExp.$1) : '0';
    this.geckoVersion     = this.gecko      && /.*rv:\s*([^\)]+)\)\s+gecko/.exec(ua) ? this.parseVersion(RegExp.$1) : '0';
    this.konquerorVersion = this.konqueror  && /.*konqueror\/([\d\.]+).*/.exec(ua)   ? this.parseVersion(RegExp.$1) : '0';
  
    this.flashVersion   = 0;
  
    if(this.ieWin) {
      var axo;
      var stop = false;
      try {
        axo = new ActiveXObject('ShockwaveFlash.ShockwaveFlash.7');
      } catch(e) {
        // In case the Flash 7 registry key does not exist, we need to test for specific 
        // Flash 6 installs before we can use the general key. 
        // See also <http://blog.deconcept.com/2006/01/11/getvariable-setvariable-crash-internet-explorer-flash-6/>.
        // Many thanks to Geoff Stearns and Bobby van der Sluis for clarifying the problem and providing
        // examples of non-crashing code.
        try {
          axo                   = new ActiveXObject('ShockwaveFlash.ShockwaveFlash.6');
          this.flashVersion     = this.parseVersion('6');
          axo.AllowScriptAccess = 'always';
        } catch(e) { stop = this.flashVersion == this.parseVersion('6'); }
        
        if(!stop) try { axo = new ActiveXObject('ShockwaveFlash.ShockwaveFlash'); } catch(e) {}
      }
      
      if(!stop && axo) {
        this.flashVersion = this.parseVersion((axo.GetVariable('$version') || '').replace(/^\D+(\d+)\D+(\d+)\D+(\d+).*/g, '$1.$2.$3'));
      }
    } else if(navigator.plugins && navigator.plugins['Shockwave Flash']) {
      var d = navigator.plugins['Shockwave Flash'].description.replace(/^.*\s+(\S+\s+\S+$)/, '$1');
      var v = d.replace(/^\D*(\d+\.\d+).*$/, '$1');
      if(/r/.test(d)) v += d.replace(/^.*r(\d*).*$/, '.$1');
      else if(/d/.test(d)) v += '.0';
      this.flashVersion = this.parseVersion(v);
      
      // Watch out for QuickTime, which could be stealing the Flash handling! Also check to make sure the plugin for the Flash
      // MIMEType is enabled.
      var foundEnabled = false;
      for(var i = 0, valid = this.flashVersion >= UserAgentDetection.MIN_FLASH_VERSION; valid && i < navigator.mimeTypes.length; i++) {
        var mime = navigator.mimeTypes[i];
        if(mime.type != 'application/x-shockwave-flash') continue;
        if(mime.enabledPlugin) {
          foundEnabled = true;
          if(mime.enabledPlugin.description.toLowerCase().indexOf('quicktime') > -1) {
            valid = false;
            this.quicktime = true;
          }
        }
      }
      
      if(this.quicktime || !foundEnabled) this.flashVersion = this.parseVersion('0');
    }
    this.flash = this.flashVersion >= UserAgentDetection.MIN_FLASH_VERSION;
    this.transparencySupport  = this.macintosh || this.windows
                                               || this.linux && (
                                                    this.flashVersion >= this.parseVersion('10')
                                                    && (
                                                      this.gecko && this.geckoVersion >= this.parseVersion('1.9')
                                                      || this.opera
                                                    )
                                                  );
    this.computedStyleSupport = this.ie || !!document.defaultView.getComputedStyle;
    this.fixFocus             = this.gecko  && this.windows;
    this.nativeDomLoaded      = this.gecko  || this.webkit    && this.webkitVersion  >= this.parseVersion('525')
                                            || this.konqueror && this.konquerorMajor >  this.parseVersion('03') || this.opera;
    this.mustCheckStyle       = this.khtml  || this.opera;
    this.forcePageLoad        = this.webkit && this.webkitVersion < this.parseVersion('523')
    this.properDocument       = typeof(document.location) == 'object';
  
    this.supported            = this.flash  && this.properDocument && (!this.ie || this.ieSupported) && this.computedStyleSupport
                                            && (!this.opera  || this.operaVersion  >= this.parseVersion('9.61')) 
                                            && (!this.webkit || this.webkitVersion >= this.parseVersion('412'))
                                            && (!this.gecko  || this.geckoVersion  >= this.parseVersion('1.8.0.12'))
                                            && (!this.konqueror/* || this.konquerorVersion >= this.parseVersion('4.1')*/);
  };
  
  UserAgentDetection.parseVersion = function(s) {
    return s.replace(
      /(^|\D)(\d+)(?=\D|$)/g,
      function(s, nonDigit, digits) {
        s = nonDigit;
        for(var i = 4 - digits.length; i >= 0; i--) s += '0';
        return s + digits;
      }
    );
  };
  UserAgentDetection.MIN_FLASH_VERSION = UserAgentDetection.parseVersion('8');
  
  function FragmentIdentifier(sIFR) {
    this.fix = sIFR.ua.ieWin && window.location.hash != '';
  
    var cachedTitle;
    this.cache = function() {
      cachedTitle = document.title;
    };
  
    function doFix() {
      document.title = cachedTitle;
    }
  
    this.restore = function() {
      if(this.fix) setTimeout(doFix, 0);
    };
  };
  function PageLoad(sIFR) {
    var dummy = null;
    
    function pollLoad() {
      try {
        // IE hack courtesy of Diego Perini – <http://javascript.nwbox.com/IEContentLoaded/>.
        // Merged polling taken from jQuery – <http://dev.jquery.com/browser/trunk/jquery/src/event.js>
        if(sIFR.ua.ie || document.readyState != 'loaded' && document.readyState != 'complete') {
          document.documentElement.doScroll('left');
        }
      } catch(e) {
        return setTimeout(pollLoad, 10);
      }
      afterDomLoad();
    };
    
    function afterDomLoad() {
      if(sIFR.useStyleCheck) checkStyle();
      else if(!sIFR.ua.mustCheckStyle) fire(null, true);
    };
    
    function checkStyle() {
      dummy = sIFR.dom.create("div", ClassNames.DUMMY);
      sIFR.dom.getBody().appendChild(dummy);
      pollStyle();
    };
    
    function pollStyle() {
      if(sIFR.dom.getComputedStyle(dummy, 'marginLeft') == '42px') afterStyle();
      else setTimeout(pollStyle, 10);
    };
    
    function afterStyle() {
      if(dummy && dummy.parentNode) dummy.parentNode.removeChild(dummy);
      dummy = null;
      fire(null, true);
    };
    
    function fire(evt, preserveReplacements) {
      sIFR.initialize(preserveReplacements);
      
      // Remove handlers to prevent memory leak in Firefox 1.5, but only after onload.
      if(evt && evt.type == 'load') {
        if(document.removeEventListener) document.removeEventListener('DOMContentLoaded', fire, false);
        if(window.removeEventListener) window.removeEventListener('load', fire, false);
      }
    };
    
    // Unload detection based on the research from Moxiecode. <http://blog.moxiecode.com/2008/04/08/unload-event-never-fires-in-ie/>
    function verifyUnload() {
      sIFR.prepareClearReferences();
      if(document.readyState == 'interactive') {
        document.attachEvent('onstop', unloadByStop);
        setTimeout(function() { document.detachEvent('onstop', unloadByStop) }, 0);
      }
    };
    
    function unloadByStop() {
      document.detachEvent('onstop', unloadByStop);
      fireUnload();
    };
    
    function fireUnload() {
      sIFR.clearReferences();
    };
    
    this.attach = function() {
      if(window.addEventListener) window.addEventListener('load', fire, false);
      else window.attachEvent('onload', fire);
      
      if(!sIFR.useDomLoaded || sIFR.ua.forcePageLoad || sIFR.ua.ie && window.top != window) return;
      
      if(sIFR.ua.nativeDomLoaded) {
        document.addEventListener('DOMContentLoaded', afterDomLoad, false);
      } else if(sIFR.ua.ie || sIFR.ua.khtml) {
        pollLoad();
      } 
    };
    
    this.attachUnload = function() {
      if(!sIFR.ua.ie) return;
      window.attachEvent('onbeforeunload', verifyUnload);
      window.attachEvent('onunload', fireUnload);
    }
  };
  
  var PREFETCH_COOKIE = 'sifrFetch';
  
  function Prefetch(sIFR) {
    var hasPrefetched = false;
    
    this.fetchMovies = function(movies) {
      if(sIFR.setPrefetchCookie && new RegExp(';?' + PREFETCH_COOKIE + '=true;?').test(document.cookie)) return;
  
      try { // We don't know which DOM actions the user agent will allow
        hasPrefetched = true;
        prefetch(movies);
      } catch(e) {}
  
      if(sIFR.setPrefetchCookie) document.cookie = PREFETCH_COOKIE + '=true;path=' + sIFR.cookiePath;
    };
  
    this.clear = function() {
      if(!hasPrefetched) return;
  
      try {
        var nodes = document.getElementsByTagName('script');
        for(var i = nodes.length - 1; i >= 0; i--) {
          var node = nodes[i];
          if(node.type == 'sifr/prefetch') node.parentNode.removeChild(node);
        }
      } catch(e) {}
    };
    
    function prefetch(args) {
      for(var i = 0; i < args.length; i++) {
        document.write('<scr' + 'ipt defer type="sifr/prefetch" src="' + args[i].src + '"></' + 'script>');
      }
    }
  };
  
  function BrokenFlashIE(sIFR) {
    var active      = sIFR.ua.ie;
    var fixFlash    = active && sIFR.ua.flashVersion < sIFR.ua.parseVersion('9.0.115');
    var resetMovies = {};
    var registry    = {};
    
    this.fixFlash = fixFlash;
    
    this.register = function(flashNode) {
      if(!active) return;
      
      var id = flashNode.getAttribute('id');
      // Try cleaning up previous Flash <object>
      this.cleanup(id, false);
      
      registry[id] = flashNode;
      delete resetMovies[id];
      
      if(fixFlash) window[id] = flashNode;
    };
    
    this.reset = function() {
      if(!active) return false;
      
      for(var i = 0; i < sIFR.replacements.length; i++) {
        var flash = sIFR.replacements[i];
        var flashNode = registry[flash.id];
        if(!resetMovies[flash.id] && (!flashNode.parentNode || flashNode.parentNode.nodeType == 11)) {
          flash.resetMovie();
          resetMovies[flash.id] = true;
        }
      }
      
      return true;
    };
    
    this.cleanup = function(id, usePlaceholder) {
      var node = registry[id];
      if(!node) return;
      
      for(var expando in node) {
        if(typeof(node[expando]) == 'function') node[expando] = null;
      }
      registry[id] = null;
      if(fixFlash) window[id] = null;
      
      if(node.parentNode) {
        if(usePlaceholder && node.parentNode.nodeType == 1) {
          // Replace the Flash node by a placeholde element with the same dimensions. This stops the page from collapsing
          // when the Flash movies are removed.
          var placeholder          = document.createElement('div');
          placeholder.style.width  = node.offsetWidth  + 'px';
          placeholder.style.height = node.offsetHeight + 'px';
          node.parentNode.replaceChild(placeholder, node);
        } else {
          node.parentNode.removeChild(node);
        }
      }
    };
    
    this.prepareClearReferences = function() {
      if(!fixFlash) return;
      
      // Disable Flash cleanup, see <http://blog.deconcept.com/2006/05/18/flash-player-bug-streaming-content-innerhtml-ie/>
      // for more info.
      __flash_unloadHandler      = function(){};
      __flash_savedUnloadHandler = function(){};
    };
    
    this.clearReferences = function() {
      // Since we've disabled Flash' own cleanup, add all objects on the page to our registry so they can be cleaned up.
      if(fixFlash) {
        var objects = document.getElementsByTagName('object');
        for(var i = objects.length - 1; i >= 0; i--) registry[objects[i].getAttribute('id')] = objects[i];
      }
      
      for(var id in registry) {
        if(Object.prototype[id] != registry[id]) this.cleanup(id, true);
      }
    };
  }
  
  function FlashInteractor(sIFR, id, vars, forceWidth, events) {
    this.sIFR         = sIFR;
    this.id           = id;
    this.vars         = vars;
    // Type of value depends on SWF builder. This could use some improvement!
    this.movie        = null;
    
    this.__forceWidth = forceWidth;
    this.__events     = events;
    this.__resizing   = 0;
  }
  
  FlashInteractor.prototype = {
    getFlashElement: function() {
      return document.getElementById(this.id);
    },
    
    getAlternate: function() {
      return document.getElementById(this.id + '_alternate');
    },
    
    getAncestor: function() {
      var ancestor = this.getFlashElement().parentNode;
      return !this.sIFR.dom.hasClass(ClassNames.FIX_FOCUS, ancestor) ? ancestor : ancestor.parentNode;
    },
    
    available: function() {
      var flashNode = this.getFlashElement();
      return flashNode && flashNode.parentNode;
    },
    
    call: function(type) {
      var flashNode = this.getFlashElement();
      
      if (!flashNode[type]) {
        return false;
      }
      // In Firefox 2, exposed Flash methods aren't proper functions, there's no `apply()` method! This workaround
      // does work, though.
      return Function.prototype.apply.call(flashNode[type], flashNode, Array.prototype.slice.call(arguments, 1));
    },
    
    attempt: function() {
      if(!this.available()) return false;
      
      try {
        this.call.apply(this, arguments);
      } catch(e) {
        if(this.sIFR.debug) throw e;
        return false;
      }
      
      return true;
    },
    
    updateVars: function(name, value) {
      for(var i = 0; i < this.vars.length; i++) {
        if (this.vars[i].split('=')[0] == name) {
          this.vars[i] = name + '=' + value;
          break;
        }
      }
      
      var vars = this.sIFR.util.encodeVars(this.vars);
      this.movie.injectVars(this.getFlashElement(), vars);
      this.movie.injectVars(this.movie.html, vars);
    },
    
    storeSize: function(type, value) {
      this.movie.setSize(type, value);
      this.updateVars(type, value);
    },
    
    fireEvent: function(name) {
      if(this.available() && this.__events[name]) this.sIFR.util.delay(0, this.__events[name], this, this);
    },
    
    resizeFlashElement: function(height, width, firstResize) {
      if(!this.available()) return;
      
      this.__resizing++;
      
      var flashNode = this.getFlashElement();
      flashNode.setAttribute('height', height);
      
      // Reset element height as declared by `MovieCreator`
      this.getAncestor().style.minHeight = '';
      
      this.updateVars('renderheight', height);
      this.storeSize('height', height);
      if(width !== null) {
        flashNode.setAttribute('width', width);
        // Don't store the size, it may cause Flash to wrap the text when the movie is reset.
        this.movie.setSize('width', width);
      }
      if(this.__events.onReplacement) {
        this.sIFR.util.delay(0, this.__events.onReplacement, this, this);
        delete this.__events.onReplacement;
      }
      
      if(firstResize) {
        this.sIFR.util.delay(0, function() {
          this.attempt('scaleMovie');
          this.__resizing--;
        }, this);
      } else {
        this.__resizing--;
      }
    },
    
    blurFlashElement: function() {
      if(this.available()) this.sIFR.dom.blurElement(this.getFlashElement());
    },
    
    resetMovie: function() {
      this.sIFR.util.delay(0, this.movie.reset, this.movie, this.getFlashElement(), this.getAlternate());
    },
    
    resizeAfterScale: function() {
      if(this.available() && this.__resizing == 0) this.sIFR.util.delay(0, this.resize, this);
    },
    
    resize: function() {
      if(!this.available()) return;
      
      this.__resizing++;
      
      var flashNode      = this.getFlashElement();
      var currentWidth   = flashNode.offsetWidth;
      
      // The Flash movie has no dimensions, which means it's not visible anyway. No need to recalculate.
      if(currentWidth == 0) return;
      
      var originalWidth  = flashNode.getAttribute('width');
      var originalHeight = flashNode.getAttribute('height');
      
      var ancestor       = this.getAncestor();
      var minHeight      = this.sIFR.dom.getHeightFromStyle(ancestor);
      
      // Remove Flash movie from flow
      flashNode.style.width  = '1px';
      flashNode.style.height = '1px';
      
      // Set a minimal height on the flashNode's parent, to stop a reflow
      ancestor.style.minHeight = minHeight + 'px';
      
      // Restore original content
      var nodes = this.getAlternate().childNodes;
      var clones = [];
      for(var i = 0; i < nodes.length; i++) {
        var node = nodes[i].cloneNode(true);
        clones.push(node);
        ancestor.appendChild(node);
      }
      
      // Calculate width
      var width = this.sIFR.dom.getWidthFromStyle(ancestor);
      
      // Remove original content again
      for(var i = 0; i < clones.length; i++) ancestor.removeChild(clones[i]);
      
      // Reset Flash movie flow
      flashNode.style.width = flashNode.style.height = ancestor.style.minHeight = '';
      flashNode.setAttribute('width', this.__forceWidth ? width : originalWidth);
      flashNode.setAttribute('height', originalHeight);
      
      // IE can get mightily confused about where to draw the Flash <object>. This is a workaround to force IE to repaint
      // the <object>.
      if(sIFR.ua.ie) {
        flashNode.style.display = 'none';
        var repaint = flashNode.offsetHeight;
        flashNode.style.display = '';
      }
      
      // Resize!
      if(width != currentWidth) {
        if(this.__forceWidth) this.storeSize('width', width);
        this.attempt('resize', width);
      }
      
      this.__resizing--;
    },
    
    // `content` must not be util.escaped when passed in.
    // alternate may be an array of nodes to be appended to the alternate content, use this
    // in XHTML documents.
    replaceText: function(content, alternate) {
      var escapedContent = this.sIFR.util.escape(content);
      if(!this.attempt('replaceText', escapedContent)) return false;
      
      this.updateVars('content', escapedContent);
      var node = this.getAlternate();
      if(alternate) {
        while(node.firstChild) node.removeChild(node.firstChild);
        for(var i = 0; i < alternate.length; i++) node.appendChild(alternate[i]);
      } else {
        try { node.innerHTML = content; } catch(e) {};
      }
      
      return true;
    },
    
    changeCSS: function(css) {
      css = this.sIFR.util.escape(this.sIFR.util.cssToString(this.sIFR.util.convertCssArg(css)));
      this.updateVars('css', css);
      return this.attempt('changeCSS', css);
    },
    
    remove: function() {
      if(this.movie && this.available()) this.movie.remove(this.getFlashElement(), this.id);
    }
  };
  
  var MovieCreator = new function() {
    this.create = function(sIFR, brokenFlash, node, fixFocus, id, src, width, height, vars, wmode, backgroundColor) {
      var klass = sIFR.ua.ie ? IEFlashMovie : FlashMovie;
      return new klass(
        sIFR, brokenFlash, node, fixFocus, 
        id, src, width, height, 
        ['flashvars', vars, 'wmode', wmode, 'bgcolor', backgroundColor, 'allowScriptAccess', 'always', 'quality', 'best']
      );
    }
    
    function FlashMovie(sIFR, brokenFlash, node, fixFocus, id, src, width, height, params) {
      var object = sIFR.dom.create('object', ClassNames.FLASH);
      var attrs  = ['type', 'application/x-shockwave-flash', 'id', id, 'name', id, 'data', src, 'width', width, 'height', height];
      for(var i = 0; i < attrs.length; i += 2) object.setAttribute(attrs[i], attrs[i + 1]);
      
      var insertion = object;
      if(fixFocus) {
        insertion = dom.create("div", ClassNames.FIX_FOCUS);
        insertion.appendChild(object);
      }
      
      for(var i = 0; i < params.length; i+=2) {
        if(params[i] == 'name') continue;
        
        var param = dom.create('param');
        param.setAttribute('name', params[i]);
        param.setAttribute('value', params[i + 1]);
        object.appendChild(param);
      }
      
      // Before removing the existing content, set its height such that the element
      // does not collapse. Height is restored in `FlashInteractor#resizeFlashElement`.
      node.style.minHeight = height + 'px';
      
      while(node.firstChild) node.removeChild(node.firstChild);
      node.appendChild(insertion);
      
      this.html = insertion.cloneNode(true);
    }
    
    FlashMovie.prototype = {
      reset: function(flashNode, alternate) {
        flashNode.parentNode.replaceChild(this.html.cloneNode(true), flashNode);
      },
      
      remove: function(flashNode, id) {
        flashNode.parentNode.removeChild(flashNode);
      },
      
      setSize: function(type, value) {
        this.html.setAttribute(type, value);
      },
      
      injectVars: function(flash, encodedVars) {
        var params = flash.getElementsByTagName('param');
        for(var i = 0; i < params.length; i++) {
          if(params[i].getAttribute('name') == 'flashvars') {
            params[i].setAttribute('value', encodedVars);
            break;
          }
        }
      }
    };
    
    function IEFlashMovie(sIFR, brokenFlash, node, fixFocus, id, src, width, height, params) {
      this.dom    = sIFR.dom;
      this.broken = brokenFlash;
      
      this.html = '<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" id="' + id +
        '" width="' + width + '" height="' + height + '" class="' + ClassNames.FLASH + '">' +
        '<param name="movie" value="' + src + '"></param></object>'
        ;
      var paramsHtml = '';
      for(var i = 0; i < params.length; i+=2) {
        paramsHtml += '<param name="' + params[i] + '" value="' + params[i + 1] + '"></param>';
      }
      this.html      = this.html.replace(/(<\/object>)/, paramsHtml + '$1');
      
      // Before removing the existing content, set its height such that the element
      // does not collapse. Height is restored in `FlashInteractor#resizeFlashElement`.
      node.style.minHeight = height + 'px';
      
      node.innerHTML = this.html;
      
      this.broken.register(node.firstChild);
    }
    
    IEFlashMovie.prototype = {
      reset: function(flashNode, alternate) {
        alternate            = alternate.cloneNode(true);
        var parent           = flashNode.parentNode;
        parent.innerHTML     = this.html;
        this.broken.register(parent.firstChild);
        parent.appendChild(alternate);
      },
      
      remove: function(flashNode, id) {
        this.broken.cleanup(id);
      },
      
      setSize: function(type, value) {
         this.html = this.html.replace(type == 'height' ? /(height)="\d+"/ : /(width)="\d+"/, '$1="' + value + '"');
      },
      
      injectVars: function(flash, encodedVars) {
        if(flash != this.html) return;
        this.html = this.html.replace(/(flashvars(=|\"\svalue=)\")[^\"]+/, '$1' + encodedVars);
      }
    };
  }
  
  this.errors =             new Errors(self);
  var util    = this.util = new Util(self);
  var dom     = this.dom  = new DomUtil(self);
  var ua      = this.ua   = new UserAgentDetection(self);
  var hacks   = {
    fragmentIdentifier:     new FragmentIdentifier(self),
    pageLoad:               new PageLoad(self),
    prefetch:               new Prefetch(self),
    brokenFlashIE:          new BrokenFlashIE(self)
  };
  this.__resetBrokenMovies = hacks.brokenFlashIE.reset;
  
  var replaceKwargsStore = {
    kwargs: [],
    replaceAll:  function(preserve) {
      for(var i = 0; i < this.kwargs.length; i++) self.replace(this.kwargs[i]);
      if(!preserve) this.kwargs = [];
    }
  };
  
  this.activate = function(/* … */) {
    if(!ua.supported || !this.isEnabled || this.isActive || !isValidDomain() || isFile()) return;
    hacks.prefetch.fetchMovies(arguments);
    
    this.isActive = true;
    this.setFlashClass();
    hacks.fragmentIdentifier.cache();
    hacks.pageLoad.attachUnload();
    
    if(!this.autoInitialize) return;
    
    hacks.pageLoad.attach();
  };
  
  this.setFlashClass = function() {
    if(this.hasFlashClassSet) return;
    
    dom.addClass(ClassNames.ACTIVE, dom.getBody() || document.documentElement);
    this.hasFlashClassSet = true;
  };
  
  this.removeFlashClass = function() {
    if(!this.hasFlashClassSet) return;
    
    dom.removeClass(ClassNames.ACTIVE, dom.getBody());
    dom.removeClass(ClassNames.ACTIVE, document.documentElement);
    this.hasFlashClassSet = false;
  };
  
  this.initialize = function(preserveReplacements) {
    if(!this.isActive || !this.isEnabled) return;
    if(isInitialized) {
      if(!preserveReplacements) replaceKwargsStore.replaceAll(false);
      return;
    }
    
    isInitialized = true;
    replaceKwargsStore.replaceAll(preserveReplacements);
    
    if(self.repaintOnResize) {
      if(window.addEventListener) window.addEventListener('resize', resize, false);
      else window.attachEvent('onresize', resize);
    }
    
    hacks.prefetch.clear();
  };
  
  this.replace = function(kwargs, mergeKwargs) {
    if(!ua.supported) return;
    
    // This lets you specify two kwarg objects so you don't have to repeat common settings.
    // The first object will be merged with the second, while properties in the second 
    // object have priority over those in the first. The first object is unmodified
    // for further use, the resulting second object will be used in the replacement.
    if(mergeKwargs) kwargs = util.copyProperties(kwargs, mergeKwargs);
    
    if(!isInitialized) return replaceKwargsStore.kwargs.push(kwargs);
    
    if(this.onReplacementStart) this.onReplacementStart(kwargs);
    
    var nodes = kwargs.elements || dom.querySelectorAll(kwargs.selector);
    if(nodes.length == 0) return;
    
    var src             = getSource(kwargs.src);
    var css             = util.convertCssArg(kwargs.css);
    var filters         = getFilters(kwargs.filters);
    
    var forceSingleLine = kwargs.forceSingleLine === true;
    var preventWrap     = kwargs.preventWrap === true && !forceSingleLine;
    var fitExactly      = forceSingleLine || (kwargs.fitExactly == null ? this.fitExactly : kwargs.fitExactly) === true;
    var forceWidth      = fitExactly || (kwargs.forceWidth == null ? this.forceWidth : kwargs.forceWidth) === true;
    var ratios          = kwargs.ratios || [];
    var pixelFont       = kwargs.pixelFont === true;
    var tuneHeight      = parseInt(kwargs.tuneHeight) || 0;
    var events          = !!kwargs.onRelease || !!kwargs.onRollOver || !!kwargs.onRollOut;
    
    // Alignment should be handled by the browser in this case.
    if(fitExactly) util.extractFromCss(css, '.sIFR-root', 'text-align', true);
    
    var fontSize        = util.extractFromCss(css, '.sIFR-root', 'font-size', true)        || '0';
    var backgroundColor = util.extractFromCss(css, '.sIFR-root', 'background-color', true) || '#FFFFFF';
    var kerning         = util.extractFromCss(css, '.sIFR-root', 'kerning', true)          || '';
    var opacity         = util.extractFromCss(css, '.sIFR-root', 'opacity', true)          || '100';
    var cursor          = util.extractFromCss(css, '.sIFR-root', 'cursor', true)           || 'default';
    var leading         = parseInt(util.extractFromCss(css, '.sIFR-root', 'leading'))      || 0;
    var gridFitType     = kwargs.gridFitType ||
                            (util.extractFromCss(css, '.sIFR-root', 'text-align') == 'right') ? 'subpixel' : 'pixel';
    var textTransform   = this.forceTextTransform === false 
                            ? 'none'
                            : util.extractFromCss(css, '.sIFR-root', 'text-transform', true) || 'none';
    // Only font sizes specified in pixels are supported.
    fontSize            = /^\d+(px)?$/.test(fontSize) ? parseInt(fontSize) : 0;
    // Make sure to support percentages and decimals
    opacity             = parseFloat(opacity) < 1 ? 100 * parseFloat(opacity) : opacity;
    
    var cssText = kwargs.modifyCss ? '' : util.cssToString(css);
    var wmode   = kwargs.wmode || '';
    if(!wmode) {
      if(kwargs.transparent) wmode = 'transparent';
      else if(kwargs.opaque) wmode = 'opaque';
    } 
    if(wmode == 'transparent') {
      if(!ua.transparencySupport) wmode = 'opaque';
      else backgroundColor = 'transparent';
    } else if(backgroundColor == 'transparent') {
      backgroundColor = '#FFFFFF';
    }
    
    for(var i = 0; i < nodes.length; i++) {
      var node = nodes[i];
      
      if(dom.hasOneOfClassses(ClassNames.IGNORE_CLASSES, node) || dom.ancestorHasClass(node, ClassNames.ALTERNATE)) continue;
      
      // Opera does not allow communication with hidden Flash movies. Visibility is tackled by sIFR itself, but
      // `display:none` isn't. Additionally, WebKit does not return computed style information for elements with
      // `display:none`. We'll prevent elements which have `display:none` or are contained in such an element from
      // being replaced. It's a bit hard to detect this, but we'll check for the dimensions of the element and its
      // `display` property.
      
      var dimensions = dom.getDimensions(node);
      var height     = dimensions.height;
      var width      = dimensions.width;
      var display    = dom.getComputedStyle(node, 'display');
      
      if(!height || !width || !display || display == 'none') continue;
      
      // Get the width (to approximate the final size).
      width = dom.getWidthFromStyle(node);
      
      var size, lines;
      if(!fontSize) {
        var calculation    = calculate(node);
        size               = Math.min(this.MAX_FONT_SIZE, Math.max(this.MIN_FONT_SIZE, calculation.fontSize));
        if(pixelFont) size = Math.max(8, 8 * Math.round(size / 8));
        
        lines = calculation.lines;
      } else {
        size  = fontSize;
        lines = 1;
      }
      
      var alternate = dom.create('span', ClassNames.ALTERNATE);
      // Clone the original content to the alternate element.
      var contentNode = node.cloneNode(true);
      // Temporarily append the contentNode to the document, to get around IE problems with resolved hrefs
      node.parentNode.appendChild(contentNode);
      for(var j = 0, l = contentNode.childNodes.length; j < l; j++) {
        var child = contentNode.childNodes[j];
        // Let's not keep <style> or <script> in the alternate content, since it may be
        // reintroduced to the DOM after resizing.
        if (!/^(style|script)$/i.test(child.nodeName)) {
          alternate.appendChild(child.cloneNode(true));
        }
      }
      
      // Allow the sIFR content to be modified
      if(kwargs.modifyContent) kwargs.modifyContent(contentNode, kwargs.selector);
      if(kwargs.modifyCss) cssText = kwargs.modifyCss(css, contentNode, kwargs.selector);
      
      var content = parseContent(contentNode, textTransform, kwargs.uriEncode);
      // Remove the contentNode again
      contentNode.parentNode.removeChild(contentNode);
      if(kwargs.modifyContentString) content.text = kwargs.modifyContentString(content.text, kwargs.selector);
      if(content.text == '') continue;
      
      // Approximate the final height to avoid annoying movements of the page
      var renderHeight = Math.round(lines * getRatio(size, ratios) * size) + this.FLASH_PADDING_BOTTOM + tuneHeight;
      if (lines > 1 && leading) {
        renderHeight += Math.round((lines - 1) * leading);
      }
      
      var forcedWidth = forceWidth ? width : '100%';
      
      var id   = 'sIFR_replacement_' + elementCount++;
      var vars = ['id='              + id,
                  'content='         + util.escape(content.text),
                  'width='           + width,
                  'renderheight='    + renderHeight, 
                  'link='            + util.escape(content.primaryLink.href   || ''),
                  'target='          + util.escape(content.primaryLink.target || ''),
                  'size='            + size, 
                  'css='             + util.escape(cssText),
                  'cursor='          + cursor,
                  'tunewidth='       + (kwargs.tuneWidth || 0),
                  'tuneheight='      + tuneHeight,
                  'offsetleft='      + (kwargs.offsetLeft || ''),
                  'offsettop='       + (kwargs.offsetTop  || ''),
                  'fitexactly='      + fitExactly,
                  'preventwrap='     + preventWrap,
                  'forcesingleline=' + forceSingleLine,
                  'antialiastype='   + (kwargs.antiAliasType || ''),
                  'thickness='       + (kwargs.thickness || ''),
                  'sharpness='       + (kwargs.sharpness || ''),
                  'kerning='         + kerning,
                  'gridfittype='     + gridFitType,
                  'flashfilters='    + filters,
                  'opacity='         + opacity,
                  'blendmode='       + (kwargs.blendMode || ''), 
                  'selectable='      + (kwargs.selectable == null || wmode != '' && !sIFR.ua.macintosh && sIFR.ua.gecko && sIFR.ua.geckoVersion >= sIFR.ua.parseVersion('1.9')
                                         ? 'true' 
                                         : kwargs.selectable === true
                                       ),
                  'fixhover='        + (this.fixHover === true),
                  'events='          + events,
                  'delayrun='        + hacks.brokenFlashIE.fixFlash,
                  'version='         + this.VERSION];
      
      var encodedVars = util.encodeVars(vars);
      var interactor  = new FlashInteractor(self, id, vars, forceWidth, {
        onReplacement: kwargs.onReplacement,
        onRollOver: kwargs.onRollOver,
        onRollOut: kwargs.onRollOut,
        onRelease: kwargs.onRelease
      });
      interactor.movie = MovieCreator.create(
        sIFR, hacks.brokenFlashIE, node, ua.fixFocus && kwargs.fixFocus, 
        id, src, forcedWidth, renderHeight, 
        encodedVars, wmode, backgroundColor
      );
      this.replacements.push(interactor);
      this.replacements[id] = interactor;
      if(kwargs.selector) {
        if(!this.replacements[kwargs.selector]) this.replacements[kwargs.selector] = [interactor];
        else this.replacements[kwargs.selector].push(interactor);
      }
      alternate.setAttribute('id', id + '_alternate');
      node.appendChild(alternate);
      dom.addClass(ClassNames.REPLACED, node);
    }
    
    hacks.fragmentIdentifier.restore();
  };
  
  this.getReplacementByFlashElement = function(node) {
    for(var i = 0; i < self.replacements.length; i++) {
      if(self.replacements[i].id == node.getAttribute('id')) return self.replacements[i];
    }
  };
  
  this.redraw = function() {
    for(var i = 0; i < self.replacements.length; i++) self.replacements[i].resetMovie();
  };
  
  this.prepareClearReferences = function() {
    hacks.brokenFlashIE.prepareClearReferences();
  };
  
  this.clearReferences = function() {
    hacks.brokenFlashIE.clearReferences();
    hacks = null;
    replaceKwargsStore = null;
    delete self.replacements;
  };
  
  // The goal here is not to prevent usage of the Flash movie, but running sIFR on possibly translated pages
  function isValidDomain() {
    if(self.domains.length == 0) return true;
    
    var domain = util.domain();
    for(var i = 0; i < self.domains.length; i++) {
      if(util.domainMatches(domain, self.domains[i])) {
        return true;
      }
    }
    
    return false;
  }
  
  function isFile() {
    if(document.location.protocol == 'file:') {
      if(self.debug) self.errors.fire('isFile');
      return true;
    }
    return false;
  }
  
  function getSource(src) {
    if(ua.ie && src.charAt(0) == '/') {
      src = window.location.toString().replace(/([^:]+)(:\/?\/?)([^\/]+).*/, '$1$2$3') + src;
    }
    
    return src;
  }
  
  // Gives a font-size to required vertical space ratio
  function getRatio(size, ratios) {
    for(var i = 0; i < ratios.length; i += 2) {
      if(size <= ratios[i]) return ratios[i + 1];
    }
    return ratios[ratios.length - 1] || 1;
  }
  
  function getFilters(obj) {
    var filters = [];
    for(var filter in obj) {
      if(obj[filter] == Object.prototype[filter]) continue;
      
      var properties = obj[filter];
      filter = [filter.replace(/filter/i, '') + 'Filter'];
      
      for(var property in properties) {
        if(properties[property] == Object.prototype[property]) continue;
        // Double-escaping (see end of function) makes it easier to parse the resulting string
        // in AS.
        filter.push(property + ':' + util.escape(util.toJson(properties[property], util.toHexString)));
      }
      
      filters.push(filter.join(','));
    }
    
    return util.escape(filters.join(';'));
  }
  
  function resize(evt) {
    var current  = resize.viewport;
    var viewport = dom.getViewport();
    
    if(current && viewport.width == current.width && viewport.height == current.height) return;
    resize.viewport = viewport;
    
    if(self.replacements.length == 0) return; // Nothing replaced yet, resize event is not important.
    
    if(resize.timer) clearTimeout(resize.timer);
    resize.timer = setTimeout(function() {
      delete resize.timer;
      for(var i = 0; i < self.replacements.length; i++) self.replacements[i].resize();
    }, 200);
  }
  
  function calculate(node) {
    var fontSize = dom.getComputedStyle(node, 'fontSize');
    var deduce = fontSize.indexOf('px') == -1;
    
    var html = node.innerHTML;
    if (deduce) {
      node.innerHTML = 'X';
    }
    
    // Reset padding and border, so offsetHeight works properly
    node.style.paddingTop = node.style.paddingBottom = node.style.borderTopWidth = node.style.borderBottomWidth = '0px';
    // 2em magically makes offsetHeight correct in IE
    node.style.lineHeight = '2em';
    // Provided display is block
    node.style.display = 'block';
    
    fontSize = deduce ? node.offsetHeight / 2 : parseInt(fontSize, 10);
    
    if (deduce) {
      node.innerHTML = html;
    }
    
    var lines = Math.round(node.offsetHeight / (2 * fontSize));
    
    node.style.paddingTop = node.style.paddingBottom = node.style.borderTopWidth = node.style.borderBottomWidth
                          = node.style.lineHeight = node.style.display = '';
    
    if (isNaN(lines) || !isFinite(lines) || lines == 0) {
      lines = 1;
    }
    
    return {fontSize: fontSize, lines: lines};
  }
  
  function parseContent(source, textTransform, uriEncode) {
    uriEncode = uriEncode || util.uriEncode;
    var stack = [], content = [];
    var primaryLink = null;
    var nodes = source.childNodes;
    var whiteSpaceEnd = false, firstText = false;
    
    var i = 0;
    while(i < nodes.length) {
      var node = nodes[i];
      
      if(node.nodeType == 3) {
        var text = util.textTransform(textTransform, util.normalize(node.nodeValue)).replace(/</g, '&lt;');
        if(whiteSpaceEnd && firstText) text = text.replace(/^\s+/, '');
        content.push(text);
        whiteSpaceEnd = /\s$/.test(text);
        firstText = false;
      }
      
      if(node.nodeType == 1 && !/^(style|script)$/i.test(node.nodeName)) {
        var attributes = [];
        var nodeName   = node.nodeName.toLowerCase();
        var className  = node.className || '';
        // If there are multiple classes, look for the specified sIFR class
        if(/\s+/.test(className)) {
          if(className.indexOf(ClassNames.CLASS) > -1) className = className.match('(\\s|^)' + ClassNames.CLASS + '-([^\\s$]*)(\\s|$)')[2];
          // or use the first class. This is because Flash does not support the use of multiple class names.
          // Flash doesn't support IDs either.
          else className = className.match(/^([^\s]+)/)[1];
        }
        if(className != '') attributes.push('class="' + className + '"');
        
        if(nodeName == 'a') {
          var href   = uriEncode(node.getAttribute('href') || '');
          var target = node.getAttribute('target') || '';
          attributes.push('href="' + href + '"', 'target="' + target + '"');
          
          if(!primaryLink) {
            primaryLink = {
              href: href,
              target: target
            };
          }
        }
        
        content.push('<' + nodeName + (attributes.length > 0 ? ' ' : '') + attributes.join(' ') + '>');
        firstText = true;
        
        if(node.hasChildNodes()) {
          // Push the current index to the stack and prepare to iterate
          // over the childNodes.
          stack.push(i);
          i = 0;
          nodes = node.childNodes;
          continue;
        } else if(!/^(br|img)$/i.test(node.nodeName)) content.push('</', node.nodeName.toLowerCase(), '>');
      }
      
      if(stack.length > 0 && !node.nextSibling) {
        // Iterating the childNodes has been completed. Go back to the position
        // before we started the iteration. If that position was the last child,
        // go back even further.
        do {
          i = stack.pop();
          nodes = node.parentNode.parentNode.childNodes;
          node = nodes[i];
          if(node) content.push('</', node.nodeName.toLowerCase(), '>');
        } while(i == nodes.length - 1 && stack.length > 0);
      }
      
      i++;
    }
    
    return {text: content.join('').replace(/^\s+|\s+$|\s*(<br>)\s*/g, '$1'), primaryLink: primaryLink || {}};
  }
};

/*=:project
    parseSelector 2.0.2
    
  =:description
    Provides an extensible way of parsing CSS selectors against a DOM in 
    JavaScript.

  =:file
    Copyright: 2006-2008 Mark Wubben.
    Author: Mark Wubben, <http://novemberborn.net/>
       
  =:license
    This software is licensed and provided under the CC-GNU LGPL. 
    See <http://creativecommons.org/licenses/LGPL/2.1/>
    
  =:support
    parseSelector supports the following user agents:
      * Internet Explorer 6 and above
      * Firefox 1.0 and above, and equivalent Gecko engine versions
      * Safari 2.0 and above
      * Opera 8.0 and above
      * Konqueror 3.5.5 and above
    It might work in other browsers and versions, but there are no guarantees. There is
    no verification made when parseSelector is run to ascertain the browser is supported.
  
  =:notes
    The parsing of CSS selectors as streams has been based on Dean Edwards
    excellent work with cssQuery. See <http://dean.edwards.name/my/cssQuery/>
    for more info.
*/

var parseSelector = (function() {
  var SEPERATOR       = /\s*,\s*/
  var WHITESPACE      = /\s*([\s>+~(),]|^|$)\s*/g;
  var IMPLIED_ALL     = /([\s>+~,]|[^(]\+|^)([#.:@])/g;
  var STANDARD_SELECT = /(^|\))[^\s>+~]/g;
  var INSERT_SPACE    = /(\)|^)/;
  var STREAM          = /[\s#.:>+~()@]|[^\s#.:>+~()@]+/g;
  
  function parseSelector(selector, node) {
    node = node || document.documentElement;
    var argSelectors = selector.split(SEPERATOR), result = [];
    
    for(var i = 0; i < argSelectors.length; i++) {
      var nodes = [node], stream = toStream(argSelectors[i]);
      for(var j = 0; j < stream.length;) {
        var token = stream[j++], filter = stream[j++], args = '';
        if(stream[j] == '(') {
          while(stream[j++] != ')' && j < stream.length) args += stream[j];
          args = args.slice(0, -1);
        }
        nodes = select(nodes, token, filter, args);
      }
      result = result.concat(nodes);
    }
    
    return result;
  }

  function toStream(selector) {
    var stream = selector.replace(WHITESPACE, '$1').replace(IMPLIED_ALL, '$1*$2').replace(STANDARD_SELECT, insertSpaces);
    return stream.match(STREAM) || [];
  }
  
  function insertSpaces(str) {
    return str.replace(INSERT_SPACE, '$1 ');
  }
  
  function select(nodes, token, filter, args) {
    return (parseSelector.selectors[token]) ? parseSelector.selectors[token](nodes, filter, args) : [];
  }
  
  var util = {
    toArray: function(enumerable) {
      var a = [];
      for(var i = 0; i < enumerable.length; i++) a.push(enumerable[i]);
      return a;
    }
  };
  
  var dom = {
    isTag: function(node, tag) {
      return (tag == '*') || (tag.toLowerCase() == node.nodeName.toLowerCase());
    },
  
    previousSiblingElement: function(node) {
      do node = node.previousSibling; while(node && node.nodeType != 1);
      return node;
    },
  
    nextSiblingElement: function(node) {
      do node = node.nextSibling; while(node && node.nodeType != 1);
      return node;
    },
  
    hasClass: function(name, node) {
      return (node.className || '').match('(^|\\s)'+name+'(\\s|$)');
    },
  
    getByTag: function(tag, node) {
      return node.getElementsByTagName(tag);
    }
  };

  var selectors = {
    '#': function(nodes, filter) {
      for(var i = 0; i < nodes.length; i++) {
        if(nodes[i].getAttribute('id') == filter) return [nodes[i]];
      }
      return [];
    },

    ' ': function(nodes, filter) {
      var result = [];
      for(var i = 0; i < nodes.length; i++) {
        result = result.concat(util.toArray(dom.getByTag(filter, nodes[i])));
      }
      return result;
    },
    
    '>': function(nodes, filter) {
      var result = [];
      for(var i = 0, node; i < nodes.length; i++) {
        node = nodes[i];
        for(var j = 0, child; j < node.childNodes.length; j++) {
          child = node.childNodes[j];
          if(child.nodeType == 1 && dom.isTag(child, filter)) result.push(child);
        }
      }
      return result;
    },

    '.': function(nodes, filter) {
      var result = [];
      for(var i = 0, node; i < nodes.length; i++) {
        node = nodes[i];
        if(dom.hasClass([filter], node)) result.push(node);
      }
      return result;
    }, 
        
    ':': function(nodes, filter, args) {
      return (parseSelector.pseudoClasses[filter]) ? parseSelector.pseudoClasses[filter](nodes, args) : [];
    }
    
  };

  parseSelector.selectors     = selectors;
  parseSelector.pseudoClasses = {};
  parseSelector.util          = util;
  parseSelector.dom           = dom;

  return parseSelector;
})();
