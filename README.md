Easylogging++ Remote Server
===========================

Deamon tool that runs in the background and listens to TCP connection to control Easylogging++ back-end and write logs remotely.

**This is currently being developed.**

---

Server Requests:
----------------

You can send request to this server in JSON format, this is only acceptable format. This format was chosen because of it's simplicity and size. Different request types have different json key/value pairs required.

#### All Requests
|      Key      |                  Description                                  |
|---------------|---------------------------------------------------------------|
| user          | Username for server to send request. (For security purposes)  |
| pwd           | Password for username. (For security purposes)                |
| type          | Type of request you are sending, this is integral value       |

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
