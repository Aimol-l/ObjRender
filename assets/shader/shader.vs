#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aTangents;
layout (location = 4) in vec2 aBitangents;

out vec2 TexCoords;

uniform mat4x4 modelMat;
uniform mat4x4 viewMat;
uniform mat4x4 projectMat;

void main() {
    TexCoords = aTexCoords;  
    gl_Position = projectMat*viewMat*modelMat*vec4(aPos,1.0f);
}