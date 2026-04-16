#include "Model.h"
#include "Tool.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>


Model::Model(const std::string& path)
{
	LoadModel(path);
}

Model::~Model()
{
	for(auto it : m_mapTexture)
	{
		delete it.second;
	}

	for (auto it : m_meshs)
	{
		delete it;
	}
}

void Model::Draw(const GlProgram& shader)
{
	for (auto it : m_meshs)
	{
		it->Draw(shader);
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiPostProcessSteps::aiProcess_Triangulate | aiPostProcessSteps::aiProcess_FlipUVs);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
		|| scene->mRootNode == nullptr)
	{
		std::cout << "error: assimp:" << importer.GetErrorString() << std::endl;
		return;
	}

	m_strDirectory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumMeshes; ++i)
	{
		m_meshs.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (uint i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices(mesh->mNumVertices);
	std::vector<uint> indices;
	std::vector<Texture> textures;

	for (uint i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.m_position.SetX(mesh->mVertices[i].x);
		vertex.m_position.SetY(mesh->mVertices[i].y);
		vertex.m_position.SetZ(mesh->mVertices[i].z);

		if (mesh->HasNormals())
		{
			vertex.m_normal.SetX(mesh->mNormals[i].x);
			vertex.m_normal.SetY(mesh->mNormals[i].y);
			vertex.m_normal.SetZ(mesh->mNormals[i].z);
		}

		if (mesh->mTextureCoords[0] != nullptr)
		{
			vertex.m_texCoords.SetX(mesh->mTextureCoords[0][i].x);
			vertex.m_texCoords.SetY(mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertex.m_texCoords.SetX(0.0f);
			vertex.m_texCoords.SetY(0.0f);
		}
		vertices[i] = vertex;
	}

	for (uint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];

		for (uint j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuse = LoadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::TextureType::eDiffuse);
		textures.insert(textures.end(), diffuse.begin(), diffuse.end());

		std::vector<Texture> mirror = LoadMaterialTextures(material, aiTextureType_SPECULAR, Texture::TextureType::eMirror);
		textures.insert(textures.end(), mirror.begin(), mirror.end());
	}
	return new Mesh(std::move(vertices), std::move(textures), std::move(indices));
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TextureType typeName)
{
	std::vector<Texture> textures;
	int nCount = mat->GetTextureCount(type);
	for (int i = 0; i < nCount; ++i)
	{
		aiString path;
		Texture texture;
		mat->GetTexture(type, i, &path);
		auto it = m_mapTexture.find(path.C_Str());
		if (it != m_mapTexture.end())
		{
			texture.m_texture = it->second;
		}
		else
		{
			TextureUnit* unit = new TextureUnit;
			unit->LoadImg(m_strDirectory + "/" + path.C_Str(), true);
			unit->CreateGenerateMipmap();
			unit->SetRowAround(TextureUnit::eREPEAT);
			unit->SetColumnAround(TextureUnit::eREPEAT);
			unit->SetAmplifyStrategy(TextureUnit::eNEAREST);
			unit->SetShrinkStrategy(TextureUnit::eNEAREST);

			m_mapTexture[path.C_Str()] = unit;

			texture.m_texture = unit;
		}
		texture.m_type = typeName;
		textures.push_back(texture);
	}

	return textures;
}
