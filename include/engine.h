#pragma once

#include <math\Color.h>
#include <math\Vector2.h>
#include <core\BufferGeometry.h>
#include <camera\PerspectiveCamera.h>
#include <controls\OrbitControl.h>
#include <renderer\GLProgram.h>
#include <renderer\GLRenderer.h>
#include <extras\geometries\BoxBufferGeometry.h>
#include <extras\geometries\SphereBufferGeometry.h>
#include <extras\geometries\PlaneBufferGeometry.h>
#include <extras\geometries\TorusBufferGeometry.h>
#include <extras\helpers\BoxHelper.h>
#include <extras\helpers\GridHelper.h>
#include <extras\helpers\MarchingCube.h>

#define MAKE_PROGRAM(program, vertex, fragment)		\
	GLShader vert(GL_VERTEX_SHADER);				\
	GLShader frag(GL_FRAGMENT_SHADER);				\
	vert.fromFile(vertex);							\
	frag.fromFile(fragment);						\
	GLProgram program(vert, frag);					\
	program.compile()