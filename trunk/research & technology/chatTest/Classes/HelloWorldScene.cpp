#include "HelloWorldScene.h"
//#include "TextInputTest.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    winSize = Director::getInstance()->getWinSize();
    
    auto button = Button::create("button.png",
                                 "button.png");
    button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::click, this));
    button->setPosition(Vec2(winSize.width - button->getContentSize().width/2 - 30,
                             button->getContentSize().height + 100));
    button->setTitleText("click");
    button->setTitleFontSize(23);
    button->setScale(1.3);
    this->addChild(button, 10);


    auto button1 = Button::create("button.png",
                                 "button.png");
    button1->addTouchEventListener(CC_CALLBACK_2(HelloWorld::showChatUi, this));
    button1->setPosition(Vec2(winSize.width - button1->getContentSize().width/2 - 30 ,
                             winSize.height - button1->getContentSize().height - 100));
    button1->setTitleText("show");
    button1->setTitleFontSize(23);
    button1->setScale(1.3);
    this->addChild(button1, 10);

    showNum =0;
    chatWindow = ChatWindow::create();
    this -> addChild(chatWindow);
    chatWindow -> setPosition(Vec2(-751, (winSize.height-chatWindow->getContentSize().height)/2));

    
    return true;
}




void HelloWorld::showChatUi(Ref* ref,Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        MoveBy *moveBy ;
        if(showNum %2 == 0)
        {
            moveBy = MoveBy::create(.3, Vec2(751, 0));
        }else
        {
            moveBy = MoveBy::create(.3, Vec2(-751, 0));
            static_cast<TextFieldTTF*>(chatWindow -> getTextField()->getVirtualRenderer())->detachWithIME();
        }
        chatWindow->runAction(moveBy);
        

        showNum++;
    }
    
}




void HelloWorld::click(Ref* ref,Widget::TouchEventType type){
    
    if(type == Widget::TouchEventType::ENDED)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        return;
        #endif
        Director::getInstance()->end();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
        #endif
    }
}


