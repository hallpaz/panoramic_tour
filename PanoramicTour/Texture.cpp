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
    width = FreeImage_GetWidth(bitmap);
    height = FreeImage_GetHeight(bitmap);
    int channels = FreeImage_GetBPP(bitmap);
    std::cout << "Carregada a width: " << width << " e tambem a height: " << height << std::endl;
    std::cout << "Channels: " << channels << std::endl;
}

/**
 * Destructor. Releases memory allocated to pixels attribute
 */
Texture::~Texture() {
    
}

void Texture::unload(){
    FreeImage_Unload(bitmap);
}
/**
 * Returns a GLubyte pointer with RGB/RGBA coordinates.
 */
void *Texture::getData(){
    return FreeImage_GetBits(bitmap);
}

/**
 * Returns texture image width
 */
unsigned int Texture::getWidth(){
    return width;
}

/**
 * Returns texture image height
 */
unsigned int Texture::getHeight(){
    return height;
}


