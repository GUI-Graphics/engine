#pragma once

#include <vector>
#include <glad\glad.h>

namespace engine
{
	class BufferAttribute
	{
	public:
		BufferAttribute(std::vector<float>& array, unsigned char itemSize)
			: itemSize(itemSize)
			, array(std::move(array))
			, buffer(0)
		{ }

		~BufferAttribute()
		{
			if (buffer) glDeleteBuffers(1, &buffer);
		}

		void update()
		{
			if (!buffer)
			{
				glGenBuffers(1, &buffer);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * array.size(), array.data(), GL_STATIC_DRAW);
			}
		}

	public:
		unsigned char itemSize;
		std::vector<float> array;
		GLuint buffer;
	};
}