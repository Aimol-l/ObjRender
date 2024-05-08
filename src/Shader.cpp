#include "Shader.h"
#include "Log.h"


//负责着色器的加载、编译和链接。这个类可以包含着色器程序的ID、着色器的源代码等信息。
int ren::Shader::create_shader(const std::string &vertex_path, const std::string &fragment_path) {
    // Log::info("create_shader....");
    std::string vertex_code,fragment_code;
    std::fstream v_shader_file,f_shader_file;
    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    //读取glsl文件
    try{
        v_shader_file.open(vertex_path); //打开glsl文件
        f_shader_file.open(fragment_path); //打开glsl文件
        std::stringstream v_shader_stream,f_shader_stream;
        v_shader_stream<<v_shader_file.rdbuf();
        f_shader_stream<<f_shader_file.rdbuf();
        //关闭文件处理程序
        v_shader_file.close();
        f_shader_file.close();
        //转为字符串
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
    }catch(std::ifstream::failure &e){
        std::string err ="Read glsl failed,"+ *e.what();
        Log::error(err);
        std::cerr << "Read glsl failed," << e.what() << std::endl;
        return 0;
    }   
    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();
    //*********************************开始编译shader
    // 编译顶点着色器
    GLuint vertex_hader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_hader, 1, &v_shader_code, nullptr);
    glCompileShader(vertex_hader);
    // 检查顶点着色器编译是否成功
    GLint success;
    glGetShaderiv(vertex_hader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertex_hader, 512, nullptr, infoLog);
        std::string err ="Vertex shader compilation failed:\n"+ *infoLog;
        Log::error(err);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }
    // 编译片段着色器
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_shader_code, nullptr);
    glCompileShader(fragment_shader);
    // 检查片段着色器编译是否成功
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
        std::string err ="Fragment shader compilation failed:\n"+ *infoLog;
        Log::error(err);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }
    //*****************************编译shader完成
    // 链接着色器程序
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_hader);
    glAttachShader(program_id, fragment_shader);
    glLinkProgram(program_id);
    // 检查着色器程序链接是否成功
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program_id, 512, nullptr, infoLog);
        std::string err = "Shader program linking failed:" + *infoLog;
        Log::error(err);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return 0;
    }
    // 删除着色器对象，它们已经链接到着色器程序中了
    glDeleteShader(vertex_hader);
    glDeleteShader(fragment_shader);
    // Log::info("create_shader....done!");

    // glUseProgram(this->program_id);
    return 1;
}
void ren::Shader::use(){
     glUseProgram(this->program_id);
}
void ren::Shader::set_bool(const std::string &name, bool value) const{
     glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), value ? 1 : 0);
}

void ren::Shader::set_int(const std::string &name, int value) const{
     glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void ren::Shader::set_float(const std::string &name, float value) const{
     glUniform1f(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void ren::Shader::set_vec4(const std::string &name, float x, float y, float z, float w) const{
     glUniform4f(glGetUniformLocation(this->program_id,name.c_str()),x,y,z,w);
}

void ren::Shader::set_mat2(const std::string &name, const glm::mat2 &mat) const{
     glUniformMatrix4fv(glGetUniformLocation(this->program_id,name.c_str()),1,GL_FALSE,&mat[0][0]);
}

void ren::Shader::set_mat3(const std::string &name, const glm::mat3 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(this->program_id,name.c_str()),1,GL_FALSE,&mat[0][0]);
}

void ren::Shader::set_mat4(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(this->program_id,name.c_str()),1,GL_FALSE,&mat[0][0]);
}
