#version 330
in vec3 position;
in vec2 texcoord;
out vec2 Texcoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    Texcoord = texcoord;
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
}