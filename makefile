LIBS = -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm -lXi

default: cube

cube: *.h *.cpp 
	g++ -o cube *.cpp *.c $(LIBS)

clean :
	rm -rf *.o cube
