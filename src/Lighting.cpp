#include "Lighting.h"


//********************************************************
Lighting::~Lighting(){
    delete m_light_model;
}
Lighting::Lighting(int type=0,const std::string &model_path){
    m_light_model->load_model(model_path);
}
