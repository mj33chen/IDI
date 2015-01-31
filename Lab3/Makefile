all: prueba bloc3

prueba: prueba.o model.h
		g++ prueba.o model.o -o prueba -lGLU -lGL -lglut 

bloc3: bloc3.o model.h
		g++ bloc3.o model.o -o bloc3 -lGLU -lGL -lglut 


clean: 
	rm -rf *o prueba bloc3
