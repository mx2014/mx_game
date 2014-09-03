//
//  Main.h
//  aStar
//
//  Created by Yawnsan on 14-8-21.
//
//

#ifndef __aStar__Main__
#define __aStar__Main__

#include <iostream>
#include "cocos2d.h"
#include "Floor.h"

USING_NS_CC;

class Main : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC( Main );
    
private:

    void createGround();
    void createRobot();
//    void robotGo_1();
//    void openAdd(Floor * FLOOR,Floor * LAST);
    
public:
    CC_SYNTHESIZE(cocos2d::Vector< Floor * >, ground, Ground);
    CC_SYNTHESIZE(cocos2d::Vector< Floor * >, open, Open);
    CC_SYNTHESIZE(cocos2d::Vector< Floor * >, close, Close);
    CC_SYNTHESIZE(Floor *, end, End);
    CC_SYNTHESIZE(Floor *, begin, Begin);
    CC_SYNTHESIZE(cocos2d::Sprite *, sprite, _SPRITE);
    CC_SYNTHESIZE(int, j, J);
    CC_SYNTHESIZE(int, o, O);
    CC_SYNTHESIZE(Floor *, index, Index);
    CC_SYNTHESIZE(cocos2d::Vector< Floor * >, move, Move);
    
    
public:
    CC_SYNTHESIZE(cocos2d::Vector<__Array *>, path, Path);
public:
    
    void run(Floor* floor, int index);
    void handleFloor(Floor* floor, int index);
    void createOtherFloor(Floor* floor, int direct1[], cocos2d::Vector<Floor *> * otherFloor);
    void runTime(float t);
    long getCurrentTime();
    
    
    
    
    
    
    
//public:
//    void handleFloor( Floor *_floor, int x, int y );
    void back();
//    void update(float delta);
};

#endif /* defined(__aStar__Main__) */
