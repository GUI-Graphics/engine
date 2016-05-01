#include "renderer\GLRenderer.h"

namespace engine
{
	void GLRenderer::render(Object3D& scene, Camera& camera)
	{
		scene.updateMatrixWorld();
		if (!camera.parent) camera.updateMatrixWorld();
		camera.updateMatrixWorldInverse();
	}
}