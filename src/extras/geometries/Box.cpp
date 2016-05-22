#include "extras\geometries\Box.h"

namespace engine
{
	void Box::init()
	{
		float px = 0.5f * width;
		float nx = -px;

		float py = 0.5f * height;
		float ny = -py;

		float pz = 0.5f * depth;
		float nz = -pz;

		std::vector<float> vertices = 
		{
			nx, ny, pz,		px, ny, pz,		px, py, pz,		nx, py, pz,		// front
			px, ny, pz,		px, ny, nz,		px, py, nz,		px, py, pz,		// right
			px, ny, nz,		nx, ny, nz,		nx, py, nz,		px, py, nz,		// back
			nx, ny, nz,		nx, ny, pz,		nx, py, pz,		nx, py, nz,		// left
			nx, py, pz,		px, py, pz,		px, py, nz,		nx, py, nz,		// top
			px, ny, pz,		nx, ny, pz,		nx, ny, nz,		px, ny, nz,		// bottom
		};

		std::vector<float> normals = 
		{
			 0,  0,  1,		 0,  0,  1,		 0,  0,  1,		 0,  0,  1,
			 1,  0,  0,		 1,  0,  0,		 1,  0,  0,		 1,  0,  0,
			 0,  0, -1,		 0,  0, -1,		 0,  0, -1,		 0,  0, -1,
			-1,  0,  0,		-1,  0,  0,		-1,  0,  0,		-1,  0,  0,
			 0,  1,  0,		 0,  1,  0,		 0,  1,  0,		 0,  1,  0,
			 0, -1,  0,		 0, -1,  0,		 0, -1,  0,		 0, -1,  0,
		};

		std::vector<float> uvs =
		{
			0, 0,	1, 0,	1, 1,	0, 1,
			0, 0,	1, 0,	1, 1,	0, 1,
			0, 0,	1, 0,	1, 1,	0, 1,
			0, 0,	1, 0,	1, 1,	0, 1,
			0, 0,	1, 0,	1, 1,	0, 1,
			0, 0,	1, 0,	1, 1,	0, 1,
		};

		indices = 
		{
			 0,  1,  3,		 1,  2,  3,		// front
			 4,  5,  7,		 5,  6,  7,		// right
			 8,  9, 11,		 9, 10, 11,		// back
			12, 13, 15,		13, 14, 15,		// left
			16, 17, 19,		17, 18, 19,		// top
			20, 21, 23,		21, 22, 23,		// bottom
		};

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normals", new BufferAttribute(normals, 3));
		addAttribute("uvs", new BufferAttribute(uvs, 2));
	}
}