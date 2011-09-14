//$Id: json_server.js,v 1.2.4.2 2010/05/04 20:04:26 skyredwang Exp $

/**
 *  Convert a variable to a json string.
 */
Drupal.toJson = function(v) {
  switch (typeof v) {
    case 'boolean':
      return v == true ? 'TRUE' : 'FALSE';
    case 'number':
      return v;
    case 'string':
      return '"'+ v +'"';
    case 'object':
      var output = "{";
      for(i in v) {
        output = output + i + ":" + Drupal.toJson(v[i]) + ",";
      }
      output = output + "}";
      return output;
    default:
      return 'null';
  }
};

/**
 *  A JavaScript implementation for interacting with services.
 */
Drupal.service = function(service_method, args, success) {
  args = $.extend({method: service_method}, args);
  args_done = {};
  for(i in args) {
    args_done[i] = Drupal.toJson(args[i]);
  }
  $.post(Drupal.settings.baseurl + "?q=services/json", args_done, function(unparsed_data) {
    parsed_data = Drupal.parseJson(unparsed_data);
    success(!parsed_data['#error'], parsed_data['#data']);
  });
};

