#version 460 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

#define MAX_LIGHTS 100
uniform Lighting lights[MAX_LIGHTS];
uniform int num_light;

struct Lighting {
    int type;       // {0:平行光, 1:点光源, 2:聚光灯}
    vec3 position;  //光源位置
    vec3 direction; //光源方向
    vec3 color;     //光源颜色

    vec3 ambient;   //环境光系数
    vec3 diffuse;   //漫反射系数
    vec3 specular;  //镜面反射系数
};      

vec3 CalculateLighting(Lighting light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 result = vec3(0.0);
    if (light.type == 0) {
        result += ParallelLighting(light, normal, fragPos, viewDir);
    } else if (light.type == 1) {
        result += PointLighting(light, normal, fragPos, viewDir);
    } else if (light.type == 2) {
        result += SpotLighting(light, normal, fragPos, viewDir);
    }
    return result;
}

vec3 ParallelLighting(Lighting light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 diff = max(dot(normal, lightDir), 0.0) * light.diffuse * vec3(texture(texture_diffuse1, TexCoords));
    vec3 spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess) * light.specular * vec3(texture(texture_diffuse1, TexCoords));
    return light.ambient + diff + spec;
}

vec3 PointLighting(Lighting light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 diff = max(dot(normal, lightDir), 0.0) * light.diffuse * vec3(texture(texture_diffuse1, TexCoords));
    vec3 spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess) * light.specular * vec3(texture(texture_diffuse1, TexCoords));
    return (light.ambient + diff + spec) * attenuation;
}

vec3 SpotLighting(Lighting light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 diff = max(dot(normal, lightDir), 0.0) * light.diffuse * vec3(texture(texture_diffuse1, TexCoords));
    vec3 spec = pow(max(dot(viewDir, reflect(-lightDir, normal)), 0.0), material.shininess) * light.specular * vec3(texture(texture_diffuse1, TexCoords));
    return (light.ambient + diff + spec) * attenuation * intensity;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lighting = vec3(0.0);
    for (int i = 0; i < numLights; ++i) {
        lighting += CalculateLighting(lights[i], norm, FragPos, viewDir);
    }
    FragColor = vec4(lighting, 1.0);
}
