/*
 * LPShader.cpp
 *
 *  Created on: 26 juin 2013
 *      Author: hallison
 */


#include <cstring>

#include <iostream>
#include <fstream>
#include <sstream>

#include "LPShader.h"

#define max_index 200


namespace LayerSceneGraph {

/**
 * Constructor. It's necessary to pass the path for a vertex shader file and a fragment shader file
 */
LPShader::LPShader(const std::string vertexShaderFile, const std::string fragmentShaderFile) {
    
    std::string vertexShaderCode, fragmentShaderCode;
    
    vertexShaderCode = readShaderFile(vertexShaderFile.c_str(), VERTEX_SHADER);
    fragmentShaderCode = readShaderFile(fragmentShaderFile.c_str(), FRAGMENT_SHADER);
    
    setUpShader(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
    
}
    

/**Shader destructor
 * Detachs and deletes each shader. Deletes shader program too.
 * */
LPShader::~LPShader() {
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(program);
}

/**
 * This method attachs both vertex and fragment shaders to a shader program. it also binds default
 * attributes inside the shaders and calls a routine which enable texturing
 * @param vertexShaderCode, fragmentShaderCode the source code for the vertex and fragment programs
 */
void LPShader::setUpShader(const GLchar *vertexshaderCode, const GLchar *fragmentShaderCode){
	// Load the vertex/fragment shaders
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexshaderCode);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
	// Cria o programa em que os shaders serao ligados
	program = glCreateProgram();
	if(program == 0)
		return;
    printf("Programa criado\n");
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

}
    
/**
* Binds attributes "position" and "textureCoordinates" to attributes in the vertex shader
*/
void LPShader::bindAttributes(const std::unordered_map<GLint, std::string> attributes_map){
    
    for (auto it = attributes_map.begin(); it != attributes_map.end(); it++) {
        glEnableVertexAttribArray(it->first);
        glBindAttribLocation(program, it->first, it->second.c_str());
    }
}

void LPShader::linkProgram(){
    // Link the program
    glLinkProgram(program);
    // Check the link status
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    //search for any error
    if(!linked)
    {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        std::cout << "Shader Link problem\n" << std::endl;
        if(infoLen > 1)
        {
            char* infoLog = new char[(sizeof(char) * infoLen)];
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            delete[] infoLog;
        }
        glDeleteProgram(program);
        return;
    }
}
    
/**
 * This method receives the address for a shader file, opens the file and returns the source code
 * @param filename The path to the shader file
 * @param shaderType A int which represents the type of the shader file
 * @return content The source code of the shader
 */
std::string LPShader::readShaderFile(const GLchar *filename, int shaderType)
{
    std::ifstream ifs(filename);
    if(ifs.fail()){
        std::cout << "Erro na leitura do arquivo de shader " << filename << std::endl;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();
    std::string content = buffer.str();
    
    return content;
}

    


/**
 * Some routines necessaries to use textures. It generates a texture and configures texture filters.
 */
void inline LPShader::enableTexture(){
	/*****Exemplo da textura**/
	glActiveTexture(GL_TEXTURE0);
	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// Generate a texture object
	glGenTextures(1, &textureId);
	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);
	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gvSamplerHandle = glGetAttribLocation(program, "s_texture");
	// Set the sampler texture unit to 0
	glUniform1i(gvSamplerHandle, 0);
	/***********************************************************************/
}

/**
 * This method creates, loads and compiles a new shader.
 * @param type The type of the shader to be loaded
 * @param shaderSrc The source code of the shader file
 * @return shader A handle to the compiled shader object
 */
GLuint LPShader::loadShader(GLenum type, const GLchar *shaderSrc) {
	GLuint shader;
	GLint compiled;
	// Create the shader object
	shader = glCreateShader(type);
	if(shader == 0)
		return 0;
	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// Compile the shader
	glCompileShader(shader);
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
		{
			char* infoLog = new char[(sizeof(char) * infoLen)];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			delete[] infoLog;
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

/**
 * Returns the value of "linked" variable for debug purposes.
 * @param linked A handle to the link status of the program
 */
GLint LPShader::getLinkStatus() {
	return linked;
}

/**
 * Returns shader program.
 * @retun program A handle to the linked program
 */
GLuint LPShader::getProgram() {
	return program;
}

} /* namespace LayerSceneGraph */
