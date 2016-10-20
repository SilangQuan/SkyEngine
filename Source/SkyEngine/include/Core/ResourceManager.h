#pragma once
typedef int ResHandle;

#include "Base.h"
#include <map>

// =================================================================================================
// Resource
// =================================================================================================

struct ResourceTypes
{
	enum List
	{
		Undefined = 0,
		SceneGraph,
		Geometry,
		Animation,
		Material,
		Code,
		Shader,
		Texture,
		ParticleEffect,
		Pipeline
	};
};


class Resource
{
public:
	Resource(const std::string &name);
	virtual ~Resource();

	virtual void initDefault();
	virtual void release();
	virtual bool load(const char *data, int size);
	void unload();

	const std::string &getName() { return _name; }
	ResHandle getHandle() { return _handle; }
	bool isLoaded() { return _loaded; }

protected:
	std::string          _name;
	ResHandle            _handle;

	bool                 _loaded;

	friend class ResourceManager;
};


// =================================================================================================
// Resource Manager
// =================================================================================================

// =================================================================================================


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance()
	{
		if (instance == NULL)
			instance = new ResourceManager();
		return instance;
	}

	Resource *GetResource(const std::string &name);

	template <typename T>
	T *LoadResource(const std::string &filePath)
	{
		T* resource = new T(filePath);
		resources[filePath] = resource;
		return resource;
	}

	template <typename T>
	T *TryGetResource(const std::string &filePath)
	{
		auto iter = resources.find(filePath);
		if (iter == resources.end())
		{
			return LoadResource<T>(filePath);
		}
		else
		{
			return dynamic_cast<T*>(iter->second);
		}
	}

	void RemoveResource(Resource &resource);
	void Clear();

	std::map <const std::string, Resource*> &GetResources() { return resources; }

private:
	std::map <const std::string, Resource*>   resources;
	static ResourceManager * instance;
};

