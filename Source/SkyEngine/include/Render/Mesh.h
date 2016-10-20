#pragma once
#include "Base.h"
#include "Texture.h"

class TextureVariable;

class Mesh
{
public:
	enum VertexAttribute
	{
		POSITION_ATTRIBUTE,
		UV_COORD_ATTRIBUTE,
		NORMAL_ATTRIBUTE,

		NUM_VERTEX_ATTRIBUTES
	};

	vector<Vector3> positions;
	vector<Vector3> normals;
	vector<Color> colors;
	vector<Vector2> uv;
	vector<uint32> triangles;
	vector<TextureVariable*> textures;

private:

	uint32 vaoID;									//Vertex Array Object
	uint32 vboIDs[Mesh::NUM_VERTEX_ATTRIBUTES];		//Vertex Buffer Object (One per vertex attribute)
	uint32 iboID;

public:
	Mesh(vector<Vector3> positions, vector<Vector3> normals, vector<Vector2> uv, vector<uint32> triangles, vector<TextureVariable*> textures);
	Mesh();
	virtual ~Mesh() {}

	inline vector<Vector3>& GetPositions() { return positions; }
	inline vector<Vector3>& GetNormals() { return normals; }
	inline vector<Vector2>& GetUvCoords() { return uv; }
	inline vector<uint32>& GetIndices() { return triangles; }

	inline uint32 GetVAO() const { return vaoID; }
	inline uint32 GetVBO(uint32 index) const { return vboIDs[index]; }
	inline const uint32* GetVBOs() const { return vboIDs; }
	inline uint32 GetIBO() const { return iboID; }

	//void BindTextures();

	//void AttachTexture(Texture* tex);

	void CreateBufferData();


	inline void FreeData()
	{
		positions.clear();
		normals.clear();
		uv.clear();
		triangles.clear();
		normals.clear();
	}
};
