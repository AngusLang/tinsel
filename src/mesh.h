#pragma once

#include <vector>

#include "maths.h"
#include "bvh.h"

struct Mesh
{
	~Mesh()
	{
		delete[] bvh.nodes; 
	}

    void AddMesh(Mesh& m);

	void DuplicateVertex(int i);

    void CalculateNormals();
    void Transform(const Mat44& m);
	void Normalize(float s=1.0f);	// scale so bounds in any dimension equals s and lower bound = (0,0,0)

    void GetBounds(Vec3& minExtents, Vec3& maxExtents) const;

	void RebuildBVH();
    void RebuildCDF();
    
    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    std::vector<int> indices;

    std::vector<float> cdf;
    float area;

	BVH bvh;
};


// create mesh from file
Mesh* ImportMeshFromObj(const char* path);
Mesh* ImportMeshFromPly(const char* path);
Mesh* ImportMeshFromBin(const char* path);
Mesh* ImportMeshFromWo3(const char* path);

// just switches on filename
Mesh* ImportMesh(const char* path);

// save mesh in optimized binary format
void ExportMeshToBin(const char* path, const Mesh* m);
void ExportMeshToObj(const char* path, const Mesh* m);

// create procedural primitives
Mesh* CreateQuadMesh(float size, float y=0.0f);
Mesh* CreateDiscMesh(float radius, int segments);
Mesh* CreateTetrahedron();
Mesh* CreateSphere(int slices, int segments, float radius = 1.0f);
Mesh* CreateCapsule(int slices, int segments, float radius = 1.0f, float halfHeight = 1.0f);
