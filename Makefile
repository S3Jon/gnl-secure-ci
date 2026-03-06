# Compilador y flags
CC=gcc
CFLAGS=-Wall -Wextra -Werror -D BUFFER_SIZE=$(BUFFER_SIZE)

SRC=$(wildcard src/*.c)
OUT=app

# Target por defecto
all: build

# Build normal
build:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Build con AddressSanitizer (memory check)
sanitize:
	$(CC) -fsanitize=address $(CFLAGS) $(SRC) -o $(OUT)_san

# Ejecutar tests automáticos
test: build
	chmod +x tests/run_tests.sh
	tests/run_tests.sh

# Limpieza
clean:
	rm -f $(OUT) $(OUT)_san output.txt output2.txt
