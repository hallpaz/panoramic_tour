/*
 * Texture.h
 *
 *  Created on: 28 juin 2013
 *      Author: hallison
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <FreeImage.h>


class Texture {
private:
    FIBITMAP *bitmap;

public:
    
    Texture(std::string filename);
	virtual ~Texture();

	BYTE *getData();
	size_t getWidth();
	size_t getHeight();
};

#endif /* TEXTURE_H_ */
