all: bloc4 prueba

bloc4: bloc4.o model.h
		g++ bloc4.o model.o -o bloc4 -lGLU -lGL -lglut 

prueba: prueba.o model.h
		g++ prueba.o model.o -o prueba -lGLU -lGL -lglut 

clean: 
	rm -rf *o bloc4 prueba
