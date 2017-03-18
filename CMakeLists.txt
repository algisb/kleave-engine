cmake_minimum_required(VERSION 2.6)
project(kek_engine)

SET(CMAKE_CXX_FLAGS "-I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src -rdynamic -L ../bullet/src/BulletSoftBody -L ../bullet/src/BulletDynamics -L ../bullet/src/BulletCollision -L ../bullet/src/LinearMath -L ../SDL2_image/.libs -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++")
#include_directories( /usr/include )
#include_directories( /usr/lib )
#include_directories( /usr/include )
#link_directories( ../bullet/src/BulletDynamics )
add_compile_options(-I ../ -I ../SDL2/include -I ../glm/glm -I ../glm/glm/gtc -I ../glm/glm/gtx -I ../SDL2_image -I ../bullet/src -rdynamic -L ../bullet/src/BulletSoftBody -L ../bullet/src/BulletDynamics -L ../bullet/src/BulletCollision -L ../bullet/src/LinearMath -L ../SDL2_image/.libs -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++)



add_executable(kek_engine Main.cpp)

install(TARGETS kek_engine RUNTIME DESTINATION bin)
