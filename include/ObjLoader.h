 #pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include "glm/glm.hpp"

struct Face{
    std::array<uint,3> v;
    std::array<uint,3> vt;
    std::array<uint,3> vn;
};
class ObjLoader{
private:
    std::vector<Face> m_faces;
    std::vector<glm::vec3> m_v_s;
    std::vector<glm::vec2> m_vt_s;
    std::vector<glm::vec3> m_vn_s;
public:
    ObjLoader(){
        std::cout<<"ObjLoader........"<<std::endl;
    };
    ~ObjLoader(){};
    void show_info();
    void load_obj(const std::string &path);

    std::vector<Face> get_faces();
    std::vector<glm::vec3> get_vertexes();
    std::vector<glm::vec2> get_ver_texture();
    std::vector<glm::vec3> get_ver_normals();

    inline size_t get_num_faces() { return m_faces.size();};
    inline size_t get_num_v(){return m_v_s.size();};
    inline size_t get_num_vn(){return m_vn_s.size();};
    inline size_t get_num_vt(){return m_vt_s.size();};


};

