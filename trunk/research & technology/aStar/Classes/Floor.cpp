//
//  Floor.cpp
//  aStar
//
//  Created by Yawnsan on 14-8-21.
//
//

#include "Floor.h"

Floor::Floor()
{
    _x = 0;
    _y = 0;
    
    _h = -1;
    _g = -1;
    
    _lastFloor = NULL;
}

int Floor::at(int x, int y)
{
    return x + 48 * y;
}

Floor *Floor::create(const cocos2d::Color4B &color)
{
    Floor *_floor = Floor::create();
    if ( _floor && _floor -> initWithColor( color ) )
    {
//        _floor -> autorelease();
        
        
        return _floor;
    }
    
    delete _floor;
    _floor = NULL;
    return NULL;
}

bool Floor::init(){
    if (!LayerColor::init()) {
        return false;
    }
//    _label =  Label::create("create","Marker Felt",30);;
    _label = Label::create();


    _label->setPosition(Vec2(10, 10));
    this->addChild(_label, 100);
    return true;
}

void Floor::setString(std::string str){
    _label->setString(str.c_str());
}

bool Floor::initWithColor(const cocos2d::Color4B &color)
{
    if ( LayerColor::initWithColor(color, 20, 20) )
    {
        return true;
    }
    
    return false;
}

int Floor::getF()
{
    return _h + _g;
}
