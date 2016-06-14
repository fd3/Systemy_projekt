CC = gcc
ARGS = -Wall
CLIENT_NAME = klient
SERVER_NAME = serwer
all: $(CLIENT_NAME) $(SERVER_NAME)
$(CLIENT_NAME): klient.c biblioteki/biblioteka.h biblioteki/biblioteka.c
	$(CC) $(ARGS) -o $(CLIENT_NAME) klient.c biblioteki/biblioteka.h biblioteki/biblioteka.c
$(SERVER_NAME): serwer.c biblioteki/biblioteka.h biblioteki/biblioteka.c
	$(CC) $(ARGS) -o $(SERVER_NAME) serwer.c biblioteki/biblioteka.h biblioteki/biblioteka.c
clean:
	rm -f $(CLIENT_NAME)
	rm -f $(SERVER_NAME)
