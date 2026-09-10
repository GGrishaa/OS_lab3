CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: server client1 client2 client3

run: run_s run_c1 run_c2 run_c3

server: server.c
	@$(CC) $(CFLAGS) $< -o $@

client1: client1.c
	@$(CC) $(CFLAGS) $< -o $@

client2: client2.c
	@$(CC) $(CFLAGS) $< -o $@

client3: client3.c
	@$(CC) $(CFLAGS) $< -o $@

run_s: server
	@echo "\n======================================== СЕРВЕР НАЧАЛ РАБОТУ ========================================\n"
	@./server || true
	@echo "\n======================================== СЕРВЕР ЗАКОНЧИЛ РАБОТУ ========================================\n"

run_c1: client1
	@echo "\n======================================== КЛИЕНТ 1 НАЧАЛ РАБОТУ ========================================\n"
	@./client1 || true
	@echo "\n======================================== КЛИЕНТ 1 ЗАКОНЧИЛ РАБОТУ ========================================\n"

run_c2: client2
	@echo "\n======================================== КЛИЕНТ 2 НАЧАЛ РАБОТУ ========================================\n"
	@./client2 || true
	@echo "\n======================================== КЛИЕНТ 2 ЗАКОНЧИЛ РАБОТУ ========================================\n"

run_c3: client3
	@echo "\n======================================== КЛИЕНТ 3 НАЧАЛ РАБОТУ ========================================\n"
	@./client3 || true
	@echo "\n======================================== КЛИЕНТ 3 ЗАКОНЧИЛ РАБОТУ ========================================\n"

clean:
	rm -f server client1 client2 client3
	(ipcs -q | grep -q 3039) && ipcrm -Q 12345 || true
	clear

rebuild: clean all

stat:
	ipcs -q

clang:
	touch .clang-format
	echo "---" > .clang-format
	echo "BasedOnStyle: Google" >> .clang-format
	clang-format -i *.c
	rm -f .clang-format
	clear

.PHONY = all run server client1 client2 client3 run_s run_c1 run_c2 run_c3 clean rebuild clang