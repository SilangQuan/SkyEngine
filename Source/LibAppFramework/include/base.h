#pragma once

#ifdef _DEBUG
#pragma comment( lib, "..\\..\\Lib\\Win32\\Debug\\SkyEngine.lib" )
#else
#pragma comment( lib, "..\\..\\Lib\\Win32\\Release\\SkyEngine.lib" )
#endif

#pragma comment( lib, "..\\3rdParty\\lib\\GLEW\\Win32\\glew32.lib" )
#pragma comment( lib, "..\\3rdParty\\lib\\SDL\\x86\\SDL2.lib" )
#pragma comment( lib, "..\\3rdParty\\lib\\SDL\\x86\\SDL2main.lib" )
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#if _MSC_VER > 1000
#pragma warning( disable : 4786 ) // shut up compiler warning
#endif

// Basic macro definitions ----------------------------------------------------

#define SAFE_DELETE( p ) { if( p ) { delete p; p = 0; }  }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] p; p = 0; }  }
#define SAFE_RELEASE( p ) { if( p ) { ( p )->Release(); p = 0; }  }

// Basic variable type-definitions --------------------------------------------

#include <string>

#include "../../SkyEngine/include/SkyEngine.h"
#include "Input.h"
#include "InputDefinition.h"
#include "Time.h"
#include "Renderer.h"
using namespace std;

#ifdef __amigaos4__	
#include <exec/types.h>
#else // avoid conflicts with <exec/types.h>

typedef signed char         int8;		///< 8-bit signed integer
typedef signed short        int16;		///< 16-bit signed integer
typedef signed int          int32;		///< 32-bit signed integer
typedef unsigned char       uint8;		///< 8-bit unsigned integer
typedef unsigned short      uint16;		///< 16-bit unsigned integer
typedef unsigned int        uint32;		///< 32-bit unsigned integer

typedef float				float32;	///< 32-bit float
typedef double				float64;	///< 64-bit float

#endif

typedef unsigned char		byte;		///< byte


