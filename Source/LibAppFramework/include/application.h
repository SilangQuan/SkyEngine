#pragma once
#include "base.h"
//#include "Core/Color.h"

class Renderer;
class Scene;
class ResourceManager;
class SdlWindow;
class Input;
class Time;

struct CreationFlags
{
	string	title;
	uint16	width, height;
	bool	isWindowed;
};

class Application
{
public:
	Application();
	virtual ~Application();

	virtual bool Initialize(const CreationFlags &creationFlags);
	virtual int	Run();

	virtual bool CreateWorld() = 0;
	virtual void DestroyWorld() = 0;

	virtual void FrameMove() = 0;		// update animated objects, etc.
	virtual void RenderWorld() = 0;		// draw objects

protected:
	bool CreateSubSystems(const CreationFlags &creationFlags);

public:
	float32 GetFPS();

	inline float32 GetInvFPS() { return fInvFPS; }
	inline float32 GetElapsedTime() { return fElapsedTime; }

	//windowhandle hGetWindowHandle() { return hWindowHandle; }
	bool GetWindowed() { return bWindowed; }
	bool GetActive() { return bActive; }
	//string GetWindowTitle() { return window->GetTitle(); }
	SdlWindow* GetWindow();
	uint16 GetWindowWidth() { return iWindowWidth; }
	uint16 GetWindowHeight() { return iWindowHeight; }

	uint32 GetFrameIdent() { return frameIdent; }

	inline void SetAppData(void *i_pData, uint32 i_iLength)
	{
		SAFE_DELETE_ARRAY(pAppData);
		pAppData = new byte[i_iLength];
		memcpy(pAppData, i_pData, i_iLength);
	}
	inline void *GetAppData() { return pAppData; }

	// Subsystems -------------------------------------------------------------
	//inline InputManager			*GetInput() { return pInput; }
	//inline class CFileIO		*pGetFileIO() { return pFileIO; }
	inline Renderer		*GetGraphics() { return pRenderer; }
	inline ResourceManager	*GetResManager() { return pResManager; }
	inline Scene			*GetScene() { return pScene; }

protected:
	float32		fFPS, fInvFPS, fElapsedTime;

	//windowhandle	hWindowHandle;
	bool			bWindowed, bActive;
	uint16			iWindowWidth, iWindowHeight;

	uint32	frameIdent;

	byte	*pAppData;

	 Input	*pInput;
	//class CFileIO		*pFileIO;
	 Renderer		*pRenderer;
	 ResourceManager	*pResManager;
	 Scene		*pScene;
	 SdlWindow* window;
	 Time* time;
private:
	LARGE_INTEGER	ticksPerSecond, startTime, lastTime;

private:
	void BeginFrame();
	bool CheckMessages();
	void EndFrame();
};
