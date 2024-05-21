#version 460 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;
struct Lighting {
    int type;       // {0:平行光, 1:点光源, 2:聚光灯}
    vec3 position;  //光源位置
    vec3 direction; //光源方向
    vec3 color;     //光源颜色
    vec3 ambient;   //环境光系数
    vec3 diffuse;   //漫反射系数
    vec3 specular;  //镜面反射系数
    float constant;
    float linear;
    float quadratic;
    float cut_off;
    float outer_cut_off;
};      

#define MAX_LIGHTS 20
// layout (location = 0 ) uniform vec3 = xxxx;
uniform Lighting lights[MAX_LIGHTS];
uniform int num_light;
uniform vec3 camera_pos;
uniform sampler2D texture_diffuse1;

vec3 ParallelLighting(Lighting light, vec3 normal, vec3 camera_direction) {
    // 衰减系数,平行光不衰减
    //float distance = length(light.position - FragPos);
    //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    // 环境光
    vec3 ambient_ = light.ambient * light.color * texture(texture_diffuse1, TexCoords).rgb;;
    //漫反射
    vec3 light_direct = normalize(light.direction);
    vec3 diffuse_ = max(dot(normal, light_direct), 0.0) * light.color * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
    // 镜面反射
    vec3 reflect_direct = reflect(normalize(light.direction), normal);  // 输入法线方向，光线方向，输出反射方向
    float spec = pow(max(dot(camera_direction, reflect_direct), 0.0), 24);
    vec3 specular_ = light.specular * spec * light.color * texture(texture_diffuse1, TexCoords).rgb;
    return (ambient_ + diffuse_ + specular_);
}
vec3 PointLighting(Lighting light, vec3 normal, vec3 camera_direction) {
    // 衰减系数
    float distance = length(light.position - FragPos);
    float attenuation = 3.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    // 环境光
    vec3 ambient_ = light.ambient * light.color * texture(texture_diffuse1, TexCoords).rgb;
    // 漫反射 
    vec3 light_direct = normalize(light.position - FragPos);
    vec3 diffuse_ = max(dot(normal, light_direct), 0.0) * light.color * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
    // 镜面反射
    vec3 reflect_direct = reflect(light_direct, normal);  // 输入法线方向，光线方向，输出反射方向
    float spec = pow(max(dot(camera_direction, reflect_direct), 0.0), 32);
    vec3 specular_ = light.specular * spec * light.color * texture(texture_diffuse1, TexCoords).rgb;
    //**********
    return (ambient_ + attenuation*diffuse_ + attenuation*specular_);
}
vec3 SpotLighting(Lighting light, vec3 normal, vec3 camera_direction) {
    // 衰减系数
    float distance = length(light.position - FragPos);
    float attenuation = 3.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    // 环境光
    vec3 ambient_ = light.ambient * light.color * texture(texture_diffuse1, TexCoords).rgb;
    // 漫反射 
    vec3 light_direct = normalize(light.position - FragPos);
    float theta = dot(light_direct, normalize(-light.direction));
    vec3 diffuse_ = vec3(0.0);
    vec3 specular_ = vec3(0.0);
    float lightSoft = clamp((theta - light.outer_cut_off) / (light.cut_off - light.outer_cut_off), 0.0f, 1.0f);
    if(cos(light.cut_off)>theta&& theta > cos(light.outer_cut_off)){
        //柔光圈
        diffuse_ = lightSoft*max(dot(normal, light_direct), 0.0) * light.color * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
        vec3 reflect_direct = reflect(camera_direction, normal);  // 输入法线方向，光线方向，输出反射方向
        float spec = pow(max(dot(camera_direction, reflect_direct), 0.0), 32);
        specular_ = lightSoft*light.specular * spec * light.color * texture(texture_diffuse1, TexCoords).rgb;
    }
    if(theta > cos(light.cut_off)){
        diffuse_ = max(dot(normal, light_direct), 0.0) * light.color * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
        // 镜面反射
        vec3 reflect_direct = reflect(camera_direction, normal);  // 输入法线方向，光线方向，输出反射方向
        float spec = pow(max(dot(camera_direction, reflect_direct), 0.0), 32);
        specular_ = light.specular * spec * light.color * texture(texture_diffuse1, TexCoords).rgb;
    }
    return (ambient_ + attenuation*diffuse_ + attenuation*specular_);
}
vec3 CalculateLighting(Lighting light, vec3 normal, vec3 camera_direction) {
    if (light.type == 0) {
       return ParallelLighting(light, normal, camera_direction);
    }
    if (light.type == 1) {
       return PointLighting(light, normal, camera_direction);
    }
    if (light.type == 2) {
       return SpotLighting(light, normal, camera_direction);
    }
}
void main() {
    vec3 norm = normalize(Normal); // 片段单位法向量
    vec3 camera_direction = normalize(camera_pos - FragPos); //相机观察的方向
    vec3 lighting = vec3(0.0);
    for (int i = 0; i < num_light; i++) {
        lighting += CalculateLighting(lights[i], norm, camera_direction);
    }
    // vec3 lighting = PointLighting(lights[0], norm, camera_direction);
    FragColor = vec4(lighting, 1.0);
}
