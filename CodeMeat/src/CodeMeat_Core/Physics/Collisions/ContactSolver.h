#pragma once
#include"Contacts.h"



class ContactSolver 
{
public:
	ContactSolver() {}

	void SetMaxIterations(int newMax) { m_MaxIterations = newMax; }
	void ResolveContacts(Contacts* CArray, int NumContacts, float dt);
private:

	int m_MaxIterations, m_Iteration;
};