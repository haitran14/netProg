MAKE_DIR = $(shell pwd)
SRC_DIR = $(MAKE_DIR)/src
BIN_DIR = $(MAKE_DIR)/bin
P_THREAD = -pthread

all: select_server multi_server client

select_server: $(SRC_DIR)/select_server.c $(SRC_DIR)/select_server_utilities.o $(SRC_DIR)/common_utilities.o
	$(CC) $^ -o $(BIN_DIR)/$@

multi_server: $(SRC_DIR)/multi_server.c $(SRC_DIR)/multi_server_utilities.o $(SRC_DIR)/common_utilities.o
	$(CC) $^ -o $(BIN_DIR)/$@

client: $(SRC_DIR)/client.c $(SRC_DIR)/client_utilities.o $(SRC_DIR)/common_utilities.o
	$(CC) $(P_THREAD) $^ -o $(BIN_DIR)/$@

%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm $(SRC_DIR)/*.o
	rm $(BIN_DIR)/*
