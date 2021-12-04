#pragma comment(lib, "WS2_32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

#define BUFFER_LENGTH 1024
#define MAX_CLIENTS 1
#define ERROR -1

int print_message(char *_buffer, unsigned long _buffer_length)
{
	printf("> ");

	for (unsigned long iterator = 0; iterator < _buffer_length; iterator++ )
	{
		printf("%c", _buffer[iterator]);
	}
	printf("\n");

	return 0;
}

int main(int num_arguments, const char *args[])
{
	WSADATA ws;

	if (FAILED(WSAStartup(MAKEWORD(1, 1), &ws)))
	{
		perror("# No WinSock2.lib started");
		exit(-1);
	}

	//if (num_arguments == 3)
	//{
		int _port = 7; //atoi(args[1]);
		int _max_clients = 1; // atoi(args[2]);
	//}
	

	SOCKET _server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (_server_socket == NULL)
	{
		perror("# Socket: ");
		//printf("# No socket\n");
		exit(-1);
	}



	struct sockaddr_in _server_address;

	_server_address.sin_family = AF_INET;
	_server_address.sin_port = htons(7);
	_server_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);



	if (bind(_server_socket, (struct sockaddr *)&_server_address, sizeof(struct sockaddr_in)) == ERROR)
	{
		perror("# Bind: ");
		//printf("# No bind\n");
		exit(-1);
	}



	if (listen(_server_socket, _max_clients) == ERROR)
	{
		perror("# Listen: ");
		exit(-1);
	}



	char *_buffer = (char *)malloc(BUFFER_LENGTH * sizeof(char));

	while (1)
	{
		struct arr_clients
		{
			int number;
			struct sockaddr_in;
		};

		struct arr_clients *_array_clients = (struct arr_clients *)malloc(_max_clients * sizeof(struct arr_clients));

		_array_clients[1].sin_addr = _server_address.sin_addr;

		struct sockaddr_in _client_address;

		int sockaddr_length = sizeof(struct sockaddr_in);
		int _connection = accept(_server_socket, (struct sockaddr *)&_client_address, &sockaddr_length);

		if (_connection == ERROR)
		{
			perror("# Accept: ");
			exit(-1);
		}

		while (1)
		{
			int _recieved_length = recv(_server_socket, _buffer, BUFFER_LENGTH, 0);

			if (_recieved_length == ERROR)
			{
				break;
			}
			else
			{
				_buffer[_recieved_length] = '\0';
				print_message(_buffer, BUFFER_LENGTH);
			}

			send(_connection, _buffer, BUFFER_LENGTH, 0);

		}

		printf("# Disconnected");

		close(_connection);
	}
	
	return 0;
}