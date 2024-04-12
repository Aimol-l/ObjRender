#version 460 core
out vec4 FragColor;

uniform sampler2D ourTexture;

in vec4 vertexColor; 
in vec3 norCoord;
in vec2 texCoord;

void main(){
    // FragColor = vertexColor;
    FragColor = texture(ourTexture, texCoord);
}