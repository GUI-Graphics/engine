#pragma once

#include "camera\Camera.h"

namespace engine
{
	class GLRenderer
	{
	public:
		GLRenderer()
		{ }

		void render(Object3D& scene, Camera& camera);

	protected:
		void projectObject(Object3D& object);
	};
}
