#include "LoaderParams.h"

void LoaderParams::CreateCube()
{
	DrawMode = GL_TRIANGLES;
	float px = 1.0f; float nx = -1.0f;
	float py = 1.0f; float ny = -1.0f;
	float pz = 1.0f; float nz = -1.0f;

	VertexData p1, p2, p3, p4, p5, p6, p7, p8;

	//face layout

	/*Front Face:	p1 --- p2		Left Face:	p6 --- p1		Back Face:	p5 --- p6		Right Face:	p2 --- p5	Top Face:	p6 --- p5	Bottom Face:	p3 --- p4
					 |     |					 |		|					 |     |					 |     |				 |     |					 |     |
					 |     |					 |		|					 |     |					 |     |				 |     |					 |     |
					p3 --- p4					p8 --- p3 					p7 --- p8					p4 --- p7				p1 --- p2					p8 --- p7
					
	Connections:
		p1 -> p2, p8, p5
		p2 -> p3, p5, p1
		p3 -> p2, p8, p4
		p4 -> p3, p5, p8
		p5 -> p6, p4, p1
		p6 -> p1, p7, p5
		p7 -> p6, p4, p8
		p8 -> p1, p7, p4*/

	p1.m_Pos = glm::vec3(nx, py, pz);
	p2.m_Pos = glm::vec3(px, py, pz);
	p3.m_Pos = glm::vec3(nx, ny, pz);
	p4.m_Pos = glm::vec3(px, ny, pz);

	p5.m_Pos = glm::vec3(px, py, nz);
	p6.m_Pos = glm::vec3(nx, py, nz);
	p7.m_Pos = glm::vec3(px, ny, nz);
	p8.m_Pos = glm::vec3(nx, ny, nz);

	p1.m_Norm = p1.m_Pos;
	p2.m_Norm = p2.m_Pos;
	p3.m_Norm = p3.m_Pos;
	p4.m_Norm = p4.m_Pos;

	p5.m_Norm = p5.m_Pos;
	p6.m_Norm = p6.m_Pos;
	p7.m_Norm = p7.m_Pos;
	p8.m_Norm = p8.m_Pos;

	p1.m_TexCoord = glm::vec2(0.0f, 1.0f);
	p2.m_TexCoord = glm::vec2(1.0f, 1.0f);
	p3.m_TexCoord = glm::vec2(0.0f, 0.0f);
	p4.m_TexCoord = glm::vec2(1.0f, 0.0f);

	p5.m_TexCoord = glm::vec2(0.0f, 1.0f);
	p6.m_TexCoord = glm::vec2(1.0f, 1.0f);
	p7.m_TexCoord = glm::vec2(0.0f, 0.0f);
	p8.m_TexCoord = glm::vec2(1.0f, 0.0f);

	PushVertexOrder(p1, p2, p3);	//Front Face
	PushVertexOrder(p4, p3, p2);

	PushVertexOrder(p6, p1, p8);	//Left Face
	PushVertexOrder(p3, p8, p1);

	PushVertexOrder(p5, p6, p7);	//Back Face
	PushVertexOrder(p8, p7, p6);

	PushVertexOrder(p2, p5, p4);	//Right Face
	PushVertexOrder(p7, p4, p5);

	PushVertexOrder(p6, p5, p1);	//Top Face
	PushVertexOrder(p2, p1, p5);

	PushVertexOrder(p3, p4, p8);	//Bottom Face
	PushVertexOrder(p7, p8, p4);

	InitBufferData();
}

void LoaderParams::CreatePyramid() {

	DrawMode = GL_TRIANGLES;
	float px = 1.0f; float nx = -1.0f;
	float py = 1.0f; float ny = -1.0f;
	float pz = 1.0f; float nz = -1.0f;
	float ze = 0.0f;

	VertexData p1, p2, p3, p4, p5;

	//face layout

	/*Front Face:	   p1 		Left Face:	 	   p1 	  		Back Face:		   p1 			Right Face:		   p1 		Bottom Face:	  p3 --- p2	
					 /    \ 					 /    \ 	 					 /    \ 						 /    \ 					   |	 |   
					/      \					/      \						/      \						/      \					   |     |
				   p3 - - - p2				   p4 - - - p3					  p5 - - - p4					  p2 - - - p5					  p4 --- p5

	Connections:
		p1 -> p2, p3, p4
		p2 -> p3, p1, p4
		p3 -> p1, p2, p4
		p4 -> p1, p5, p3
		p5 -> p1, p2, p4*/

	p1.m_Pos = glm::vec3(ze, py, ze);

	p2.m_Pos = glm::vec3(px, ze, pz);
	p3.m_Pos = glm::vec3(nx, ze, pz);

	p4.m_Pos = glm::vec3(nx, ze, nz);
	p5.m_Pos = glm::vec3(px, ze, nz);

	p1.m_Norm = p1.m_Pos;

	p2.m_Norm = p2.m_Pos;
	p3.m_Norm = p3.m_Pos;

	p4.m_Norm = p4.m_Pos;
	p5.m_Norm = p5.m_Pos;

	p1.m_TexCoord = glm::vec2(0.5f, 0.5f);

	p2.m_TexCoord = glm::vec2(1.0f, 1.0f);
	p3.m_TexCoord = glm::vec2(0.0f, 1.0f);

	p4.m_TexCoord = glm::vec2(0.0f, 0.0f);
	p5.m_TexCoord = glm::vec2(1.0f, 0.0f);

	PushVertexOrder(p1, p2, p3);	//Front Face

	PushVertexOrder(p1, p3, p4);	//Left Face

	PushVertexOrder(p1, p4, p5);	//Back Face

	PushVertexOrder(p1, p5, p2);	//Right Face

	PushVertexOrder(p3, p2, p4);	//Top Face
	PushVertexOrder(p5, p4, p2);

	InitBufferData();
}

void LoaderParams::CreatePlane() {

	DrawMode = GL_TRIANGLES;
	float px = 1.0f; float nx = -1.0f;
	float py = 1.0f; float ny = -1.0f;
	float pz = 1.0f; float nz = -1.0f;
	float ze = 0.0f;

	VertexData p1, p2, p3, p4;

	p1.m_Pos = glm::vec3(nx, py, ze);
	p2.m_Pos = glm::vec3(px, py, ze);

	p3.m_Pos = glm::vec3(nx, ny, ze);
	p4.m_Pos = glm::vec3(px, ny, ze);

	p1.m_Norm = p1.m_Pos;
	p2.m_Norm = p2.m_Pos;

	p3.m_Norm = p3.m_Pos;
	p4.m_Norm = p4.m_Pos;

	p1.m_TexCoord = glm::vec2(0.0f, 1.0f);
	p2.m_TexCoord = glm::vec2(1.0f, 1.0f);

	p3.m_TexCoord = glm::vec2(0.0f, 0.0f);
	p4.m_TexCoord = glm::vec2(1.0f, 0.0f);
	
	PushVertexOrder(p1, p2, p3);	//Front Face
	PushVertexOrder(p4, p3, p2);	

	InitBufferData();
}

void LoaderParams::CreateSphere(glm::vec2 Segments) {

	const float PI = acos(-1);



	// Note of Interest//
	/*Use this if you want a spiral Sphere
	int i, j, k, vi1, vi2;
	int index = 0;                                  // index for vertex
	for (i = 0; i < m_Segments.y; ++i)
	{
		vi1 = i * (m_Segments.x + 1);                // index of tmpVertices
		vi2 = (i + 1) * (m_Segments.x + 1);

		for (j = 0; j < m_Segments.x; ++j, ++vi1, ++vi2)
		{
			// get 4 vertices per sector
			//  v1--v3
			//  |    |
			//  v2--v4
			v1 = tmpVertices[vi1];
			v2 = tmpVertices[vi2];
			v3 = tmpVertices[vi1 + 1];
			v4 = tmpVertices[vi2 + 1];

			// if 1st stack and last stack, store only 1 triangle per sector
			// otherwise, store 2 triangles (quad) per sector
			if (i == 0) // a triangle for first stack ==========================
			{
				// put a triangle
				AddVertex(v1.x, v1.y, v1.z);
				AddVertex(v2.x, v2.y, v2.z);
				AddVertex(v4.x, v4.y, v4.z);

				//put tex coords of triangle
				AddTexCoord(v1.s, v1.t);
				AddTexCoord(v2.s, v2.t);
				AddTexCoord(v4.s, v4.t);

				// put normal
				n = ComputeFaceNormals(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
				for (k = 0; k < 3; ++k)  // same normals for 3 vertices
				{
					Addnormal(n[0], n[1], n[2]);
				}


				index += 3;     // for next
			}
			else if (i == (m_Segments.y - 1)) // a triangle for last stack =========
			{
				// put a triangle
				AddVertex(v1.x, v1.y, v1.z);
				AddVertex(v2.x, v2.y, v2.z);
				AddVertex(v3.x, v3.y, v3.z);

				// put tex coords of triangle
				AddTexCoord(v1.s, v1.t);
				AddTexCoord(v2.s, v2.t);
				AddTexCoord(v3.s, v3.t);

				// put normal
				n = ComputeFaceNormals(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
				for (k = 0; k < 3; ++k)  // same normals for 3 vertices
				{
					Addnormal(n[0], n[1], n[2]);
				}


				index += 3;     // for next
			}
			else // 2 triangles for others ====================================
			{
				// put Triangle vertices: v1-v2-v3-v4
				AddVertex(v1.x, v1.y, v1.z);
				AddVertex(v2.x, v2.y, v2.z);
				AddVertex(v3.x, v3.y, v3.z);
				AddVertex(v4.x, v4.y, v4.z);

				// put tex coords of Triangle
				AddTexCoord(v1.s, v1.t);
				AddTexCoord(v2.s, v2.t);
				AddTexCoord(v3.s, v3.t);
				AddTexCoord(v4.s, v4.t);

				n = ComputeFaceNormals(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
				for (k = 0; k < 4; ++k)  // same normals for 3 vertices
				{
					Addnormal(n[0], n[1], n[2]);
				}

				index += 4;     // for next
			}
		}
	}
	*/

	// generate interleaved vertex array as well
	isSphere = true;
}

void LoaderParams::PushVertexOrder(VertexData V1, VertexData V2, VertexData V3) {
	m_InterLeavedVertices.push_back(V1);
	m_InterLeavedVertices.push_back(V2);
	m_InterLeavedVertices.push_back(V3);
}

void LoaderParams::Draw(unsigned int texture =0) {
	glBindVertexArray(m_VAO);
	glActiveTexture(GL_TEXTURE0);
	if (texture != 0) {
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glDrawArrays(GL_TRIANGLES, 0, m_InterLeavedVertices.size());
}

void LoaderParams::InitBufferData() {
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_InterLeavedVertices.size() * sizeof(VertexData), m_InterLeavedVertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, m_Norm));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, m_TexCoord));
	glEnableVertexAttribArray(2);
}
