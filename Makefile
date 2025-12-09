SRC_DIR = ./src
LIB_DIR = ./lib
RAYLIB_DIR = $(LIB_DIR)/raylib

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:.c=.o)

CFLAGS = -L $(RAYLIB_DIR) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL $(RAYLIB_DIR)/libraylib.a 

rasterizer: $(OBJS)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f $(OBJS) rasterizer
	