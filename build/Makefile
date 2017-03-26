#compilation
CC = clang -std=gnu++11


InputManager.o : ../InputManager.cpp
	$(CC) -c ../InputManager.cpp -I ../

EventSubscriber.o : ../EventSubscriber.cpp
	$(CC) -c ../EventSubscriber.cpp -I ../

Event.o : ../Event.cpp
	$(CC) -c ../Event.cpp -I ../

EventHandler.o : ../EventHandler.cpp
	$(CC) -c ../EventHandler.cpp -I ../

Component.o : ../Component.cpp
	$(CC) -c ../Component.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

GameObject.o : ../GameObject.cpp
	$(CC) -c ../GameObject.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Light.o : ../Light.cpp
	$(CC) -c ../Light.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Mesh.o : ../Mesh.cpp
	$(CC) -c ../Mesh.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Obj2.o : ../Obj2.cpp
	$(CC) -c ../Obj2.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

ShaderManager.o : ../ShaderManager.cpp
	$(CC) -c ../ShaderManager.cpp -I ../
	
Geo2D.o : ../Geo2D.cpp
	$(CC) -c ../Geo2D.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx

#-------------------------------------------------------------

Scene.o : ../Scene.cpp
	$(CC) -c ../Scene.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src

glew.o : ../glew.c
	clang -c ../glew.c -I ../

Main.o : ../Main.cpp
	$(CC) -c ../Main.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src


#linking
all: Main.o glew.o Scene.o  InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Geo2D.o
	$(CC) -o ../bin/kek-engine-v2 Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o Geo2D.o -rdynamic -L ../bullet/src/BulletSoftBody -L ../bullet/src/BulletDynamics -L ../bullet/src/BulletCollision -L ../bullet/src/LinearMath -L ../SDL2_image/libs -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++
	#$(CC) -o softRend Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o ../SDL2libs/libSDL2.so -lm -lstdc++ -lGL

clean:
	rm -f *.o
