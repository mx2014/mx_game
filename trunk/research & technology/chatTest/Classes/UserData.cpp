//
//  UserData.cpp
//  companyChatTest
//
//  Created by Yawnsan on 14-8-15.
//
//

#include "UserData.h"

Layout* UserData::createLayout()
{
    auto layout = Layout::create();
    return layout;
    
}

bool UserData::init()
{
    if (!Layout::init()) {
        return false;
    }
    this ->setTouchEnabled(true);
    this -> createLayoutBg();


    return true;
}

void UserData::createLayoutBg()
{
    this -> setContentSize(Size(600,434));
    this -> setBackGroundImage("toast_b.png");
    this -> setBackGroundImageScale9Enabled(true);
    layoutWin = Layout::create();
    layoutWin->setContentSize(Size(300, 400));
    layoutWin->setAnchorPoint(Vec2(.5,.5));
    layoutWin->setPosition(Vec2(this->getContentSize().width/2+110,this->getContentSize().height/2));
    layoutWin->setBackGroundImage("toast_b.png");
    layoutWin-> setBackGroundImageScale9Enabled(true);
    this -> addChild(layoutWin);

}

void UserData::createLayoutDate()
{
    Text* label = Text::create(StringUtils::format("Name: %s",userName.c_str()), "fonts/Marker Felt.ttf", 30);
    label->setAnchorPoint(Vec2(.5,.5));
    label->cocos2d::Node::setPosition(layoutWin->getContentSize().width/2,layoutWin->getContentSize().height-30);
    layoutWin->addChild(label);
    
    Text* label_Data = Text::create(StringUtils::format("Data: %s",userData1.c_str()), "fonts/Marker Felt.ttf", 30);
    label_Data->setAnchorPoint(Vec2(0,1));
    label_Data->ignoreContentAdaptWithSize(false);
    label_Data->setContentSize(Size(250,100));
    label_Data->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    label_Data->setTextVerticalAlignment(cocos2d::TextVAlignment::TOP);
    label_Data->cocos2d::Node::setPosition(20,layoutWin->getContentSize().height-60);
    layoutWin->addChild(label_Data);

}

void UserData::createLayoutButton()
{
    auto closeButton = Button::create("CloseNormal.png");
    closeButton->addTouchEventListener(CC_CALLBACK_2(UserData::buttonChange, this));
    closeButton->setAnchorPoint(Vec2::ZERO);
    closeButton->setScale(1.5);
    closeButton->setPosition(Vec2(layoutWin->getContentSize().width - closeButton->getContentSize().width,layoutWin ->getContentSize().height - closeButton->getContentSize().height));
    layoutWin ->addChild(closeButton, 10);
    closeButton->setTag(101);
    
    auto aloneChatButton = Button::create("button.png");
    aloneChatButton->addTouchEventListener(CC_CALLBACK_2(UserData::buttonChange,this));
    layoutWin ->addChild(aloneChatButton, 10);
    aloneChatButton->setPosition(Vec2(80, 50));
    aloneChatButton->setTag(102);
    aloneChatButton->setTitleText("私聊");
    aloneChatButton->setTitleFontSize(23);
}

void UserData::onEnter()
{
    Layout::onEnter();
    this->createLayoutButton();
    this->createLayoutDate();
}

void UserData::buttonChange(Ref* ref,Widget::TouchEventType type)
{
    if (static_cast<Button *>(ref)->getTag() == 101) {
        this -> removeFromParentAndCleanup(true);
    }else if (static_cast<Button *>(ref)->getTag() == 102) {
        textField->setText(StringUtils::format("/R %s : ",userName.c_str()));
        this -> removeFromParentAndCleanup(true);
    }
    
}