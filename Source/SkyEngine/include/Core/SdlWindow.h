#pragma once
#include "Base.h"
#include "../../3rdParty/include/SDL/SDL.h"

#include "../../3rdParty/include/SDL/SDL_opengl.h"
#include <windows.h>



class SdlWindow
{
public:
	SdlWindow();
	SdlWindow(std::string title, int width, int height);
	~SdlWindow();
	void Quit(int code);
	void ToggleFullscreen();
	void HandleKeyEvent(SDL_Keysym* keysym);
	void HandleEvents();
	void SdlDie(const char *msg);
	void CheckSDLError(int line = -1);
	std::string GetTitle();
	SDL_Window * GetSDLWindow();
	bool IsActive();

protected:
private:
	SDL_Window *mainwindow;
	SDL_GLContext maincontext;
	//Whether the window is windowed or not
	bool windowed;
	//Whether the window is fine
	bool windowOK;
	std::string title;
	int width;
	int height;
	bool isActive;

};