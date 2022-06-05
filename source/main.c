#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* todo:
 - parse options from command-line arguments and/or environment variables (and help argument!)
 - read message from file and store in memory
 - create tcp socket & bind to ip/port
 - create thread to listen for incoming connections
 - when new connection is established, create new thread, send message in that thread, then close once done
 - handle sigterm/sigint
*/

/* options:
--help / -h
	show program name, version (Telnet, v0.1.0)
	show author, contact website (viral32111, https://viral32111.com/contact)
	show license (The Unlicense, https://unlicense.org/)
	show program options
	show program signals
	show program example usage

--message <path> \ -m <path> \ TELNET_MESSAGE
	set the path to the message file
	default ./message.txt

--address <ip> \ -a <ip> \ TELNET_ADDRESS
	set the interface ip address to listen on
	default 0.0.0.0 (all interfaces)

--port <number> \ -p <num> \ TELNET_PORT
	set the port number to listen on
	default 23 (telnet)

--delay <milliseconds> \ -d <ms> \ TELNET_DELAY
	set the delay between sending each character
	default 0 (all at once, no delay)
*/

/* help:
Telnet, version 0.1.0.
Created by viral32111 (https://viral32111.com).

Usage: telnet [options...]
Example: telnet --message /home/bob/fun.txt -a 123.123.123.123 --delay 100

Options can be passed either through command-line arguments, or through environment
variables. The former will take priority.

Options:
	-m, --message <path> (TELNET_MESSAGE)
		The path to a text document containing the message to send when a client connects.
		The file will be created with an example message if it does not exist.
		By default this is 'message.txt' in the current working directory.

	-a, --address <ip> (TELNET_ADDRESS)
		The IP address of the interface to listen for incoming connections on.
		By default this is 0.0.0.0, which listens on all interfaces.

	-p, --port <number> (TELNET_PORT)
		The port number to listen for incoming connections on.
		Ports below 1024 require root privileges to use.
		By default this is the default telnet port 23.

	-d, --delay <milliseconds> (TELNET_DELAY)
		The time in milliseconds to wait between sending each character of the message.
		By default this is 0, which will send the whole message in one go.

Signals:
	SIGINT (2), SIGTERM (15)
		Instantly send any remaining messages, disconnect all active clients, and stop listening for new connections.

The program will write detailed logs of incoming connections and messages to stdout,
while any warnings and errors encountered will be written to stderr.

This is free and unencumbered software released into the public domain.
For more information, please refer to https://unlicense.org.
*/

int main( int argument_count, char* argument_values[], char* environment_variables[] ) {
	char* option_message = "message.txt";
	char* option_address = "0.0.0.0";
	unsigned short option_port = 23;
	unsigned int option_delay = 0;

	for ( int index = 1; index < argument_count; index++ ) {
		char* argument_value = argument_values[ index ];

		if ( strncmp( argument_value, "--", 2 ) != 0 ) continue;

		argument_value += 2;

		if ( strlen( argument_value ) == 0 ) {
			printf( "No option name supplied!\n" );
			exit( 1 );
		}

		if ( strcmp( argument_value, "help" ) == 0 ) {
			printf( "Usage: telnet [--message <path>] [--address <ip>] [--port <number>] [--delay <milliseconds>]\n" );
			continue;

		} else if ( strcmp( argument_value, "message" ) == 0 ) {
			if ( ( index + 1 ) >= argument_count ) {
				printf( "No value given for option!\n" );
				exit( 1 );
			}
			option_message = argument_values[ index + 1 ];
			continue;

		} else if ( strcmp( argument_value, "address" ) == 0 ) {
			if ( ( index + 1 ) >= argument_count ) {
				printf( "No value given for option!\n" );
				exit( 1 );
			}
			option_address = argument_values[ index + 1 ];
			continue;

		} else if ( strcmp( argument_value, "port" ) == 0 ) {
			if ( ( index + 1 ) >= argument_count ) {
				printf( "No value given for option!\n" );
				exit( 1 );
			}
			option_port = ( unsigned short ) strtol( argument_values[ index + 1 ], NULL, 10 );
			continue;

		} else if ( strcmp( argument_value, "delay" ) == 0 ) {
			if ( ( index + 1 ) >= argument_count ) {
				printf( "No value given for option!\n" );
				exit( 1 );
			}
			option_delay = ( unsigned short ) strtol( argument_values[ index + 1 ], NULL, 10 );
			continue;

		} else {
			printf( "Unrecognised option '--%s'!\n", argument_value );
			exit( 1 );
		}
	}

	printf( "Message is '%s'\n", option_message );
	printf( "Address is '%s'\n", option_address );
	printf( "Port is '%d'\n", option_port );
	printf( "Delay is '%d'\n", option_delay );

	return 0;
}
