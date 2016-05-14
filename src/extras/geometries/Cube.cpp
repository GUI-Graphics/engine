#include "extras\geometries\Cube.h"

namespace engine
{
	Cube::Cube(float length) : length(length)
	{
		float p = 0.5f * length;
		float n = -p;

		std::vector<float> vertices =
		{
			n, n, p,	p, n, p,	p, p, p,	n, p, p,		// front
			p, n, p,	p, n, n,	p, p, n,	p, p, p,		// right
			p, n, n,	n, n, n,	n, p, n,	p, p, n,		// back
			n, n, n,	n, n, p,	n, p, p,	n, p, n,		// left
			n, p, p,	p, p, p,	p, p, n,	n, p, n,		// top
			p, n, p,	n, n, p,	n, n, n,	p, n, n,		// bottom
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
			 0,  1,  3,		 1,  2,  3,
			 4,  5,  7,		 5,  6,  7,
			 8,  9, 11,		 9, 10, 11,
			12, 13, 15,		13, 14, 15,
			16, 17, 19,		17, 18, 19,
			20, 21, 23,		21, 22, 23,
		};

		addAttribute("position", new BufferAttribute(vertices, 3));
		addAttribute("normals", new BufferAttribute(normals, 3));
		addAttribute("uvs", new BufferAttribute(uvs, 2));
	}
}