//
//  TestLayer.cpp
//  mx_libs_0.3
//
//  Created by Rayln on 14-9-1.
//
//

#include "TestLayer.h"

Scene * TestLayer::createScene(){
    auto scene = Scene::create();
    auto layer = TestLayer::create();
    layer->setLayerLoad("GameLayer");
//    auto layer = TestLayer::createInstance("_test");
    scene->addChild(layer);
    return scene;
}
bool TestLayer::init(){
    if (!MLayer::init()) {
        return false;
    }

    return true;
}

void TestLayer::progress(_Progress progress){
//    log("%i---TestLayer--%i",_progress.now, _progress.sum);
}

void TestLayer::renderer(){
    MLayer::renderer();
    auto s = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("s33.jpg"));
    s->setPosition(300, 300);
    this->addChild(s);
}

void TestLayer::onEnter(){
    MLayer::onEnter();
    auto s = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("s12.jpg"));
    s->setPosition(400, 300);
    this->addChild(s);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestLayer::menuCloseCallback, this));
//    closeItem->setPosition(Vec2(600, 200));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2(600, 200));
    this->addChild(menu);

}

void TestLayer::menuCloseCallback(Ref* pSender)
{

    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}