#include <stdio.h>
#include <exception>
#include <SOIL.h>

#include "textures\Texture.h"

namespace engine
{
	Texture::Texture(const char* filename, GLuint format)
	{
		int width, height;
		unsigned char* image = SOIL_load_image(filename, &width, &height, 0, format - GL_RGB + SOIL_LOAD_RGB);

		if (!image)
		{
			printf("cannot load image: %s\n", filename);
			throw std::exception();
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
	}
}