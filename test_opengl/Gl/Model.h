#pragma once
#include "Mesh.h"
#include "assimp/material.h"
#include <map>

struct aiNode;
struct aiScene;
struct aiMesh;
class Model
{
public:
	Model(const std::string& path);
	~Model();
	void Draw(const GlProgram& shader);

private:
	std::vector<Mesh*> m_meshs;		//����
	std::string m_strDirectory;		//ģ���ļ�·��
	std::map <std::string, TextureUnit*> m_mapTexture;

	void LoadModel(const std::string& path);

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TextureType typeName);
};

