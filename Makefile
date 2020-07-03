game:
	gcc -Wall src/main.c src/gameWindow.c src/shaders.c gl3w-master/src/gl3w.c -o \
	build/play \
	-I include \
	-L lib \
	-l SDL2-2.0.0 \
	-Wno-deprecated
