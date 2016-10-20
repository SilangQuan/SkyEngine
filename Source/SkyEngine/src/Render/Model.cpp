#include "Render/Model.h"
#include "Render/ShaderProgram.h"
#include "Render/Mesh.h"
#include "Core/ObjLoader.h"


Model::Model(GLchar* path, bool usingAssimp)
{
	string str = path;
	int index = str.find_last_of("/");
	directory = str.substr(0, index + 1);

	if (usingAssimp)
	{
		LoadModelByAssimp(path);
	}
	else
	{
		LoadModel(path);
	}
}

Model::~Model()
{

}

void Model::CreateBufferData()
{
	for (std::vector<Mesh>::iterator iter = meshes.begin(); iter != meshes.end(); ++iter)
	{
		iter->CreateBufferData();
	}
}
void Model::Draw(ShaderProgram* shadeProgram)
{
	//for (GLuint i = 0; i < this->meshes.size(); i++)
	//	this->meshes[i].Draw(shadeProgram);
}

vector<Mesh>* Model::GetMeshes()
{
	return &meshes;
}

void Model::LoadModel(string path)
{
	vector<tinyobj::ObjMesh> shapes;
	vector<tinyobj::ObjMaterial> materials;

	string err;
	bool ret = tinyobj::ObjLoader::LoadObj(shapes, materials, err, path.c_str(), directory.c_str());
	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << endl;
	}

	if (!ret) {
		qDebug() << "LoadModel" << path << " error";
		exit(1);
	}else
	{
		qDebug() << path << " Loaded!";
		qDebug() << "shapes.size()" << (int)shapes.size();
		qDebug() << "materials.size()" << (int)materials.size();
	}

	for (int i = 0; i < shapes.size(); i++)
	{
		qDebug() << "shapes: " << shapes[i].name;
		qDebug() << "shapes: " << (int)shapes[i].material_ids.size();
		meshes.push_back(ProcessMesh(&shapes[i], materials));
	}

	// Process materials
	for (size_t i = 0; i < materials.size(); i++)
	{
		qDebug() << "materials: " << materials[i].diffuse_texname.c_str();
	}
}


		//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
/*
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	std::cout << "# of shapes    : " << shapes.size() << std::endl;
	std::cout << "# of materials : " << materials.size() << std::endl;
}*/


Mesh Model::ProcessMesh(tinyobj::ObjMesh* mesh, vector<tinyobj::ObjMaterial>& materials)
{
	vector<Vector3> positions;
	vector<Vector3> normals;
	vector<Vector2> uvs;
	vector<GLuint> indices = mesh->indices;
	vector<TextureVariable*> textures;

	positions.reserve(mesh->positions.size() / 3);
	normals.reserve(mesh->positions.size() / 3);
	uvs.reserve(mesh->positions.size() / 3);
	//memcpy(positions.data(), mesh->positions.data(), sizeof(Vector3) * positions.size());

	bool hasUV = mesh->texcoords.size() > 0;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->positions.size()/3; i++)
	{
		positions.push_back(Vector3(mesh->positions[3 * i + 0], mesh->positions[3 * i + 1], mesh->positions[3 * i + 2]));

		normals.push_back(Vector3(mesh->normals[3 * i + 0], mesh->normals[3 * i + 1], mesh->normals[3 * i + 2]));

		Vector2 tmpTexcoord(0,1);
		// Texture Coordinates
		if (hasUV) // Does the mesh contain texture coordinates?
		{
			tmpTexcoord.x = mesh->texcoords[2 * i + 0];
			tmpTexcoord.y = mesh->texcoords[2 * i + 1];
		}

		uvs.push_back(tmpTexcoord);
	}

	qDebug() << mesh->name << (int)mesh->material_ids.size();

/*
	for (int i = 0; i < mesh->material_ids.size(); i++)
	{
		tinyobj::ObjMaterial mat = materials[mesh->material_ids[i]];
		qDebug() << mesh->name<< " " << mat.diffuse_texname;
	}
*/

	// Return a mesh object created from the extracted mesh data
	return Mesh(positions, normals, uvs, indices, textures);
}

void Model::LoadModelByAssimp(string path)
{
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	this->ProcessNodeByAssimp(scene->mRootNode, scene);
}

Mesh Model::ProcessMeshByAssimp(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	vector<Vector3> positions;
	vector<Vector3> normals;
	vector<Vector2> uvs;
	//vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<TextureVariable*> textures;

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		//Vertex vertex;
		Vector3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		positions.push_back(vector);
		// Normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		normals.push_back(vector);

		Vector2 tmpVec2(0, 0);
		// Texture Coordinates
		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			tmpVec2.x = mesh->mTextureCoords[0][i].x;
			tmpVec2.y = mesh->mTextureCoords[0][i].y;
		}
		uvs.push_back(tmpVec2);

	}
	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<TextureVariable*> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<TextureVariable*> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(positions, normals, uvs, indices, textures);
}

void Model::ProcessNodeByAssimp(aiNode* node, const aiScene* scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->ProcessMeshByAssimp(mesh, scene));
	}
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNodeByAssimp(node->mChildren[i], scene);
	}
}

vector<TextureVariable*> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<TextureVariable*> tmpTextures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// If texture hasn't been loaded already, load it
		string path = this->directory + "/" + str.C_Str();
			
		Texture* texture = ResourceManager::GetInstance()->TryGetResource<Texture>(path);

		stringstream ss;
		ss << "material.";
		ss << typeName;
		ss << i;
		TextureVariable* textureVariable = new TextureVariable(texture, -1, ss.str());

		tmpTextures.push_back(textureVariable);
	}
	return tmpTextures;
}
