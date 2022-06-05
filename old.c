/* Code from https://github.com/viral32111/telnet */

#include <stdio.h> // printf
#include <string.h> // strlen
#include <unistd.h> // write
#include <sys/socket.h> // socket
#include <arpa/inet.h> // inet_addr
#include <sys/types.h> // ssize_t

int main( int argc, char *args[], char *env[] ) {

	int socket_server = socket( AF_INET, SOCK_STREAM, 0 );
	if ( socket_server == -1 ) {
		printf( "failed to create socket.\n" );
		return 1;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	if ( bind( socket_server, ( struct sockaddr * ) &server, sizeof( server ) ) < 0 ) {
		printf( "failed to bind socket.\n" );
		return 1;
	}

	listen( socket_server, 3 );

	printf( "Waiting for incoming connections...\n" );

	int c = sizeof( struct sockaddr_in );
	struct sockaddr_in client;
	int socket_client = accept( socket_server, ( struct sockaddr * ) &client, ( socklen_t * ) &c );
	if ( socket_client < 0 ) {
		printf( "failed to accept socket.\n" );
		return 1;
	}

	char *client_ip = inet_ntoa( client.sin_addr );
	int client_port = ntohs( client.sin_port );
	printf( "Client %s:%d connected.\n", client_ip, client_port );

	char *message = "Hello World.";
	ssize_t sent_bytes = write( socket_client, message, strlen( message ) );
	printf( "Sent %ld bytes to %s:%d.\n", sent_bytes, client_ip, client_port );

	if ( close( client_port ) == -1 ) {
		printf( "failed to close client.\n" );
		return 1;
	};

	printf( "Closed connection to client.\n" );

	return 0;

}
