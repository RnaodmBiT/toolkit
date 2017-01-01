#pragma once
#include "../includes.hpp"

struct projectileType {
    std::string name;
    float mass;
    float reloadtime;
    bool tracking;
    bool connected;
    bool sticky;
    Vec4f color;
};

const std::vector<projectileType> projectileTypes { 
    projectileType{"normal",1,0.2f,false,false,false,Vec4f{1,1,1,1}},
    projectileType{"missle",1,1,true,false,false,Vec4f{1,0.5f,0,1}},
    projectileType{"cannon",10,1,false,false,false,Vec4f{0.5f,0.5f,0.5f,1}}
};
