#include "Core/SdlWindow.h"
#include "Log/Log.h"
#include <stdio.h>

SdlWindow::SdlWindow()
{
	isActive = true;
}

SdlWindow::SdlWindow(std::string _title, int _width, int _height)
{

	title = _title;
	height = _height;
	width = _width;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
		SdlDie("Unable to initialize SDL"); /* Or die on error */

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	/* Request opengl 3.2 context.
	* SDL doesn't have the ability to choose which profile at this time of writing,
	* but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);


	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */
	mainwindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	
	if (!mainwindow) /* Die if creation failed */
	{
		SdlDie("Unable to create window");
	}
	else windowed = true;

	CheckSDLError(__LINE__);

	isActive = true;

}

SdlWindow::~SdlWindow()
{

}

void SdlWindow::Quit(int code)
{
	SDL_Quit();
	exit(code);
}

void SdlWindow::SdlDie(const char *msg)
{
	printf("%s: %s\n", msg, SDL_GetError());

	SDL_Quit();
	exit(1);
}

std::string SdlWindow::GetTitle()
{
	return title;
}

SDL_Window*  SdlWindow::GetSDLWindow()
{
	return mainwindow;
}

void SdlWindow::ToggleFullscreen()
{

}

void SdlWindow::HandleKeyEvent(SDL_Keysym* keysym)
{
	switch (keysym->sym)
	{
	case SDLK_ESCAPE:
		//this->quit(0);
		break;
	case SDLK_SPACE:
		std::cout << "Space" << std::endl;
		break;
	case SDLK_F1:
		this->ToggleFullscreen();
		break;
	case SDLK_r:
		std::cout << "Fuck" << std::endl;
		break;

	default:
		break;
	}
}

bool SdlWindow::IsActive()
{
	return isActive;
}


void SdlWindow::HandleEvents()
{
	// Our SDL event placeholder.
	SDL_Event event;
	//Grab all the events off the queue.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			// Handle key Event
			HandleKeyEvent(&event.key.keysym);
			break;
		case SDL_QUIT:
			isActive = false;
			// Handle quit requests (like Ctrl-c).
			//quit(0);
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				if (mainwindow)
				{
					int tmpX, tmpY;
					SDL_GetWindowSize(mainwindow, &tmpX, &tmpY);
					//gl->resizeGL(tmpX, tmpY);

				}
			}
			SDL_GL_SwapWindow(mainwindow);
			break;
		}
	}
}
void SdlWindow::CheckSDLError(int line)
{

}

