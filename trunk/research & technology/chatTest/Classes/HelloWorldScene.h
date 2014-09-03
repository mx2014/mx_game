#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "mx/Mx.h"
#include "UserData.h"
#include "ChatWindow.h"
class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(HelloWorld);
    
public:
    
    void click(Ref* ref,Widget::TouchEventType type);
    
    CC_SYNTHESIZE(Size, winSize, WinSize);
    
    CC_SYNTHESIZE(int, showNum, ShowNum);
    
    CC_SYNTHESIZE(ChatWindow *, chatWindow, chatWindow_1);
    
    
public:
    void showChatUi(Ref* ref,Widget::TouchEventType type);

};

#endif // __HELLOWORLD_SCENE_H__
