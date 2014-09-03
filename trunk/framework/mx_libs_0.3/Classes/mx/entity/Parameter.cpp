//
//  Parameter.cpp
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-30.
//
//

#include "Parameter.h"

Parameter* Parameter::create(){
    Parameter *request = new Parameter();
    request->autorelease();
    return request;
}

void Parameter::addObject(std::string key, std::string value){
    auto dic = __Dictionary::create();
    dic->setObject(__String::create(value), key);
    params.pushBack(dic);
}

std::string Parameter::toString(){
    std::string paramStr = "";
    sort(params.begin(), params.end(), [](__Dictionary* req1, __Dictionary* req2){
        auto str1 = static_cast<__String*>(req1->allKeys()->getObjectAtIndex(0)) ;
        auto str2 = static_cast<__String*>(req2->allKeys()->getObjectAtIndex(0)) ;
        return strcmp(str1->getCString(), str2->getCString()) < 0 ? true : false;;
    });
    
    for (__Dictionary* request : params) {
        auto key = static_cast<__String*>(request->allKeys()->getObjectAtIndex(0)) ;
        auto value = static_cast<__String*>(request->objectForKey(key->getCString()));
        paramStr = paramStr + key->getCString() + "=" + value->getCString() + "&";
    }
    paramStr = paramStr.substr(0, paramStr.length() - 1);
    paramStr = paramStr + "&" + "key="+ md5(paramStr);

    return paramStr;
}