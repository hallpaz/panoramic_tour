/*
 * LPShader.h
 *
 *  Created on: 26 juin 2013
 *      Author: hallison
 */

#ifndef SHADER_H_
#define SHADER_H_

#ifdef MOBILE
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
#else
    #include <OpenGL/gl3.h>
#endif

#include <string>
#include <unordered_map>

namespace LayerSceneGraph {
    
enum {VERTEX_SHADER, FRAGMENT_SHADER};
    
enum Buffer_Indexes : GLint{
        VERTEX_BUFFER_INDX,
        COLOR_BUFFER_INDX,
        TEXTURE_BUFFER_INDX
};
/**
 * Shader class. This class encapsulates all basic operations necessaries to read shader files create, compile and link a shader program.
 *
 */
class LPShader {

public:
    LPShader(const std::string vertexshaderFile, const std::string fragmentShaderFile);
	virtual ~LPShader();
	void inline setUpShader(const GLchar *vertexshaderCode, const GLchar *fragmentShaderCode);
    void linkProgram();
    void bindAttributes(const std::unordered_map<GLint, std::string> attributes_map);
	void enableTexture();
	GLuint loadShader(GLenum type, const GLchar *shaderSrc);
	GLuint getProgram();
private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;
    GLuint program;
    GLuint textureId;
    GLuint gvSamplerHandle;
    GLint getLinkStatus();
    std::string readShaderFile(const GLchar *filename, int shaderType);
    
};

} /* namespace LayerSceneGraph */
#endif /* SHADER_H_ */
