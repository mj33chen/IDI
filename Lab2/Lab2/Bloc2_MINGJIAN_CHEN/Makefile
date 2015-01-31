all: legoman 


legoman: legoman.o model.h
		g++ legoman.o model.o -o legoman -lGLU -lGL -lglut 
		

clean: 
	rm -rf *o test legoman
