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
