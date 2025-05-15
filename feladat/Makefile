
CC = C:/Users/Andris/Desktop/Parhuzamos_Grafika/c_sdk_220203/MinGW/bin/gcc
CFLAGS = -Iinclude -std=c99 -Wall -O2
LDFLAGS = -lfreeglut -lopengl32 -lglu32 -lm

SRC = src/main.c \
      src/camera.c \
      src/model.c \
      src/texture.c \
      src/shader.c \
      src/stb_image.c \
      src/glad.c

OBJ = $(SRC:.c=.o)
EXE = space.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del src\*.o $(EXE) 2>nul || rem
