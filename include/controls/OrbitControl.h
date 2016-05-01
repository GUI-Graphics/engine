#pragma once

#include "window/Window.h"
#include "math/Math.h"
#include "math/Vector2.h"
#include "core/Object3D.h"

namespace engine
{
	class OrbitControl : public EventHandler
	{
	public:
		enum class State : unsigned char { None, Rotate, Pan, Dolly };

		OrbitControl(Object3D& object, Window& window);

	public:
		bool enabled	= true;
		bool noRotate	= false;
		bool noPan		= false;
		bool noZoom		= false;
		bool autoRotate = false;

		float rotateSpeed		= 0.5f;
		float autoRotateSpeed	= 1;

		float minLatitude =  Math::PI * -0.5f;
		float maxLatitude =  Math::PI *  0.5f;

		float minLongitude = -Math::PI;
		float maxLongitude =  Math::PI;

		Vector3 target = { 0, 0, 0 };

		Window& window;
		Object3D& object;

	private:
		State state;

		float longitude;
		float latitude;
		float scale;

		Vector3 panOffset;

		Vector2 rotateStart;
		Vector2 dollyStart;
		Vector2 panStart;

		void onMouseUp(MouseEvent& e);
		void onMouseDown(MouseEvent& e);
		void onMouseMove(MouseEvent& e);
		void onMouseWheel(WheelEvent& e);

		void getRotateAngle();

		void rotateLeft(float angle)
		{
			longitude -= angle;

			if (minLongitude == -Math::PI && maxLongitude == Math::PI)
			{
				if (longitude > Math::PI) longitude = longitude - 2 * Math::PI;
				else if (longitude < -Math::PI) longitude = 2 * Math::PI + longitude;
			}
			else
			{
				if (longitude > maxLongitude) longitude = maxLongitude;
				else if (longitude < minLongitude) longitude = minLongitude;
			}
		}

		void rotateUp(float angle)
		{
			latitude += angle;

			if (latitude > maxLatitude) latitude = maxLatitude;
			else if (latitude < minLatitude) latitude = minLatitude;
		}

		void dollyIn(float dollyScale)
		{
			scale *= dollyScale;
		}

		void dollyOut(float dollyScale)
		{
			scale /= dollyScale;
		}

		void pan(float offsetX, float offsetY)
		{
			const float* e = object.matrix.elements;

			Vector3 x(e[0], e[4], e[8]);
			x *= -offsetX;
			panOffset += x;

			Vector3 y(e[1], e[5], e[9]);
			y *= offsetY;
			panOffset += y;
		}

		void update();
	};
}