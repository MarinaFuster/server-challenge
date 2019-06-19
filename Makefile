COMPILER=gcc
OUTPUT_SERVER_FILE=replicated_server
OUTPUT_CHALLENGE_SOLVED_FILE=challenge_solved

all: replicated_server challenge_solved

challenge_sovled:
	$(COMPILER) -o $(OUTPUT_CHALLENGE_SOVLED_FILE) challenge_solved.c

replicated_server:
	$(COMPILER) -o $(OUTPUT_SERVER_FILE) replicated_server.c server_functions.c

clean:
	rm -rf $(OUTPUT_SERVER_FILE) $(OUTPUT_CHALLENGE_SOLVED_FILE) *.o *.h.gch