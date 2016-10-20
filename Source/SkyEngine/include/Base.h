#pragma once
#include <float.h>
#pragma warning( disable: 4996 ) // Disable warning about _controlfp being deprecated.
#pragma comment( lib, "..\\3rdParty\\lib\\assimp\\lib32\\assimp.lib" )
#pragma comment( lib, "..\\3rdParty\\lib\\SDL2_ttf\\x86\\SDL2_ttf.lib" )

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "Math/Mathf.h"
#include "Log/Debug.h"
#include "Log/Log.h"
#include "Core/ResourceManager.h"
#include "Components/Transform.h"
#include <map>

inline void fpuTruncate() { _controlfp(_RC_DOWN + _PC_24, _MCW_RC | _MCW_PC); }	///< Sets FPU to truncation-mode and single precision.
inline void fpuReset() { _controlfp(_CW_DEFAULT, _MCW_RC | _MCW_PC); }		///< Resets FPU to default.

typedef signed char         int8;		///< 8-bit signed integer
typedef signed short        int16;		///< 16-bit signed integer
typedef signed int          int32;		///< 32-bit signed integer
typedef unsigned char       uint8;		///< 8-bit unsigned integer
typedef unsigned short      uint16;		///< 16-bit unsigned integer
typedef unsigned int        uint32;		///< 32-bit unsigned integer

typedef float				float32;	///< 32-bit float
typedef double				float64;	///< 64-bit float


enum result
{
	ok = 0,				///< No errors were encountered, function returned successfully.
	unknown,				///< An unknown error has occured.
	invalidparameters,	///< One or more parameters were invalid.
	outofmemory,			///< Allocation of memory within the function failed.

	invalidformat,		///< A format is invalid for a specific task.
	invalidstate,			///< An invalid state has been found and the function cannot continue.
	shadercompileerror
};

class Base
{
protected:
	inline Base() : refCount(1) {}	///< The constructor initializes the reference count to 1.
	virtual inline ~Base() {}

public:
	inline void AddRef() { ++refCount; }	///< AddRef() increases the reference count.
	inline void Release() { if (--refCount == 0) delete this; }	///< Release() decreases the reference count and calls the destructor when it is 0.

private:
	Base(const Base &) {}								///< Private copy-operator to avoid object copying.
	Base &operator =(const Base &) { return *this; }	///< Private assignment-operator to avoid object copying. Returns a value to avoid compiler warnings.

private:
	uint32 refCount;
};