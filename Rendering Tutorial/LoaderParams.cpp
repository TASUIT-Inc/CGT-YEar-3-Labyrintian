#include "LoaderParams.h"

void LoaderParams::CreateCube()
{
	std::vector<float> normals;
	float x = 0.5f;
	float y = 0.5f;
	float z = 0.5f;

	std::cout << "Create variables" << std::endl;

	//gen each triangle segment seperately and Calculate Normals---------------------
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z - z);

	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Back-z side
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);

	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Back z Created " << std::endl;

	//-----------------------------------------------------------------------------

	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);

	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Front-z side
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z + z);

	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Front z Created " << std::endl;

	//------------------------------------------------------------------------------

	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Back-x side
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z + z);

	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Back x Created " << std::endl;

	//------------------------------------------------------------------------------

	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z - z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Front-x side
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);

	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Front x Created " << std::endl;

	//-------------------------------------------------------------------------------

	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z + z);

	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(1.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y - y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Back-y side
	AddVertex(m_Pos.x + x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(0.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y - y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Back y Created " << std::endl;

	//-----------------------------------------------------------------------------

	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);

	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(1.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//Front-y side
	AddVertex(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y + y, m_Pos.z - z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(0.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y + y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	std::cout << " Cube Front y Created " << std::endl;

	//-------------------------------------------------------------------------------
	SetInterlacedVertices();

	std::cout << " Interlaced vector Created " << std::endl;

	InitVertexObjects();

	std::cout << " VAO's Created " << std::endl;

}

void LoaderParams::CreatePyramid() {
	std::vector<float> normals;
	float x = 0.5f;
	float y = 0.5f;
	float z = 0.5f;


	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x, m_Pos.y + y, m_Pos.z);	//top of pyramid
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);

	AddTexCoord(0.5f, 1.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	// Front-x side

	normals = ComputeFaceNormals(m_Pos.x, m_Pos.y + y, m_Pos.z,
		m_Pos.x + x, m_Pos.y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x, m_Pos.y + y, m_Pos.z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);

	AddTexCoord(0.5f, 1.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	//Back-x side

	normals = ComputeFaceNormals(m_Pos.x, m_Pos.y + y, m_Pos.z,
		m_Pos.x - x, m_Pos.y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x, m_Pos.y + y, m_Pos.z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z + z);

	AddTexCoord(0.5f, 1.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	//Front-z side

	normals = ComputeFaceNormals(m_Pos.x, m_Pos.y + y, m_Pos.z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x, m_Pos.y + y, m_Pos.z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z - z);

	AddTexCoord(0.5f, 1.0f);
	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	// back-z side

	normals = ComputeFaceNormals(m_Pos.x, m_Pos.y + y, m_Pos.z,
		m_Pos.x + x, m_Pos.y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);
	// Bottom First triangle

	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);

	AddTexCoord(1.0f, 0.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);
	//Bottom Second Triangle

	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}


	SetInterlacedVertices();
	InitVertexObjects();
}

void LoaderParams::CreatePlane() {
	std::vector<float> normals;
	float x = 10.0f;
	float z = 10.0f;

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);

	AddTexCoord(1.0f, 1.0f);
	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);


	normals = ComputeFaceNormals(m_Pos.x + x, m_Pos.y, m_Pos.z - z,
		m_Pos.x + x, m_Pos.y, m_Pos.z + z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	//-------------------------------------------------------------------------------
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z - z);
	AddVertex(m_Pos.x - x, m_Pos.y, m_Pos.z + z);
	AddVertex(m_Pos.x + x, m_Pos.y, m_Pos.z - z);

	AddTexCoord(0.0f, 1.0f);
	AddTexCoord(0.0f, 0.0f);
	AddTexCoord(1.0f, 1.0f);


	normals = ComputeFaceNormals(m_Pos.x - x, m_Pos.y, m_Pos.z - z,
		m_Pos.x - x, m_Pos.y, m_Pos.z + z,
		m_Pos.x + x, m_Pos.y, m_Pos.z - z);


	for (int j = 0; j < 3; j++) {
		Addnormal(normals[0], normals[1], normals[2]);
	}

	SetInterlacedVertices();
	InitVertexObjects();
}

void LoaderParams::CreateSphere() {

	const float PI = acos(-1);

	// tmp vertex definition (x,y,z,s,t)
	struct Vertex
	{
		float x, y, z, s, t;
	};
	std::vector<Vertex> tmpVertices;

	float sectorStep = 2 * PI / m_Segments.x;
	float stackStep = PI / m_Segments.y;
	float sectorAngle, stackAngle;

	// compute all vertices first, each vertex contains (x,y,z,s,t) except normal
	for (int i = 0; i <= m_Segments.y; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		float xy = m_Extents.x * cosf(stackAngle);       // r * cos(u)
		float z = m_Extents.x * sinf(stackAngle);        // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= m_Segments.x; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			Vertex vertex;
			vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
			vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
			vertex.z = z;                           // z = r * sin(u)
			vertex.s = (float)j / m_Segments.x;        // s
			vertex.t = (float)i / m_Segments.y;         // t
			tmpVertices.push_back(vertex);
		}
	}


	Vertex v1, v2, v3, v4;                          // 4 vertex positions and tex coords
	std::vector<float> n;                           // 1 face normal

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
				// put Triangle vertices: v1-v2-v3
				AddVertex(v1.x, v1.y, v1.z);
				AddVertex(v2.x, v2.y, v2.z);
				AddVertex(v3.x, v3.y, v3.z);

				// put tex coords of Triangle
				AddTexCoord(v1.s, v1.t);
				AddTexCoord(v2.s, v2.t);
				AddTexCoord(v3.s, v3.t);

				n = ComputeFaceNormals(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
				for (k = 0; k < 4; ++k)  // same normals for 3 vertices
				{
					Addnormal(n[0], n[1], n[2]);
				}
				// put Triangle vertices: v4-v2-v3
				AddVertex(v4.x, v4.y, v4.z);
				AddVertex(v3.x, v3.y, v3.z);
				AddVertex(v2.x, v2.y, v2.z);

				// put tex coords of Triangle 2
				AddTexCoord(v4.s, v4.t);
				AddTexCoord(v3.s, v3.t);
				AddTexCoord(v2.s, v2.t);

				// put normal
				n = ComputeFaceNormals(v4.x, v4.y, v4.z, v3.x, v3.y, v3.z, v2.x, v2.y, v2.z);
				for (k = 0; k < 4; ++k)  // same normals for 3 vertices
				{
					Addnormal(n[0], n[1], n[2]);
				}


				index += 4;     // for next
			}
		}
	}


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
	SetInterlacedVertices();
	InitVertexObjects();
}

std::vector<float> LoaderParams::ComputeFaceNormals(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {

	const float EPSILON = 0.000001f;

	std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
	float nx, ny, nz;

	// find 2 edge vectors: v1-v2, v1-v3
	float edgevertex_X1 = x2 - x1;
	float edgevertex_Y1 = y2 - y1;
	float edgevertex_Z1 = z2 - z1;
	float edgevertex_X2 = x3 - x1;
	float edgevertex_Y2 = y3 - y1;
	float edgevertex_Z2 = z3 - z1;

	// cross product: e1 x e2
	nx = edgevertex_Y1 * edgevertex_Z2 - edgevertex_Z1 * edgevertex_Y2;
	ny = edgevertex_Z1 * edgevertex_X2 - edgevertex_X1 * edgevertex_Z2;
	nz = edgevertex_X1 * edgevertex_Y2 - edgevertex_Y1 * edgevertex_X2;

	// normalize only if the length is > 0
	float length = sqrtf(nx * nx + ny * ny + nz * nz);
	if (length > EPSILON)
	{
		// normalize
		float lengthInv = 1.0f / length;
		normal[0] = nx * lengthInv;
		normal[1] = ny * lengthInv;
		normal[2] = nz * lengthInv;
	}

	return normal;

}

void LoaderParams::SetInterlacedVertices() {
	int i, j;

	for (i = 0, j = 0; i < m_Vertices.size(); i += 3, j += 2) {
		//create an ordered vector going vertices -> normals -> texcoords
		m_InterLeavedVertices.push_back(m_Vertices[i]);
		m_InterLeavedVertices.push_back(m_Vertices[i + 1]);
		m_InterLeavedVertices.push_back(m_Vertices[i + 2]);

		m_InterLeavedVertices.push_back(m_Texcoords[j]);
		m_InterLeavedVertices.push_back(m_Texcoords[j + 1]);

		m_InterLeavedVertices.push_back(m_Normals[i]);
		m_InterLeavedVertices.push_back(m_Normals[i + 1]);
		m_InterLeavedVertices.push_back(m_Normals[i + 2]);


	}
}

void LoaderParams::AddVertex(float x, float y, float z) {
	m_Vertices.push_back(x);
	m_Vertices.push_back(y);
	m_Vertices.push_back(z);
}

void LoaderParams::Addnormal(float x, float y, float z) {
	m_Normals.push_back(x);
	m_Normals.push_back(y);
	m_Normals.push_back(z);
}

void LoaderParams::AddTexCoord(float x, float y) {
	m_Texcoords.push_back(x);
	m_Texcoords.push_back(y);
}

void LoaderParams::Draw(Shader* shader, unsigned int texture) {
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
}

void LoaderParams::InitVertexObjects() {
	//float* vertices = &m_InterLeavedVertices[0];
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_InterLeavedVertices.size() * sizeof(float), m_InterLeavedVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_InterLeavedStride, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_InterLeavedStride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}
