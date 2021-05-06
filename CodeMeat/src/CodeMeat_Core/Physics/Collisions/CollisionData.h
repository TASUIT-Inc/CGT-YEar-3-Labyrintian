#pragma once
#include "Contacts.h"

#define NULLDATA CollisionData()

struct CollisionData {	//Collection of collision specific data

	Contacts* m_Contacts = nullptr;	//total number of contacts in current collision
	int m_ContactAmount, m_MaxContatcs;

	virtual ~CollisionData() 
	{
		if (m_Contacts != nullptr) 
		{
			delete[] m_Contacts;
		}
	}
};
