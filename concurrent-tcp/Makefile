all: client server

client: mpTcpClient.c
	gcc -Wall -o client mpTcpClient.c

server: mpTcpServer.c
	gcc -Wall -o server mpTcpServer.c -lpthread

clean:
	rm server client
