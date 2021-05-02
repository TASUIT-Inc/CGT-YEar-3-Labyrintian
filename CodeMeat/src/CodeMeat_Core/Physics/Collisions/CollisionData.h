#pragma once
#include "Contacts.h"

#define NULLDATA CollisionData()

struct CollisionData {

	Contacts* m_Contacts = nullptr;
	int m_ContactAmount, m_MaxContatcs;

	virtual ~CollisionData() 
	{
		if (m_Contacts != nullptr) 
		{
			delete[] m_Contacts;
		}
	}
};
