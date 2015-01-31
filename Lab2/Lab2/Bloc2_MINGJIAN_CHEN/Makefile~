all: test prueba legoman bloc2

test: test.cpp 
		g++ test.cpp -o test.o -lglut -lGL  
		
prueba: prueba.o model.h
		g++ prueba.o model.o -o prueba -lGLU -lGL -lglut 

legoman: legoman.o model.h
		g++ legoman.o model.o -o legoman -lGLU -lGL -lglut 
		
bloc2: bloc2.o model.h
		g++ bloc2.o model.o -o bloc2 -lGLU -lGL -lglut 
clean: 
	rm -rf *o test prueba legoman bloc2
