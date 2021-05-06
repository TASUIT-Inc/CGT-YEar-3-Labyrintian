#include "BoundingBox.h"

void BoundingBox::Update(Transform& transform) {
	m_Pos = transform.GetPos();		//update BB's Center pos
}


