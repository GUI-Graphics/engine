#include "controls/OrbitControl.h"

namespace engine
{
	OrbitControl::OrbitControl(Object3D& object, Window& window)
		: object(object)
		, window(window)
		, state(State::None)
		, scale(1)
		, panOffset(0, 0, 0)
	{
		window.addEventHandler(*this);
		addCallback(Event::MOUSE_DOWN, &OrbitControl::onMouseDown);
		addCallback(Event::MOUSE_WHEEL, &OrbitControl::onMouseWheel);

		getRotateAngle();
	}

	void OrbitControl::onMouseUp(MouseEvent& event)
	{
		if (!enabled) return;

		removeCallback(Event::MOUSE_MOVE, &OrbitControl::onMouseMove);
		removeCallback(Event::MOUSE_UP, &OrbitControl::onMouseUp);

		state = State::None;
	}

	void OrbitControl::onMouseDown(MouseEvent& event)
	{
		if (!enabled) return;

		if (event.button == MouseButton::Left)
		{
			if (noRotate) return;

			state = State::Rotate;
			rotateStart.set((float)event.mouseX, (float)event.mouseY);
		}
		else if (event.button == MouseButton::Middle)
		{
			if (noRotate) return;

			state = State::Dolly;
			dollyStart.set((float)event.mouseX, (float)event.mouseY);
		}
		else if (event.button == MouseButton::Right)
		{
			if (noPan) return;

			state = State::Pan;
			panStart.set((float)event.mouseX, (float)event.mouseY);
		}

		if (state != State::None)
		{
			addCallback(Event::MOUSE_MOVE, &OrbitControl::onMouseMove);
			addCallback(Event::MOUSE_UP, &OrbitControl::onMouseUp);
		}
	}

	void OrbitControl::onMouseMove(MouseEvent& event)
	{
		if (!enabled) return;

		if (state == State::Rotate)
		{
			if (noRotate) return;

			Vector2 end((float)event.mouseX, (float)event.mouseY);
			Vector2 delta = end - rotateStart;
			rotateLeft(2 * Math::PI * delta.x / window.width * rotateSpeed);
			rotateUp(2 * Math::PI * delta.y / window.height * rotateSpeed);
			rotateStart = end;
		}
		else if (state == State::Dolly)
		{
			if (noZoom) return;

			Vector2 end((float)event.mouseX, (float)event.mouseY);
			Vector2 delta = end - dollyStart;

			if (delta.y > 0)
			{
				dollyIn(1.2f);
			}
			else if (delta.y < 0)
			{
				dollyOut(1.2f);
			}

			dollyStart = end;
		}
		else if (state == State::Pan)
		{
			if (noPan) return;

			Vector2 end((float)event.mouseX, (float)event.mouseY);
			Vector2 delta = end - panStart;
			pan(delta.x / window.width * 10, delta.y / window.height * 10);
			panStart = end;
		}

		if (state != State::None) update();
	}

	void OrbitControl::onMouseWheel(WheelEvent& event)
	{
		if (!enabled || noZoom || state != State::None) return;

		if (event.deltaY > 0)
		{
			dollyOut(1.2f);
		}
		else
		{
			dollyIn(1.2f);
		}

		update();
	}

	void OrbitControl::getRotateAngle()
	{
		Vector3 offset = object.position() - target;
		longitude = atan2f(offset.x, offset.z);
		latitude = atan2f(offset.y, sqrtf(offset.x * offset.x + offset.z * offset.z));
	}

	void OrbitControl::update()
	{
		if (autoRotate) rotateLeft(rotateSpeed / 60.0f);

		Vector3 offset = object.position() - target;
		float radius = offset.length() * scale;
		float clat = cosf(latitude);
		float slon = sinf(longitude);
		float clon = cosf(longitude);
		float x = radius * clat * slon;
		float y = radius * sinf(latitude);
		float z = radius * clat * clon;
		object.position(target.x + x, target.y + y, target.z + z);

		target += panOffset;
		object.lookAt(target);

		panOffset = Vector3(0, 0, 0);
		scale = 1;
	}
}