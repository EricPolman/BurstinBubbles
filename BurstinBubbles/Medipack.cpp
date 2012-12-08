#include "StdAfx.h"
#include "Medipack.h"


Medipack::Medipack(void) : GameObject("medipack")
{
}


Medipack::~Medipack(void)
{
}


void Medipack::Hit(GameObject* other)
{
	if(other->GetType() != "Bullet" && other->GetType() != "Enemy")
	{
		m_bIsDead = true;
	}
}

std::string Medipack::GetType()
{
	return "Medipack";
}
