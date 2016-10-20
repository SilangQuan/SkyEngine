#include "Render/Mesh.h"
#include "Render/ShaderProgram.h"

Mesh::Mesh() : positions(), normals(), uv(), triangles(), vaoID(-1), iboID(-1)
{
	for (uint32 i = 0; i < (uint32)Mesh::NUM_VERTEX_ATTRIBUTES; i++)
	{
		vboIDs[i] = -1;
	}
}
Mesh::Mesh(vector<Vector3> _positions, vector<Vector3> _normals, vector<Vector2> _uv, vector<uint32> _triangles, vector<TextureVariable*> _textures): positions(_positions), normals(_normals), uv(_uv), triangles(_triangles),textures(_textures), vaoID(-1), iboID(-1)
{
}

/*
void Mesh::BindTextures()
{
	for (auto& tex : textures) {
		tex->Bind();
	}
}

void Mesh::AttachTexture(Texture* tex)
{
	textures.push_back(tex);
}
*/

void Mesh::CreateBufferData()
{
	//Generate gl buffers
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(Mesh::NUM_VERTEX_ATTRIBUTES, &vboIDs[0]);
	glGenBuffers(1, &iboID);

	//Bind Vertex Array
	glBindVertexArray(vaoID);

	//Copy position data into POSITION buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[Mesh::POSITION_ATTRIBUTE]);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->GetPositions().size() * sizeof(this->GetPositions()[0]),
		&(this->GetPositions()[0]),
		GL_STATIC_DRAW);


	glVertexAttribPointer(
		Mesh::POSITION_ATTRIBUTE,
		3, GL_FLOAT,
		GL_FALSE,
		0, 0);
	//Enable position attribute
	glEnableVertexAttribArray(Mesh::POSITION_ATTRIBUTE);

	//Copy uvCoord data into UV_COORD buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[Mesh::UV_COORD_ATTRIBUTE]);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->GetUvCoords().size() * sizeof(this->GetUvCoords()[0]),
		&(this->GetUvCoords()[0]),
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		Mesh::UV_COORD_ATTRIBUTE,
		2, GL_FLOAT,
		GL_FALSE,
		0, 0);
	//Enable uvCoord attribute
	glEnableVertexAttribArray(Mesh::UV_COORD_ATTRIBUTE);

	//Copy normal data into NORMAL buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboIDs[Mesh::NORMAL_ATTRIBUTE]);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->GetNormals().size() * sizeof(this->GetNormals()[0]),
		&(this->GetNormals()[0]),
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		Mesh::NORMAL_ATTRIBUTE,
		3, GL_FLOAT,
		GL_FALSE,
		0, 0);
	//Enable normal attribute
	glEnableVertexAttribArray(Mesh::NORMAL_ATTRIBUTE);

	if(this->GetIndices().size() > 0)
	{
		//Copy index data to Element Array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			this->GetIndices().size() * sizeof(this->GetIndices()[0]),
			&(this->GetIndices()[0]),
			GL_STATIC_DRAW);
	}
	

	//Unbind Vertex Array
	glBindVertexArray(0);
}


