#version 330
in vec3 position;
in vec2 texcoord;
out vec2 Texcoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
void main() {
    Texcoord = texcoord;
    //gl_Position = projectionMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
    //gl_Position = vec4(position, 1.0);
}