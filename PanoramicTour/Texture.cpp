/*
 * Texture.cpp
 *
 *  Created on: 28 juin 2013
 *      Author: hallison
 */

#include "Texture.h"

#include <iostream>


/**
 * Constructor. This method creates a new texture from the path of an image to be used as texture
 */
Texture::Texture(std::string imageName) {
    bitmap = FreeImage_Load(FreeImage_GetFileType(imageName.c_str(), 0), imageName.c_str());
}

/**
 * Destructor. Releases memory allocated to pixels attribute
 */
Texture::~Texture() {
    FreeImage_Unload(bitmap);
}
/**
 * Returns a GLubyte pointer with RGB/RGBA coordinates.
 */
BYTE *Texture::getData() {
    return FreeImage_GetBits(bitmap);
}

/**
 * Returns texture image width
 */
size_t Texture::getWidth() {
    return FreeImage_GetWidth(bitmap);
}

/**
 * Returns texture image height
 */
size_t Texture::getHeight() {
	return FreeImage_GetHeight(bitmap);
}


