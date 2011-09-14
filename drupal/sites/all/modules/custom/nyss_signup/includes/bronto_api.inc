<?php

/**
 *  @file
 *  Bronto API class
 */
 
class bronto_api {
  private $binding;
  private $login = ''; // the account's Bronto login ID
  private $sitename = ''; // the account's Bronto sitename
  private $password = ''; // the account's Bronto password
  private $siteId = NULL; // the account's siteId (Agency users only)

  private $err_code = NULL; // the error code from the last api call
  private $err_msg  = NULL; // the error message from the last api call

  function __construct($login, $sitename, $password, $siteId = NULL) {
    $this->login = $login;
    $this->sitename = $sitename;
    $this->password = $password;
    $this->siteId = $siteId;
    $this->err_code = NULL;
    $this->err_msg = NULL;
  }

  /** GET/SET FUNCTIONS **/

  protected function set_error_code($value) {
    $this->err_code = (int) $value;
  }
  function get_error_code() {
    return $this->err_code;
  }

  protected function set_error_message($value) {
    $this->err_msg = (string) $value;
  }
  function get_error_message() {
    return $this->err_msg;
  }

  protected function clear_response_codes() {
    $this->err_code = NULL;
    $this->err_msg = NULL;
  }

  /** API FUNCTIONS **/

  function get_accounts() {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }

    try {
      $result = $binding->readAccounts();
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }

    if (!is_array($result->return->accounts)) {
      $result_exp = var_export($result, TRUE);
      $this->set_error_code(-1);
      $this->set_error_message("\$result from readAccounts() error:<br/> <pre>$result_exp</pre>");
      return FALSE;
    }
    return $result->return->accounts;    
  }

  function get_contact_lists($email) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    $contact = $this->get_contact_by_email($email);
    if (!$contact) {
      return FALSE;
    }

    $lists = $this->get_all_lists();
    if (!$lists) {
      return FALSE;
    }
    
    $user_lists = array();
    if (is_array($contact->lists)) {
      foreach ($lists as $list) {
        if (in_array($list->id, $contact->lists)) {
          $user_lists[] = $list->label;
        }
      }
    }
    else {
      foreach ($lists as $list) {
        if ($list->id == $contact->lists) {
          $user_lists = array($list->label);
          break;
        }
      }
    }
    return $user_lists;
  }

  function add_email_to_list($email, $list_name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    $list = $this->get_list_by_name($list_name);
    if (!$list->id) {
      return FALSE;
    }
  
    $contact = $this->get_contact_by_email($email);
    if (!$contact) {
      return FALSE;
    }
    
    if (!$contact->lists) {
      $contact->lists = array($list->id);
    }
    else {
      if (is_array($contact->lists)) {
        if (!in_array($list->id, $contact->lists)) {
          $contact->lists[] = $list->id;
        }
      }
      elseif ($contact->lists != $list->id) {
        $contact->lists = array($contact->lists, $list->id);
      }
    }
  
    unset($contact->modified);
  
    try {
      $result = $binding->writeContacts(
        array(
          'contacts' => array($contact),
          'handler' => array(
            'mode' => 'insertUpdate',
            'listsMode' => 'insertUpdate',
          ),
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
    
    return $result->return->result->success;
  }

  function remove_email_from_list($email, $list_name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }

    $list = $this->get_list_by_name($list_name);
    if (!$list->id) {
      return FALSE;
    }
    
    $contact = $this->get_contact_by_email($email);
    if (!$contact) {
      return FALSE;
    }
    
    if (!$contact->lists) {
      $contact->lists = array();
    }
    else {
      if (is_array($contact->lists)) {
        $contact->lists = array_diff($contact->lists, array($list->id));
        // Need to make sure keys are sequential for some reason
        $lists = array();
        foreach ($contact->lists as $list) {
          $lists[] = $list;
        }
        $contact->lists = $lists;
      }
      elseif ($contact->lists == $list->id) {
        $contact->lists = array();
      }
    }

    unset($contact->modified);
  
    try {
      $result = $binding->writeContacts(
        array(
          'contacts' => array($contact),
          'handler' => array(
            'mode' => 'insertUpdate',
            'listsMode' => 'replace',
          ),
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
    
    return $result->return->result->success;
  }

  function create_fields($field_data) {   
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    $fields = array();
    foreach ($field_data as $name => $field) {
      $fields[] = array(
        'name' => $name,
        'label' => $field['label'],
        'type' => 'string',
        'visibility' => $field['visibility'],
        'display' => $field['display'],
      );
    }
    
    try {
      $result = $binding->writeFields(
        array(
          'fields' => $fields,
          'handler' => array(
            'mode' => 'insertUpdate',
            'optionsMode' => 'insertUpdate',
          ),
        )
      );
    }
    catch(SoapFault $exception) {  
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
   
    return $result->return->result;
  }

  function update_fields($email, $values) {   
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }

    $contact = $this->get_contact_by_email($email);
    if (!$contact) {
      return FALSE;
    }
    
    $field_ids = array();
    foreach ($values as $name => $value) {
      $field = new stdClass();
      $field->fieldId = $this->get_field_id($name);
      $field->value = $values[$name];
      $field_ids[] = $field;
    }
    $contact->fields = $field_ids;
    
    unset($contact->modified);
  
    try {
      $result = $binding->writeContacts(
        array(
          'contacts' => array($contact),
          'handler' => array(
            'mode' => 'insertUpdate',
            'listsMode' => 'insertUpdate',
            'fieldsMode' => 'insertUpdate',
          ),
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
    
    return $result->return->result->success;
  }

  function send_message($from_name, $from_email, $recipient, $subject, $body, $footer = '', $type = 'text', $recipient_type = 'list') {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    // first step, create the message and get the message id stored in bronto
    $bmid = $this->create_message($subject, $body, $footer, $type);
    if (!$bmid) {
      return FALSE;
    }

    if ($recipient_type == 'list') {
      $list = $this->get_list_by_name($recipient);
      if (!$list->id) {
        return FALSE;
      }
      $recipients = array(array('type' => 'list', 'id' => $list->id));
    }
    elseif ($recipient_type == 'contact') {
      $contact = $this->get_contact_by_email($recipient);
      if (!$contact) {
        return FALSE;
      }
      $recipients = array(array('type' => 'contact', 'id' => $contact->id));    
    }

    $delivery = array(
      'start' => 'now',
      'messageId' => $bmid,
      'recipients' => $recipients,
      'fromEmail' => $from_email,
      'fromName' => $from_name,
      'replyEmail' => $from_email,
    );
  
    $handler = array(
      'mode' => 'insert',
    );
  
    try {
      $result = $binding->writeDeliveries(
        array(
          'deliveries' => array($delivery),
          'handler' => $handler,
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }

    return $result->return->result->success;
  }

  function create_list($list_name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    $params = array(
      'lists' => array(
        'name' => $list_name,
        'label' => $list_name
      ),
      'handler' => array(
        'mode' => 'insert'
      )
    );
  
    try {
      $result = $binding->writeLists($params);
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
    return $result->return->result->success;
  }

  /** HELPER FUNCTIONS **/

  protected function login() {
    $wsdl = 'http://api.bronto.com/?q=mail_3&wsdl';
    $Binding = new SoapClient($wsdl, array('trace' => 1));
  
    // First we try to log in
    $parameters = array(
      'username' => $this->login,
      'sitename' => $this->sitename,
      'password' => $this->password,
    );
    
    if ($this->siteId) {
      $parameters['siteId'] = $this->siteId;
    }

    try {
      $Result = $Binding->login($parameters);
    }
    catch (SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
  
    if (!$Result->return->success) {
      $this->set_error_code(-1);
      $this->set_error_message('Unable to login');
      return FALSE;
    }

    $serviceURL = $Result->return->serviceURL;
    $sessionId = $Result->return->sessionId;

    // Next we need to set the SessionHeader with the sessionId.
    $SessionHeader = new SoapHeader('http://api.bronto.com', 'sessionHeader', array('sessionId' => $sessionId));
    $Binding->__setLocation($serviceURL);
    $Binding->__setSoapHeaders(array($SessionHeader));
    return $Binding;
  }

  protected function get_binding() {
    if (!$this->binding) {
      $this->binding = $this->login();
    }
  
    return $this->binding;  
  }
  
  protected function get_list_by_name($name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
  
    $attributes = array('label' => TRUE, 'activeCount' => TRUE);
  
    $criterion = new stdClass();
    $criterion->attribute = 'name';
    $criterion->value = array('type'=> 'string', 'value' => $name);
    $criterion->comparison = '=';
  
    $filter = array(
      'criteria' => array($criterion),
      'operator' => 'or',
    );

    try {
      $result = $binding->readLists(array(
        'attributes' => $attributes,
        'filter' => $filter,
      ));
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
  
    if (!($result->return->lists) || is_array($result->return->lists)) {
      $result_exp = var_export($result, TRUE);
      $this->set_error_code(-1);
      $this->set_error_message("\$result from readLists() error:<br/> <pre>$result_exp</pre>");
      return FALSE;
    }
    return $result->return->lists;
  }

  protected function get_all_lists() {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }

    $attributes = array('label' => TRUE, 'activeCount' => TRUE);
  
    $filter = array();
  
    try {
      $result = $binding->readLists(array(
        'attributes' => $attributes,
        'filter' => $filter,
      ));
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }  

    if (!$result->return->lists) {
      $result_exp = var_export($result, TRUE);
      $this->set_error_code(-1);
      $this->set_error_message("\$result from readLists() error:<br/> <pre>$result_exp</pre>");
      return FALSE;
    }
    
    if (!is_array($result->return->lists)) {
      return array($result->return->lists);
    }
    else {
      return $result->return->lists;
    }
  }
  
  protected function get_contact_by_email($email, $source = 'Not specified') {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
    
    $attributes = array(
      'status' => TRUE,
      'msgPref' => TRUE,
      'created' => TRUE,
      'modified' => TRUE,
      'source' => TRUE,
      'customSource' => TRUE,
      'lists' => TRUE,
    );
  
    $criterion = new stdClass();
    $criterion->attribute = 'email';
    $criterion->value = array('type' => 'string', 'value' => $email);
    $criterion->comparison = '=';
  
    $filter = array(
      'criteria' => array($criterion),
    );
  
    try {
      $result = $binding->readContacts(
        array(
          'attributes' => $attributes,
          'filter' => $filter,
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }
        
    if (!$result->return->contacts->id) {
      // add the person, then query again
      $contact = new stdClass();
      $contact->email = $email;
      $contact->status = 'active';
      $contact->msgPref = 'html';
      $contact->customSource = $source;
  
      $handler = array(
        'mode' => 'insert',
      );
    
      try {
        $result = $binding->writeContacts(
          array(
            'contacts' => array($contact),
            'handler' => $handler,
          )
        );
      }
      catch(SoapFault $exception) {
        $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
        $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
        return FALSE;
      }
    
      if (!$result->return->result->id) {
        $this->set_error_code(-1);
        $this->set_error_message("get_contact_by_email(): contact for '$email' does not exist and attempt to create new contact fails");
        return FALSE;
      }
  
      try {
        $result = $binding->readContacts(
          array(
            'attributes' => $attributes,
            'filter' => $filter,
          )
        );
      }
      catch(SoapFault $exception) {
        $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
        $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
        return FALSE;
      }
    }
    return $result->return->contacts;
  }

  protected function get_field_id($name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }

    $criterion = new stdClass();
    $criterion->attribute = 'name';
    $criterion->value = array('type' => 'string', 'value' => $name);
    $criterion->comparison = '=';
  
    $filter = array(
      'criteria' => array($criterion),
    );
  
    try {
      $result = $binding->readFields(
        array(
          'attributes' => array(),
          'filter' => $filter,
        )
      );
    }
    catch(SoapFault $exception) {
      $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
      $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
      return FALSE;
    }

    if (!isset($result->return->fields)) {
      $this->set_error_code(-1);
      $this->set_error_message("get_field_id(): field ID for '$name' not found");
      return FALSE;
    }
    if (is_array($result->return->fields)) {
      $this->set_error_code(-1);
      $this->set_error_message("Multiple fields found for field name '$name'.");
      return FALSE;
    }
    return $result->return->fields->id;
  }

  protected function create_message($subject, $body, $footer = '', $type = 'text') {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
  
    $body .= "<br/><br/>-----------------------------------------------<br/>" . ($footer ? $footer . '<br/>' : '') . "<a href='%%!unsubscribe_url%%'>Unsubscribe</a> from all future messages.<br/>";
    $content = array(
      'subject' => $subject,
      'content' => $body,
      'type' => $type == 'text' ? $type : 'html',
    );
  
    $message_folder = $this->get_message_folder_by_name('Messages');
    if (!$message_folder) {
      return FALSE;
    }
  
    $message->content = $content;
    $message->name = $subject;
    $message->status = 'approved';
    $message->messageFolderId = $message_folder->id;
  
    try {
      $result = $binding->writeMessages(
        array(
          'messages' => array($message),
          'handler' => array('mode' => 'insertUpdate', 'contentMode' => 'insertUpdate')
        )
      );
    }
    catch(SoapFault $exception) {
       $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
       $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
       return FALSE;
    }

    if ($result->return->result->success) {
      return $result->return->result->id;
    }
    $result_exp = var_export($result, TRUE);
    $this->set_error_code(-1);
    $this->set_error_message("\$result from readLists() error:<br/> <pre>$result_exp</pre>");
    return FALSE;
  }

  protected function get_message_folder_by_name($name) {
    $binding = $this->get_binding();
    if (!$binding) {
      return FALSE;
    }
  
    $criterion->attribute = 'name';
    $criterion->value = array('type' => 'string', 'value' => $name);
    $criterion->comparison = '=';
  
    try {
      $result = $binding->readMessageFolders(
        array(
          'attributes' => array(),
          'filter' => array(
            'criteria' => array($criterion)
          ),
        )
      );
    }
    catch(SoapFault $exception) {
       $this->set_error_code($exception->faultcode . '::' . $exception->faultstring);
       $this->set_error_message($exception->detail->fault->code . '::' . $exception->detail->fault->message);
       return FALSE;
    }
 
    if (!($result->return->messageFolders) || is_array($result->return->messageFolders)) {
      $this->set_error_code(-1);
      $this->set_error_message("function get_message_folder_by_name() received more than one result in SOAP reply");
      return FALSE;
    }
    
    return $result->return->messageFolders;
  }
}