#include "VertexMesh.h"

VertexMesh::VertexMesh(): MyPosition(), MyTexcoord()
{
	
}

VertexMesh::VertexMesh(Vector3D position, Vector2D texcoord)
{
	this->MyPosition = position;
	this->MyTexcoord = texcoord;
	
}

VertexMesh::VertexMesh(const VertexMesh& vertex)
{
	this->MyPosition = vertex.MyPosition;
	this->MyTexcoord = vertex.MyTexcoord;
}

VertexMesh::~VertexMesh()
{
}
