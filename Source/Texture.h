#pragma once


class Texture
{
private:
	unsigned int RendererID;
	unsigned int slot;
public:
	Texture(const char* path, int width, int height, int bits_per_pixel, int slot);
	~Texture();

	void Bind(unsigned int slot);
	void Unbind();

	inline unsigned int GetSlot() { return slot; }
};
