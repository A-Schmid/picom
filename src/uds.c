#include "uds.h"

// TODO: not sure if all of them are needed
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>

int uds_fd;
int uds_running;

// inspired by https://github.com/denehs/unix-domain-socket-example/blob/master/client.c
void uds_init()
{
	printf("init uds\n");
	struct sockaddr_un address;

	if ((uds_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
		perror("failed to create UDS socket");
		return;
	}
	printf("created socket\n");
	
	memset(&address, 0, sizeof(address));
	address.sun_family = AF_LOCAL;
	strcpy(address.sun_path, UDS_PATH);
	//unlink(UDS_PATH);

	if (connect(uds_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("failed to connect UDS socket");
		return;
	}
	printf("connected socket\n");

	uds_running = 1;

}

void uds_send_message(const char* message)
{
	send(uds_fd, message, strlen(message) + 1, 0);
}

void uds_send_start()
{
	printf("send start\n");
	fflush(stdout);
	send(uds_fd, UDS_MESSAGE_START, 2, 0);
}

void uds_send_end()
{
	printf("send end\n");
	fflush(stdout);
	send(uds_fd, UDS_MESSAGE_END, 2, 0);
}

void uds_run()
{
	/*
	char* buffer[1];

	while (uds_running) {
		if (send_start_event)
		{
			strcpy (buffer, "s");
			if (send(uds_fd, buffer, strlen(buffer)+1, 0) == -1) {
				perror("could not send data");
			}
			continue;
		}

		if (send_end_event)
		{
			strcpy (buffer, "e");
			if (send(uds_fd, buffer, strlen(buffer)+1, 0) == -1) {
				perror("could not send data");
			}
		}

	}

	uds_close();
	*/
}

void uds_close()
{
	close(uds_fd);
}
