#include <iostream>
#include "../include/App.h"

int main(int argc, char *argv[])
{
	CreationFlags creationFlags;
	int32 width = 400;
	int32 height = 300;
	creationFlags.width = width;
	creationFlags.height = height;
	creationFlags.isWindowed = true;
	creationFlags.title = "ShaderTest";
	qDebug() << "Begin App";
	App triangleApp;

	if (!triangleApp.Initialize(creationFlags))
	{
		return 1;
	}

	qDebug() << "Initialized";

	return triangleApp.Run();
	
}
