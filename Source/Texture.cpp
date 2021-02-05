#include "./Texture.h"

#define GLEW_STATIC
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./vendor/stb_image/stb_image.h"

Texture::Texture(const char* path, int width, int height, int bits_per_pixel, int slot)
{
	this->slot = slot;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* image_data = stbi_load(path, &width, &height, &bits_per_pixel, 4);

	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_2D, RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glActiveTexture(GL_TEXTURE0 + slot);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data); // could also be nullptr
	glBindTexture(GL_TEXTURE_2D, 0);

	if (image_data != nullptr) stbi_image_free(image_data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &RendererID);
}

void Texture::Bind(unsigned int slot)
{
	this->slot = slot;

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
