#include "ObjLoader.h"
#include "strtool.h"
#include "Log.h"

void ObjLoader::show_info(){
    Log::info("vertex number = "+ std::to_string(m_v_s.size()));
    Log::info("vertexTexture coor number = "+ std::to_string(m_vt_s.size()));
    Log::info("vertexNormal number = "+std::to_string(m_vn_s.size()));
    Log::info("trangle number  = "+ std::to_string(m_faces.size()));
}
void ObjLoader::load_obj(const std::string &path){
    Log::info("load_obj.....");
    std::ifstream inputFile(path);
    if(!inputFile.is_open()) {
        Log::error("failed  to load obj file:"+path);
        return;
    }
    std::string line;
    while(std::getline(inputFile, line)) {
        if(line.substr(0,2) == "v "){
            std::istringstream substr(line.substr(2));
            glm::vec3 v;
            substr >>v.x>>v.y>>v.z;
            m_v_s.push_back(v);
            std::cout<<std::format("v=[{},{},{}]",v.x,v.y,v.z)<<std::endl;
        }
        if(line.substr(0,2) == "vt"){
            std::istringstream substr(line.substr(2));
            glm::vec2 vt;
            substr>>vt.x>>vt.y;
            m_vt_s.push_back(vt);
            std::cout<<std::format("vt=[{},{}]",vt.x,vt.y)<<std::endl;
        }
        if(line.substr(0,2) == "vn"){
            std::istringstream substr(line.substr(2));
            glm::vec3 vn;
            substr >>vn.x>>vn.y>>vn.z;
            m_vn_s.push_back(vn);
        }
        if(line.substr(0,2) == "f "){
            auto results = str::split(line.substr(2));
            results.erase(std::remove(results.begin(), results.end(), ""), results.end());
            results.erase(std::remove(results.begin(), results.end(), "\r"), results.end());
            if(results.size() == 3){
                Face f;
                for(int i = 0;i<results.size();i++){
                    auto res = str::split(results[i],'/');
                    if(res[0] != "" && res.size() >=1) f.v.at(i) =  std::stoul(res[0])-1;
                    if(res[1] != "" && res.size() >=2) f.vt.at(i) =  std::stoul(res[1])-1;
                    if(res[2] != "" && res.size() >=3) f.vn.at(i) =  std::stoul(res[2])-1;
                }
                m_faces.push_back(f);
            }else if(results.size() == 4){
                Face f1,f2;
                const static int arr1[] = {0,1,2};
                for(int i = 0;i < results.size()-1;i++){
                    auto res = str::split(results[i],'/');
                    if(res[0] != "" && res.size() >=1) f1.v.at(i) =  std::stoul(res[0])-1;
                    if(res[1] != "" && res.size() >=2) f1.vt.at(i) =  std::stoul(res[1])-1;
                    if(res[2] != "" && res.size() >=3) f1.vn.at(i) =  std::stoul(res[2])-1;
                }
                const static int arr2[] = {0,2,3};
                for(int i = 0;i < results.size()-1;i++){
                    auto res = str::split(results[arr2[i]],'/');
                    if(res[0] != "" && res.size() >=1) f2.v.at(i) =  std::stoul(res[0])-1;
                    if(res[1] != "" && res.size() >=2) f2.vt.at(i) =  std::stoul(res[1])-1;
                    if(res[2] != "" && res.size() >=3) f2.vn.at(i) =  std::stoul(res[2])-1;
                }
                m_faces.push_back(f1);
                m_faces.push_back(f2);
            }
        }
    }
    inputFile.close();
    this->show_info();
    Log::info("load_obj.....done!!");
}
std::vector<Face> ObjLoader::get_faces(){
    return m_faces;
}
std::vector<glm::vec3> ObjLoader::get_vertexes(){
    return m_v_s;
}

std::vector<glm::vec3> ObjLoader::get_ver_normals(){
    return m_vn_s;
}
std::vector<glm::vec2> ObjLoader::get_ver_texture(){
    return std::move(m_vt_s);
}
