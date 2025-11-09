TARGET = libluraylib.so
SRC = Raylib.c
OBJ = $(SRC:.c=.o)

CC = clang
CFLAGS = -Wall -Wextra -fPIC -std=c23 -I/usr/local/include/luna
LDFLAGS = -shared -L/usr/local/lib/x86_64-linux-gnu -Wl,-rpath=/usr/local/lib/x86_64-linux-gnu \
           -llunarun -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p /usr/local/lib/luna | cp $(TARGET) /usr/local/lib/luna

clean:
	rm -f $(OBJ) $(TARGET)
