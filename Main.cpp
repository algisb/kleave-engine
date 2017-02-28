#include "SDL.h"
//#include <SDL_image.h>
//#include <SDL_ttf.h>

#include "glew.h"
#include "Scene.h"
#include "InputManager.h"
#include "EventHandler.h"

#include "iostream"
#include "string"
#include "thread"

bool InitGL()
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	
	return true;
}

int main(int argc, char *argv[])
{
	if( SDL_Init( /*SDL_INIT_VIDEO*/ SDL_INIT_EVERYTHING ) < 0 )
	{
		std::cout<<"Whoops! Something went very wrong, cannot initialise SDL :("<<std::endl;
		return -1;
	}

//	if (TTF_Init() == -1) 
//	{
//		printf("TTF_Init: %s\n", TTF_GetError());
//		exit(2);
//	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	int winPosX = 0;
	int winPosY = 0;
	int winWidth = 800;
	int winHeight = 600;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		winWidth, winHeight,
		SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_SHOWN);//SDL_WINDOW_RESIZABLE

	SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, 0 );
	SDL_GLContext glcontext = SDL_GL_CreateContext( window );
	if( !InitGL() )
	{
		return -1;
	}
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	bool exitProgram = false;
	unsigned int lastTime = SDL_GetTicks();
	EventHandler eventHandler;
	InputManager inputManager(&exitProgram, &eventHandler);
	Scene myScene(window, winWidth, winHeight, &inputManager, &eventHandler);
	
	while( !exitProgram )
	{
		//calculate delta time
		unsigned int current = SDL_GetTicks();
		float deltaTs = (float) (current - lastTime) / 1000.0f;
		lastTime = current;
		//=========THE GOODIES=============
		//inputManager.update();//TODO move it to another thread so input is read in even if the game freezes
		eventHandler.update();
		myScene.Update( deltaTs);
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		myScene.Draw();
		SDL_GL_SwapWindow( window );
		//=================================
		// Limiter in case we're running really quick
		if( deltaTs < (1.0f/50.0f) )	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTs)*1000.0f) );
		}	
	}

	SDL_GL_DeleteContext( glcontext );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
