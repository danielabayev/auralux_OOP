#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>


class Graphic
{
public:
	static Graphic& PicturesObject();
	~Graphic() = default;

private:
	Graphic();

};