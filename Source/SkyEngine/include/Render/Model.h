#pragma once
#include "Base.h"
#include "Core/ObjLoader.h"
#include "Core/ObjLoader.h"
#include "../../3rdParty/include/assimp/Importer.hpp"
#include "../../3rdParty/include/assimp/scene.h"
#include "../../3rdParty/include/assimp/postprocess.h"

class ShaderProgram;
class Mesh;
class TextureVariable;

class Model
{
public:
	Model(GLchar* path, bool usingAssimp);
	~Model();
	void Draw(ShaderProgram* shader);
	void CreateBufferData();
	vector<Mesh>* GetMeshes();

private:
	vector<Mesh> meshes;
	string directory;

	void LoadModel(string path);
	Mesh  ProcessMesh(tinyobj::ObjMesh* mesh, vector<tinyobj::ObjMaterial>& materials);

	void LoadModelByAssimp(string path);

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNodeByAssimp(aiNode* node, const aiScene* scene);

	Mesh ProcessMeshByAssimp(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<TextureVariable*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};