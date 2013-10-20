Easylogging++ Remote Server
===========================

Deamon tool that runs in the background and listens to TCP connection to control Easylogging++ back-end and write logs remotely.

**This is currently being developed.**

---

Program Arguments:
------------------

Server takes application arguments in order to configure users, set verbosity level, configure loggers and take care of security measures;

|      Arg      |                  Description                                  |
|---------------|---------------------------------------------------------------|
| `--verbose`     | Sets maximum verbose level for logging                        |
| `--v=X`         | Sets verbose level = X for logging                            |
| `--port`        | Port to run server on, defaults to 1592                       |
| `--loggers-conf`| Path to logger global configuration file                      |
| `--passkey`     | Server passkey to ensure not everyone can start this server   |
| `--users`       | Register users with their passwords and permissions, format: `[username:password=permission_flag]` seperated by comma within square brackets e.g, to register two users; `--users=[john:pass=1,mir:pk1=3]`, this registers john to write logs and mir to write logs and register new loggers.    |

Server Requests:
----------------

You can send request to this server in JSON format, this is only acceptable format. This format was chosen because of it's simplicity and size. Different request types have different json key/value pairs required.

#### All Requests
|      Key      |                  Description                                  |
|---------------|---------------------------------------------------------------|
| user          | Username for server to send request. (For security purposes)  |
| pwd           | Password for username. (For security purposes)                |
| type          | Type of request you are sending, this is integral value (see `requests/RequestType.h` for values)      |

#### Write Logs (type: 1)
|      Key      |                  Description                                  |
|---------------|---------------------------------------------------------------|
| logger        | Logger to write log, defaults to `remote`                     |
| level         | Log severity level (integral value: Debug = 2, Info = 4, Warning = 8, Error = 16, Fatal = 32, Trace = 64,Verbose = 128)  |
| log           | Log message                                                   |
| vlevel        | Verbose level (integer, 0 - 9)                                |
| func          | Log function                                                  |
| file          | Log source file                                               |
| line          | Log line                                                      |
