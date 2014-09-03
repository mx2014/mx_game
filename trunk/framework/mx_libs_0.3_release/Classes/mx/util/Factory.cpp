//
//  Factory.cpp
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-31.
//
//

#include "Factory.h"

Factory * Factory::factory = nullptr;

Factory * Factory::getInstance(){
    
    if (factory == nullptr) {
        factory = new Factory();
        factory->autorelease();
    }
    
    return factory;
}

bool Factory::checkElement(std::vector<std::string> v, std::string elem){
    bool t = false;
    for (std::string s : v) {
        if (s == elem) {
            t = true;
        }
    }
    return t;
}

std::string Factory::getSuffix(std::string f){
    int index = f.find(".");
    std::string s = f.substr(index + 1, f.size() - 1);
    transform(s.begin(), s.end(), s.begin(), (int (*)(int))tolower);
    return s;
}


