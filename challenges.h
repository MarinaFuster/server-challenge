#ifndef __CHALLENGES__
#define __CHALLENGES__

#define CHALLENGE_TXT "------------- DESAFIO -------------\n"
#define QUESTION_TXT "----- PREGUNTA PARA INVESTIGAR -----\n"

#define INITIAL_MESSAGE "En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\n\
Además tendrán que investigar otras preguntas para responder durante la defensa.\n\
El desafío final consiste en crear un servidor que se comporte igual que yo, además del\n\
cliente para comunicarse con el mismo.\n\n\
Deberán estar atentos a los desafios ocultos.\n\n\
Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con \"entendido\\n\""

#define FINAL_MESSAGE "Felicitaciones! Completaste los desafios del server replicado\n"

#define SECOND_Q "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n"
#define THIRD_Q "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n"
#define FOURTH_Q "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n"
#define FIFTH_Q "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n"
#define SIXTH_Q "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n"
#define SEVENTH_Q "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n"
#define EIGHTH_Q "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n"
#define NINTH_Q "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n"
#define TENTH_Q "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n"
#define ELEVENTH_Q "¿Cuáles son las características del protocolo SCTP?\n"
#define TWELVETH_Q "¿Qué es un RFC?\n"

#define GCC_PATH "/usr/bin/gcc"
#define SELF_PATH "./server_functions.c"

#endif // __CHALLENGES__