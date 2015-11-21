#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>

struct Packet
{
	int id;
	char msg[BUFSIZ];
};


#endif