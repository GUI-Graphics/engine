#pragma once

#include <map>
#include <string>
#include "BufferAttribute.h"

namespace engine
{
	class BufferGeometry
	{
	public:
		BufferGeometry() : vao(0), index(0)
		{ }

		virtual ~BufferGeometry()
		{
			for (auto & attribute : attributes) delete attribute.second;
			if (index) glDeleteBuffers(1, &index);
			if (vao) glDeleteVertexArrays(1, &vao);
		}

		BufferAttribute* getAttribute(std::string name)
		{
			auto itr = attributes.find(name);
			if (itr != attributes.end()) return itr->second;

			return nullptr;
		}

		void addAttribute(std::string name, BufferAttribute* attribute)
		{
			attributes[name] = attribute;
		}

		void updateAttributes()
		{
			if (!indices.empty() && !index)
			{
				glGenBuffers(1, &index);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
			}

			for (auto& attribute : attributes) attribute.second->update();
		}

	public:
		std::vector<unsigned int> indices;
		std::map<std::string, BufferAttribute*> attributes;

		GLuint vao;
		GLuint index;
	};
}