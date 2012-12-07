
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define bool unsigned int
#define true (1)
#define false (0)
#define ERL_MSG_HEADER_SIZE ((size_t)2)
#define ERL_MSG_MAX_SIZE ((size_t)65536)
#define byte_t unsigned char

static size_t packet_size(byte_t buff[ERL_MSG_HEADER_SIZE]) {
    int len;
	len = (buff[0] << 8) | buff[1];
	return len;
}

int main(int argc, char** argv) {
	bool bShutdown = false;
	fprintf(stderr, "Entering the loop.\n");
	while ( !bShutdown ) {
		byte_t packet_size_buff[ERL_MSG_HEADER_SIZE];
		byte_t packet_payload[ERL_MSG_MAX_SIZE];
		ssize_t bytes_read = 0;
		bytes_read = read(fileno(stdin), (void*) packet_size_buff, ERL_MSG_HEADER_SIZE);
		if ( bytes_read > 0 ) {
			size_t bytes_to_read = packet_size(packet_size_buff);
			fprintf(stderr, "Packet size: %d\n", bytes_to_read);

			bytes_read = read(fileno(stdin), (void*) packet_payload, bytes_to_read);
			if ( bytes_read != bytes_to_read ) {
				// fprintf(stderr, "wrong bytes_read: %d. Expected: %d\n. Errno: %s\n", bytes_read, bytes_to_read, strerror(errno));
				bShutdown = true;
			}
			else {
				// process(packet_payload, bytes_to_read);
			}
		}
		else {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			bShutdown = true;
		}
	}
	fprintf(stderr, "Left the loop. Quitting.\n");
}
