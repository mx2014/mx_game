//
//  Factory.h
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-31.
//
//

#ifndef __mx_libs_0_3__Factory__
#define __mx_libs_0_3__Factory__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocosGUI.h"

USING_NS_CC;

using namespace std;
using namespace cocostudio;

typedef function<void(int)> _FinishProgress;

class Factory : public Ref {
    
public:
    static Factory * factory;
    
public:
    static Factory * getInstance();
    
public:
    bool checkElement(std::vector<std::string> v, std::string elem);
    std::string getSuffix(std::string filename);
    
};

#endif /* defined(__mx_libs_0_3__Factory__) */
