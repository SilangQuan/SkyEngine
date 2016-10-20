#pragma once
#include "../../LibAppFramework/include/application.h"


class App : public Application
{
public:
	//bool Initialize();
	bool CreateWorld();
	void DestroyWorld();

	void FrameMove();
	void RenderWorld();

private:
	GLuint shaderProgram;
	GLuint shaderProgram2;
	GLuint VBOs[2], VAOs[2], EBO;
};