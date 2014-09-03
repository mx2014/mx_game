#include "HelloWorldScene.h"
#include "mx/Mx.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
//    Mx::getInstance()->getFilePathAtVec("");
    Mx::getInstance()->createDialog(nullptr, this, Size(300, 300));
    auto snake = Armature::create("DotaSnake");
    snake->setPosition(300, 300);
    this->addChild(snake);
//    scheduleUpdate();
    
    auto p = Mx::getInstance()->getHttpParameter();
    p->addObject("ccc", "cc");
    p->addObject("1111", "2222");
    p->addObject("aaaa", "bb");
    Mx::getInstance()->send("acion.do", p, nullptr);
    
    srand(100);
    float t = CCRANDOM_0_1();
//    log("--%f---", t);
//    auto l = MLayer::createInstance("_test");
//    this->addChild(l);
    
    string a = FileUtils::getInstance()->fullPathForFilename("test2.zip");
    
    return true;
}
void HelloWorld::time(int time){
    
}
void HelloWorld::update(float delta){
    auto progress = Mx::getInstance()->loadingPictureProgress;
//    log("%i, %i", progress.finishNum, progress.pictureCountNum);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
    auto b = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("base2.png"));
    this->addChild(b);
    
    auto snake = Armature::create("DotaSnake");
//    auto snake = Sprite::create("s12.jpg");
    this->addChild(snake);
    
    auto scene = TestLayer::createScene();
    Director::getInstance()->replaceScene(scene);
}
