//
//  Text.h
//  aStar
//
//  Created by Yawnsan on 14-8-26.
//
//

#ifndef __aStar__Text__
#define __aStar__Text__

#include <iostream>
#include "cocos2d.h"
#include "File.h"


class Text : public cocos2d::Node{
    
    
public:
    
    CC_SYNTHESIZE(int, j, J);
    void _fun()
    {
        cocos2d::log("hhhhhhhhhh");
        
    }
    void _num()
    {
        File * f;
        cocos2d::log("%i",f->getNum());
    }
};

#endif /* defined(__aStar__Text__) */
