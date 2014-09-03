//
//  File.h
//  aStar
//
//  Created by Yawnsan on 14-8-26.
//
//

#ifndef __aStar__File__
#define __aStar__File__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
//#include "Text.h"

class Text;
class File : public cocos2d::Layer{
    
    
public:
    CC_SYNTHESIZE(Text *, _text, _Text);
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(File);
    CC_SYNTHESIZE(int ,num , Num);
};



#endif /* defined(__aStar__File__) */
