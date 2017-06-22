#ifndef _GEOMETRYgENERATOR_H_
#define _GEOMETRYgENERATOR_H_
#include "cocos2d.h"
using cocos2d::Vec2;
using cocos2d::Vec3;


#define VertexOffset(Type,off) ((void*)((Type*)0 + off))


namespace ZhiFa
{
	class GeometryGenerator
	{
	public:
		struct Vertex
		{
			Vertex(){}
			Vertex(const Vec3& p, const Vec3& n, const Vec3& t, const Vec2& uv)
				: Position(p), Normal(n), TangentU(t), TexC(uv){}
			Vertex(
				float px, float py, float pz,
				float nx, float ny, float nz,
				float tx, float ty, float tz,
				float u, float v)
				: Position(px, py, pz), Normal(nx, ny, nz),
				TangentU(tx, ty, tz), TexC(u, v){}

			Vec3 Position;
			Vec3 Normal;
			Vec3 TangentU;
			Vec2 TexC;
		};

		struct MeshData
		{
			std::vector<Vertex> Vertices;
			std::vector<GLushort> Indices;
		};

		///<summary>
		/// Creates a box centered at the origin with the given dimensions.
		///</summary>
		void CreateBox(float width, float height, float depth, MeshData& meshData);

		///<summary>
		/// Creates a sphere centered at the origin with the given radius.  The
		/// slices and stacks parameters control the degree of tessellation.
		///</summary>
		void CreateSphere(float radius, unsigned int sliceCount, unsigned int stackCount, MeshData& meshData);

		///<summary>
		/// Creates a geosphere centered at the origin with the given radius.  The
		/// depth controls the level of tessellation.
		///</summary>
		void CreateGeosphere(float radius, unsigned int numSubdivisions, MeshData& meshData);

		///<summary>
		/// Creates a cylinder parallel to the y-axis, and centered about the origin.  
		/// The bottom and top radius can vary to form various cone shapes rather than true
		// cylinders.  The slices and stacks parameters control the degree of tessellation.
		///</summary>
		void CreateCylinder(float bottomRadius, float topRadius, float height, unsigned int sliceCount, unsigned int stackCount, MeshData& meshData);

		///<summary>
		/// Creates an mxn grid in the xz-plane with m rows and n columns, centered
		/// at the origin with the specified width and depth.
		///</summary>
		void CreateGrid(float width, float depth, unsigned int m, unsigned int n, MeshData& meshData);

		///<summary>
		/// Creates a quad covering the screen in NDC coordinates.  This is useful for
		/// postprocessing effects.
		///</summary>
		void CreateFullscreenQuad(MeshData& meshData);

	private:
		void Subdivide(MeshData& meshData);
		void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, unsigned int sliceCount, unsigned int stackCount, MeshData& meshData);
		void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, unsigned int sliceCount, unsigned int stackCount, MeshData& meshData);
	};
};


#endif