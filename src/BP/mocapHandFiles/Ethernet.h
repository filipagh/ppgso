//Ethernet.h
//All SOCKETs have been made void *
//to avoid the need to include winsock2.h everywhere

typedef void *SynSocket;

int StartEthernet();
void StopEthernet();

//Open a UDP connection for reading
//Sets sock to the socket
//Returns one of SynErrorEnum
//Returns 0 if success
int EthernetOpenForRead(SynSocket &sock, uint16_t port);

//Open a UDP connection for writing
//Sets sock to the socket
//Returns one of SynErrorEnum
//Returns 0 if success
int EthernetOpenForWrite(SynSocket &sock);

//Close the connection if open
void EthernetClose(SynSocket &sock);

//Read a datagram into buffer, up to size bytes
//Returns number of bytes read, possibly 0
//Returns -1 if connection closed
int EthernetRead(SynSocket sock, void *buffer, int size);

//Write a datagram from buffer, size bytes
//Returns 0 if success
int EthernetWrite(SynSocket sock, void *buffer, int size);
