#compilation

InputManager.o : ../InputManager.cpp
	gcc -c ../InputManager.cpp -I ../

EventSubscriber.o : ../EventSubscriber.cpp
	gcc -c ../EventSubscriber.cpp -I ../

Event.o : ../Event.cpp
	gcc -c ../Event.cpp -I ../

EventHandler.o : ../EventHandler.cpp
	gcc -c ../EventHandler.cpp -I ../

Component.o : ../Component.cpp
	gcc -c ../Component.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

GameObject.o : ../GameObject.cpp
	gcc -c ../GameObject.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Light.o : ../Light.cpp
	gcc -c ../Light.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Mesh.o : ../Mesh.cpp
	gcc -c ../Mesh.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

Obj2.o : ../Obj2.cpp
	gcc -c ../Obj2.cpp -I ../ -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2/include -I ../SDL2_image -I ../bullet/src

ShaderManager.o : ../ShaderManager.cpp
	gcc -c ../ShaderManager.cpp -I ../

#-------------------------------------------------------------

Scene.o : ../Scene.cpp
	gcc -c ../Scene.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src

glew.o : ../glew.c
	gcc -c ../glew.c -I ../

Main.o : ../Main.cpp
	gcc -c ../Main.cpp -I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src


#linking
all: Main.o glew.o Scene.o  InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o
	gcc -o softRend Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o -rdynamic -L ../bullet/src/BulletSoftBody -L ../bullet/src/BulletDynamics -L ../bullet/src/BulletCollision -L ../bullet/src/LinearMath -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lm -lstdc++ -Wl,-Bdynamic ../SDL2/libs/libSDL2.so -lGL 
	#gcc -o softRend Main.o glew.o Scene.o InputManager.o EventSubscriber.o Event.o EventHandler.o Component.o GameObject.o Light.o Mesh.o Obj2.o ShaderManager.o ../SDL2libs/libSDL2.so -lm -lstdc++ -lGL 
