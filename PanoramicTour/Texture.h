/*
 * Texture.h
 *
 *  Created on: 28 juin 2013
 *      Author: hallison
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

class Texture {
private:
	size_t width;
	size_t height;
	unsigned char *pixels;
public:
	Texture(unsigned char * pxls, size_t w, size_t h);
	Texture(const Texture& copy);
	Texture(const char *filename);
    
	void initFromFile(const char *filename);
	virtual ~Texture();

	Texture& operator=(Texture& texture);
	const unsigned char *getPixels();
	size_t getWidth();
	size_t getHeight();
};

#endif /* TEXTURE_H_ */
