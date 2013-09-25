<?php

class RemoteConnection {

    private $server_host;
    private $server_port;
    private $sock;

    private static $instance; 

    private function __construct() {
        $this->server_host = "127.0.0.1";
        $this->server_port = 1592;
    }

    function __destruct() {
    }

    public static function getInstance() { 
        if(!self::$instance) { 
            self::$instance = new self(); 
        } 
        return self::$instance;
    } 

    public function connect() {
        $this->sock = socket_create(AF_INET, SOCK_STREAM, 0);
        socket_connect($this->sock, $this->server_host, $this->server_port) or die("Could not estabilish connection to server");
    }

    public function disconnect() {
        socket_close($this->sock);
    }

    public function read() {
        return socket_read($this->sock, 1024);
    }

    public function write($msg) {
        $this->connect();
        $sent = socket_write($this->sock, $msg, strlen($msg));
        $this->disconnect();
        return $sent !== false;
    }
}

class el {
    const Debug = 2;
    const Info = 4;
    const Warning = 8;
    const Error = 16;
    const Fatal = 32;
    const Trace = 64;
    const Verbose = 128;

    public static function write($msg, $level, $logger = "remote") {
        return RemoteConnection::getInstance()->write(el::buildMsg($msg, $level, $logger));
    }
 
    public static function registerLogger($loggerId, $conf) {
        return RemoteConnection::getInstance()->write(el::newLogger($loggerId, $conf));
    }

    private static function buildMsg($msg, $level, $logger) {
       $msgArr['user'] = "mkhan";
       $msgArr['pwd'] = "pass";
       $msgArr['type'] = (int)1;        // 0 = Log
       $msgArr['level'] = (int)$level;
       $msgArr['logger'] = $logger;
       $msgArr['log'] = $msg;
       $msgArr['vlevel'] = (int)0;
       $msgArr['func'] = "func";
       $msgArr['file'] = "file";
       $msgArr['line'] = (int)0;
       return json_encode($msgArr);
    }
    
    private static function newLogger($loggerId, $conf) {
       $msgArr['type'] = (int)2;      // 2 = NewLogger
       $msgArr['logger'] = $loggerId;
       $msgArr['configuration'] = $conf;
       return json_encode($msgArr);
    }
}

  el::write("Flying high...", el::Info);
  el::registerLogger("r", "");
  el::write("New Logger", el::Info, "r");
?>

