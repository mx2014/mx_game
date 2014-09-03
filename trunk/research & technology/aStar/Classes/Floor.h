//
//  Floor.h
//  aStar
//
//  Created by Yawnsan on 14-8-21.
//
//

#ifndef __aStar__Floor__
#define __aStar__Floor__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

typedef enum _FloorState
{
    StateTrue,
    StateFalse
}FloorState;

class Floor : public cocos2d::LayerColor {
    
public:
    Floor();
    ~Floor(){}
    
    static Floor * create(const cocos2d::Color4B& color);
    bool initWithColor(const cocos2d::Color4B& color);
    static int at(int x, int y);
    int getF();
    bool init();
    void setString(std::string str);
    
    CREATE_FUNC(Floor);
private:
    CC_SYNTHESIZE(int, _x, X);
    CC_SYNTHESIZE(int, _y, Y);
    
    CC_SYNTHESIZE(int, _h, H);
    CC_SYNTHESIZE(int, _g, G);
    CC_SYNTHESIZE(FloorState, _foorState, FoorState);
    CC_SYNTHESIZE(Floor *, _lastFloor, LastFloor);
    CC_SYNTHESIZE(Label *, _label, Label);
};
#endif /* defined(__aStar__Floor__) */
