#include "Model.hpp"

#include "Mesh.hpp"

using namespace DEM;
using namespace DEM::Core;

Model::Model(const std::string& path)
{
	m_path = path;
	load();
}

Model::~Model()
{
}

Model& Model::load()
{
	tinyobj::LoadObj(m_shapes, m_materials, m_path.c_str());
	return *this;
}

Mesh* Model::Instanciate(DEM_UINT index)
{
	std::vector<Vertex*> vertice;

	const std::vector<unsigned int> &indices = m_shapes[index].mesh.indices;
	const std::vector<float> &positions = m_shapes[index].mesh.positions;
	const std::vector<float> &normals = m_shapes[index].mesh.normals;
	const std::vector<float> &texcoords = m_shapes[index].mesh.texcoords;

	for (DEM_UINT i = 0; i < positions.size(); i += 3)
	{
		Vertex *vert = new Vertex(Math::Vector3(positions.at(i), positions.at(i + 1), positions.at(i + 2)));

		if ((i + 3) < normals.size())
		{
			vert->normal = Math::Vector3(normals.at(i), normals.at(i + 1), normals.at(i + 2));
		}

		if ((i + 2) < texcoords.size())
		{
			vert->uv = Math::Vector2(texcoords.at(i), texcoords.at(i + 1));
		}

		vertice.push_back(vert);
	}

	Geometry *geometry = new Geometry(vertice, indices);
	LambertMaterial *material = new LambertMaterial(Math::Color(1.0f, 1.0f, 1.0f, 1.0f), Math::Color(0.5f, 0.5f, 0.5f, 1.0f));
	return new Mesh(geometry, material);
}

Mesh* Model::InstanciateAll()
{
	Mesh *root = 0;

	if (m_shapes.size() > 0)
	{
		root = Instanciate(0);

		for (DEM_UINT i = 1; i < m_shapes.size(); ++i)
		{
			Mesh *shapeMesh = Instanciate(i);
			root->addChild(shapeMesh);
		}
	}

	return root;
}

std::string Model::getPath() const
{
	return m_path;
}

void Model::setPath(const std::string& path)
{
	m_path = path;
}