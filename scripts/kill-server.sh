kill -9 $(netstat -tulnap | grep -o '[0-9]*\/remote-server' | grep -o '[0-9]*')
