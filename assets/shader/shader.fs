#version 460 core

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos; // 光源位置
uniform vec3 viewPos; //观察位置，就是相机的位置
uniform vec3 lightColor; //光源颜色
uniform vec3 objectColor; //物体固有色


out vec4 FragColor;

void main(){
    // 环境光
    float ambient_ratio = 0.1;
    vec3 ambient = ambient_ratio * lightColor;

    // 镜面反射光
    float specular_ratio = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specular_ratio * spec * lightColor;

    // 漫反射光
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //合成结果
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0) * texture(texture_diffuse1, TexCoords);
}