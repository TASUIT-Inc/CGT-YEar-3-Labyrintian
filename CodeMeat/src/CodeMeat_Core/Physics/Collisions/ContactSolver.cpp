#include "ContactSolver.h"

void ContactSolver::ResolveContacts(Contacts* cArray, int NumContacts, float dt) 
{
	m_Iteration = 0;
	int maxindex = NumContacts;

	while (m_Iteration < m_MaxIterations) 
	{
		float max = 0;
		maxindex = NumContacts;
		for (int i = 0; i < NumContacts; i++) 
		{
			float sepVel = cArray[i].ComputeSeperatingVel();
			if (sepVel < max) 
			{
				max = sepVel;
				maxindex = i;
			}
		}

		if (maxindex < NumContacts) 
		{
			cArray[maxindex].ResolveContacts(dt);
		}
		m_Iteration++;
	}
}