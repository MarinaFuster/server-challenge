#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

/*
** AUXILIAR FUNCTIONS
*/

void clean_buffer(char * buffer){
    for(int i=0;i<256;i++)
        buffer[i]='\0';
}


int main(int argc , char *argv[])
{
	// creates socket
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	// specifies an address for the socket
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; // shortcut for 0.0.0.0
	server.sin_port = htons(9003); // port number and htons converts it to the appropiate data format

	// connects to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) == 0)
	{

		// second challenge: entendido
		char ch2[11] = {'e', 'n', 't', 'e', 'n', 'd', 'i','d','o','\n','\0'};
		puts(ch2);
		sleep(3);
		send(socket_desc , ch2 , strlen(ch2) , 0);
		
		
		// third challenge: #0854780*
		char ch3[11] = {'#','0','8','5','4','7','8','0','*','\n','\0'};
		puts(ch3);
		sleep(3);
		send(socket_desc , ch3 , strlen(ch3) , 0);
		
		
		// fourth challenge: nokia
		char ch4[7] = {'n','o','k','i','a','\n','\0'};
		puts(ch4);
		sleep(3);
		send(socket_desc , ch4 , strlen(ch4) , 0);
		

		// fifth challenge: cabeza de calabaza
		char ch5[20] = {'c','a','b','e','z','a',' ','d','e',' ','c','a','l','a','b','a','z','a','\n','\0'};
		puts(ch5);
		sleep(3);
		send(socket_desc , ch5 , strlen(ch5) , 0);


		// sixth challenge: easter_egg
		char ch6[12] = {'e','a','s','t','e','r','_','e','g','g','\n','\0'};
		puts(ch6);
		sleep(3);
		send(socket_desc , ch6 , strlen(ch6) , 0);


		// seventh challenge: .runme
		char ch7[8] = {'.','r','u','n','m','e','\n','\0'};
		puts(ch7);
		sleep(3);
		send(socket_desc , ch7 , strlen(ch7) , 0);
		

		// eighth challenge: indeterminado
		char ch8[15] = {'i','n','d','e','t','e','r','m','i','n','a','d','o','\n','\0'};
		puts(ch8);
		sleep(3);
		send(socket_desc , ch8 , strlen(ch8) , 0);


		// ninth challenge: this is awesome
		char ch9[17] = {'t','h','i','s',' ','i','s',' ','a','w','e','s','o','m','e','\n','\0'};
		puts(ch9);
		sleep(3);
		send(socket_desc , ch9 , strlen(ch9) , 0);

		// tenth challenge: cachiporra
		char ch10[12] = {'c','a','c','h','i','p','o','r','r','a','\n','\0'};
		puts(ch10);
		sleep(3);
		send(socket_desc , ch10 , strlen(ch10) , 0);
		

		// eleventh challenge: gdb rules
		char ch11[11] = {'g','d','b',' ','r','u','l','e','s','\n','\0'};
		puts(ch11);
		sleep(3);
		send(socket_desc , ch11 , strlen(ch11) , 0);


		// twelveth challenge: /lib/x86_64-linux-gnu/ld-2.19.so
		char ch12[34] = {'/','l','i','b','/','x','8','6','_','6','4','-','l','i','n','u','x','-','g','n','u','/','l','d','-','2','.','1','9','.','s','o','\n','\0'};
		puts(ch12);
		sleep(3);
		send(socket_desc , ch12 , strlen(ch12) , 0);

	}
	else{
		puts("Connection error");
	}

	// close socket once we are done
	close(socket_desc);

	return 0;
}
