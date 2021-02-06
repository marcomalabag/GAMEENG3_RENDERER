#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
#include <codecvt>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* fullPath): Resource(fullPath)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warning;
	std::string error;

	std::string filepath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(fullPath);

	bool res = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filepath.c_str());

	if (!error.empty()) {
		throw std::exception("Mesh not created successfully");
	}

	if (!res) {
		throw std::exception("Mesh not created successfully");
	}

	if (shapes.size() > 1) {
		throw std::exception("Mesh not created successfully");
	}

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;


	for (size_t t = 0; t < shapes.size(); t++) {
		size_t indexOffSet = 0;
		list_vertices.reserve(shapes[t].mesh.indices.size());
		list_indices.reserve(shapes[t].mesh.indices.size());
		for (size_t g = 0; g < shapes[t].mesh.num_face_vertices.size(); g++) {
			unsigned char numFaceVertices = shapes[t].mesh.num_face_vertices[g];

			for (unsigned char v = 0; v < numFaceVertices; v++) {
				tinyobj::index_t index = shapes[t].mesh.indices[indexOffSet + v];

				tinyobj::real_t vx = attributes.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attributes.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attributes.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attributes.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attributes.texcoords[index.texcoord_index * 2 + 1];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back(indexOffSet + v);
			}
			indexOffSet += numFaceVertices;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	this->MyVertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, size_shader);

	this->MyIndexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexbuffer(&list_indices[0], (UINT)list_indices.size());
}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return this->MyVertexBuffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return this->MyIndexBuffer;
}
