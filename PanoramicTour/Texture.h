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
    unsigned int width;
    unsigned int height;

public:
    
    Texture(std::string filename);
	virtual ~Texture();

	void *getData();
    void unload();
	unsigned int getWidth();
	unsigned int getHeight();
};

#endif /* TEXTURE_H_ */
