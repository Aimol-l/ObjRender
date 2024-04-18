#version 460 core
out vec4 FragColor;

layout (binding=0) uniform sampler2D ourTexture;


in vec4 vertexColor; 
in vec3 norCoord;
in vec2 texCoord;

void main(){
    FragColor = texture(ourTexture, texCoord);
}