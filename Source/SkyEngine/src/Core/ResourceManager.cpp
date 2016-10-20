
#include "Core/ResourceManager.h"
#include "../../SkyEngine/include/SkyEngine.h"


using namespace std;

// **********************************************************************************
// Class Resource
// **********************************************************************************

Resource::Resource(const string &name)
{
	_name = name;
	_handle = 0;
	_loaded = false;
}

Resource::~Resource()
{
	// Remove all references
	// Nothing to do here
}



void Resource::initDefault()
{
}


void Resource::release()
{
}


bool Resource::load(const char *data, int size)
{
	// Resources can only be loaded once
	if (_loaded) return false;

	// A NULL pointer can be used if the file could not be loaded
	if (data == 0x0 || size <= 0)
	{
		qDebug() << "Resource '%s' of type %i: No data loaded (file not found?)";
		return false;
	}

	_loaded = true;

	return true;
}


void Resource::unload()
{
	release();
	initDefault();
	_loaded = false;
}

// **********************************************************************************
// Class ResourceManager
// **********************************************************************************
ResourceManager* ResourceManager::instance = NULL;


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
}

Resource* ResourceManager::GetResource(const std::string &name)
{
	auto iter = resources.find(name);
	if (iter == resources.end())
	{
		return NULL;
	}else
	{
		return iter->second;
	}
}

void ResourceManager::RemoveResource(Resource &resource)
{
	/*std::map <const std::string &, Resource*>::iterator iter = resources.find(name);
	if (iter != resources.end())
	{
		iter->second;
	}*/
}

void ResourceManager::Clear()
{

}
