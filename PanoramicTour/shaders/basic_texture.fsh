#version 330
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texSampler;

void main() {
   outColor = texture(texSampler, Texcoord);
}