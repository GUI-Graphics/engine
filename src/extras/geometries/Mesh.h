#pragma once

#include <core\Object3D.h>
#include <core\BufferGeometry.h>
#include <renderer\GLProgram.h>

namespace engine
{
	class Mesh : public Object3D
	{
	public:
		Mesh(BufferGeometry& geometry, GLProgram& program) : geometry(geometry), program(program)
		{ }

	public:
		BufferGeometry& geometry;
		GLProgram& program;
	};
}