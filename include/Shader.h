#pragma once
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include "glm/glm.hpp"

class Shader {
private:
    unsigned int program_id;
public:
    ~Shader(){glDeleteProgram(program_id);}
    Shader(){};
    void use();
    unsigned int get_id(){return program_id;};
    int create_shader(const std::string &vertex_path, const std::string &fragment_path);
    // 在这里添加其他有关设置uniform变量的方法
    void set_bool(const std::string &name, bool value) const ;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const ;
    void set_vec4(const std::string &name, float x,float y,float z,float w) const;
    void set_mat2(const std::string &name, const glm::mat2 &mat) const;
    void set_mat3(const std::string &name, const glm::mat3 &mat) const;
    void set_mat4(const std::string &name, const glm::mat4 &mat) const;
};

