#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "challenges.h"

char client_answer[256]={0};

/*
** AUXILIAR FUNCTIONS
*/

// function from https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
void clrscr(){
    system("@cls||clear");
}

void clean_buffer(char * buffer){
    int i;
    for(i=0;i<256;i++)
        buffer[i]='\0';
}

void encode_answer(char random_message[181]){

    srand(time(0));
    // fills message with random letters
    int i;
    for(i=0; i<180; i++){
        random_message[i] = 'a'+((rand() % (25 + 1 - 0)) + 0);
    }
    random_message[180]='\0';

    // generates six spaces
    int spaces[8];
    spaces[0]=0;
    spaces[7]=179;

    char * words[]={"la", "respuesta", "a", "este", "acertijo", "es", "indeterminada"};
    int words_length=sizeof(words)/sizeof(sizeof(words[0]));
    int word_size=2;

    for(i=0; i<6; i++){
        int index = (30*i) + ((rand() % (29 + 1 - 0)) + 0);

        if(i==5){
          word_size=strlen(words[i+1]);
          if(180-index<word_size){
            index-=word_size;
          }
        }
        else if(i!=0){
          word_size=strlen(words[i]);
          if(index-spaces[i]<word_size){
            index+=word_size-(index-spaces[i+1]);
          }
        }

        // this is not entirely correct, it could fail in a very special case
        if( index==0 || (index>0 && random_message[index-1]==' ')){  // For not having two contiguos spaces or at the beginning
            random_message[index+1]=' ';
            spaces[i+1]=index+1;
        }
        else if( index==179 ){
            random_message[index-1]=' ';
            spaces[i+1]=index-1;
        }
        else{
            random_message[index]=' ';
            spaces[i+1]=index;
        }
    }


    // hides the answer in the message
     for (int i=0; i<words_length; i++){
       int to_insert_size=spaces[i+1]-spaces[i];  // CHECKED
       word_size=strlen(words[i]);
       int zone_size=to_insert_size/word_size;
       printf("BETWEEN SPACES: %d\n",to_insert_size);
       printf("ZONE: %d\n",zone_size );
       printf("WORD SIZE: %d\n",word_size );
       printf("----------\n");
       int prev_zone=spaces[i];
       for (int j=0; j<word_size; j++){
         int position=(rand() % (zone_size)) + prev_zone;  // Generates position in first word of ANSWER to insert the letter

         if(position==spaces[i]){
           position++;
         }
         else if(position==spaces[i+1]){
           position--;
         }
         else if(position>spaces[i+1]){
           printf("SE PASO\n" );
         }
         random_message[position]=(words[i])[j]-32;
         prev_zone+=zone_size;
       }
     }

}


/*
** CHALLENGES
*/

//Challenges are listed in reverse order (12th --> 1st)

void execute_challenge(char * challenge, char * question, char * answer, int client_socket){
    printf("%s",CHALLENGE_TXT);
    printf("%s\n\n",challenge);
    printf("%s",QUESTION_TXT);
    printf("%s",question);
    do{
        clean_buffer(client_answer);
        recv(client_socket, &client_answer, sizeof(client_answer), 0);
    }while(strcmp(client_answer, answer)!=0);
    printf("Respuesta correcta\n");
    clrscr();
}

void libc(int client_socket){
    char * challenge="/lib/x86_64-linux-gnu/libc-2.19.so ?";
    char * answer="/lib/x86_64-linux-gnu/ld-2.19.so\n";
    execute_challenge(challenge, TWELVETH_Q, answer, client_socket);
    puts(FINAL_MESSAGE);
}

void gdbmeres(){
  if(0x0 == 0x12345){
    char * right = "gdb rules\n";
  }else{
    char * wrong = "try again\n";
  }
}

void gdbme(int client_socket){
    char * challenge="b gdbme y encontrá el valor mágico\ntry again";
    char * answer="gdb rules\n";
    gdbmeres();
    execute_challenge(challenge, ELEVENTH_Q, answer, client_socket);
    libc(client_socket);
}

void quine(int client_socket){

    int exit_status;
    exit_status=system("gcc -o ./quine.o ./quine.c; ./quine.o");

    if(exit_status==EXIT_SUCCESS){
        char * challenge="La respuesta a este desafio es cachiporra";
        char * answer="cachiporra\n";
        execute_challenge(challenge, TENTH_Q, answer, client_socket);
        gdbme(client_socket);
    }
    else{
        printf("There is something wrong!!!\n");
        sleep(3);
        clrscr();
        quine(client_socket);
    }
}

void many_words(int client_socket){
    char * challenge="Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo";
    char * answer="this is awesome\n";
    execute_challenge(challenge, NINTH_Q, answer, client_socket);
    quine(client_socket);
}

void mixed_fds(int client_socket){
  char challenge_message[181];

  char * answer="indeterminado\n";
  do{
      encode_answer(challenge_message);
      clrscr();
      printf("%s",CHALLENGE_TXT);
      printf("%s\n\n",challenge_message);
      printf("%s",QUESTION_TXT);
      printf("%s",EIGHTH_Q);
      clean_buffer(client_answer);
      recv(client_socket, &client_answer, sizeof(client_answer), 0);
  }while(strcmp(client_answer, answer)!=0);
  printf("Respuesta correcta\n");
  clrscr();
  many_words(client_socket);
}

void sections(int client_socket){
    char * challenge=".data .bss .comment ? .shstrtab .symtab .strtab";
    char * answer=".runme\n";
    execute_challenge(challenge, SEVENTH_Q, answer, client_socket);
    mixed_fds(client_socket);
}

void pumpkin(int client_socket){
  //If new strings created then this number could change!
    char * challenge="respuesta = strings[86]";
    char * answer="easter_egg\n";
    execute_challenge(challenge, SIXTH_Q, answer, client_socket);
    sections(client_socket);
}

void ebadf(int client_socket){
    char * challenge="EBADF... abrilo y verás";
    char * answer="cabeza de calabaza\n";
    if(fork()==0){
      write(10,answer,sizeof(*answer)); //Write in a wrong file descriptor
    }else{
      execute_challenge(challenge, FIFTH_Q, answer, client_socket);
      pumpkin(client_socket);
    }
}

void vocaroo(int client_socket){
    char * challenge="https://vocaroo.com/i/s19015zmR4t8";
    char * answer="nokia\n";
    execute_challenge(challenge, FOURTH_Q, answer, client_socket);
    ebadf(client_socket);
}

void shoot_challenges(int client_socket){
    char * challenge="# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *";
    char * answer="#0854780*\n";
    execute_challenge(challenge, THIRD_Q, answer, client_socket);
    vocaroo(client_socket);
}
int createSection __attribute__((section(".runme")));
