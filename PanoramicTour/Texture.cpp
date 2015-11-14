/*
 * Texture.cpp
 *
 *  Created on: 28 juin 2013
 *      Author: hallison
 */

#include "Texture.h"

#include <iostream>



/**
 * Constructor.
 * @param pxls: GLubyte pointer which holds RGBA coordinates.
 * @param w:    texture image width
 * @param h:    texture image height
 */
Texture::Texture(unsigned char *pxls, size_t w, size_t h) {
	//TODO think about references
	pixels = pxls;
	width = w;
	height = h;
    //loadTexture("living room");
}
/**
 * Destructor. Releases memory allocated to pixels attribute
 */
Texture::~Texture() {
	delete[] pixels;
}
/**
 * Returns a GLubyte pointer with RGBA coordinates.
 */
const unsigned char *Texture::getPixels() {
	return pixels;
}
/**
 * Returns texture image width
 */
size_t Texture::getWidth() {
	return width;
}

//TODO implement this method
Texture& Texture::operator =(Texture& texture) {
	if(this != &texture){
		//do something
	}
	return *this;
}

/**
 * Returns texture image height
 */
size_t Texture::getHeight() {
	return height;
}

/**
 * Constructor. This method creates a new texture from the path of an image to be used as texture
 */
Texture::Texture(const char* imageName) {
    
}

/**
 * Copy constructor
 */
Texture::Texture(const Texture& copy) {
	size_t max;
	width = copy.width; height = copy.height;
	max = width*height;
	pixels = new unsigned char[max];
	for(int i = 0; i < max; i++){
		pixels[i] = copy.pixels[i];
	}
}
