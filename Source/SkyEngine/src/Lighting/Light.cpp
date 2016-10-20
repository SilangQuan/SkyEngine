#include "Lighting/Light.h"
#include "Lighting/LightManager.h"
#include "Core/GameObject.h"


Light::Light(LightType _type)
{
	type = _type;
}

Light::~Light()
{
}

void Light::SetType(LightType _type)
{
	type = _type;
}

Light::Light()
{
	
}



void Light::AddToManager()
{
	//const Transform* transform = GetGameObject()->GetTransform();
	//m_World2Local = transform->GetWorldToLocalMatrixNoScale();
	//m_WorldPosition = transform->GetPosition();
	GetLightManager().AddLight(this);

}

void Light::RemoveFromManager()
{
	GetLightManager().RemoveLight(this);
}
