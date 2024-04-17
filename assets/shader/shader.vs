#version 460 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 NorCoord;


out vec4 vertexColor; 
out vec3 norCoord;
out vec2 texCoord;


uniform mat4x4 modelMat;
uniform mat4x4 viewMat;
uniform mat4x4 projectMat;

void main() {
    texCoord = TexCoord;
    norCoord = NorCoord;
    vertexColor = vec4(1.0, 1.0, 1.0, 1.0); // 把输出变量设置为暗红色
    gl_Position = projectMat*viewMat*modelMat*vec4(Pos,1.0f);
    // gl_Position=vec4(Pos,1.0);
}