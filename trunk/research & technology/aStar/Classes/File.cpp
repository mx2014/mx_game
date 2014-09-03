//
//  File.cpp
//  aStar
//
//  Created by Yawnsan on 14-8-26.
//
//

#include "File.h"
#include "Text.h"
cocos2d::Scene * File::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = File::create();
    scene -> addChild( layer );
    return scene;
}

bool File::init()
{
    if (!Layer::init()) {
        return false;
    }
    _text->_fun();
    num= 1;
//    _text->_num();
    return true;

}