//
//  Parameter.h
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-30.
//
//

#ifndef __mx_libs_0_3__Parameter__
#define __mx_libs_0_3__Parameter__

#include <iostream>
#include "cocos2d.h"
#include "../util/MD5.h"

USING_NS_CC;

class Parameter : public Ref {
    
public:
    static Parameter* create();
    CC_SYNTHESIZE(Vector<__Dictionary*>, params, Params);

public:
    void addObject(std::string key, std::string value);
    std::string toString();
};

#endif /* defined(__mx_libs_0_3__Parameter__) */
