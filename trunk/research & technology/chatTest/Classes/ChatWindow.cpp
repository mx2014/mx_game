//
//  ChatWindow.cpp
//  companyChatTest
//
//  Created by Yawnsan on 14-8-15.
//
//

#include "ChatWindow.h"


Layout* ChatWindow::createLayout()
{
    auto layout = Layout::create();
    return layout;
    
}

bool ChatWindow::init()
{
    if (!Layout::init()) {
        return false;
    }
    winSize = Director::getInstance()->getWinSize();
    this -> createChatUi();
    
    string aa[50][2] = {{"张三","你好个简单的."},{"李四","一个简单的二分查找字符串数组算法实现程序程序程序."},{"王五","一个简单的二分查找字符串数."},{"小明","明天又可以出去了,好开心啊."},{"小强","好无聊."},{"小王","ToT."}};
    string jsonStr = "{\"talk\":[{\"name\":\"张三\",\"content\":\"你好简单\"},{\"name\":\"李四\",\"content\":\"一个简单的二分查找字符串数组算法实现程序程序程序.\"},{\"name\":\"王五\",\"content\":\"一个简单的二分查找字符串数.\"}]}";
    int idx   = 0;
    this -> insertData(jsonStr,idx);

    
    return true;
}

void ChatWindow::createChatUi()
{
    this -> createChatBackground();
    this -> createChatButton();
    this -> createChatPageView();
    this -> createChatListView();
    this -> createTextField();
}

void ChatWindow::createChatBackground()
{
    bg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("chatBackground.png"));
    this -> addChild(bg);
    bg -> setAnchorPoint(Vec2::ZERO);
    this -> setContentSize(bg->getContentSize());
}

void ChatWindow::createChatButton()
{
    //创建世界 地图 私聊 3个按钮
    string str[] = {"世界","地图","私聊"};
    for (int i = 0; i < 3; i++)
    {
        
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        auto button = Button::create("animationbuttonpressed.png",
                                     "animationbuttonnormal.png");
        button->addTouchEventListener(CC_CALLBACK_2(ChatWindow::buttonChange, this));
        button->setAnchorPoint(Vec2::ZERO);
        button->setScale(1.5);
        button->setPosition(Vec2(bg->getContentSize().width - button->getContentSize().width*1.5 - 10 ,bg->getContentSize().height - button->getContentSize().height - 60 - i*100));
        bg->addChild(button, 10);
        button->setTitleText(str[i]);
        button->setTitleFontSize(25);
        button->setTag(1001+i);
    }
    
    
    //创建发送按钮
    submitButton = Button::create("stagepointe.png");
    submitButton->addTouchEventListener(CC_CALLBACK_2(ChatWindow::buttonChange, this));
    submitButton->setAnchorPoint(Vec2::ZERO);
    submitButton->setScale(1.5);
    submitButton->setPosition(Vec2(bg->getContentSize().width - submitButton->getContentSize().width*1.5 - 30 ,-10));
    bg->addChild(submitButton, 10);
    submitButton->setTag(1004);
}

void ChatWindow::createChatPageView()
{
    //创建容器PageView层
    pageView = NewPageView::create();


    pageView->setContentSize(Size(600.0f, 434.0f));
    bg->addChild(pageView);
    pageView->setAnchorPoint(Vec2(0,1));
    pageView->setPosition(Vec2(0,bg->getContentSize().height - 12));

}

void ChatWindow::createChatListView()
{
    //创建listView现实层
    for (int i = 0; i < 3; i++)
    {
        
        ListView* listView = ListView::create();
        //设置滚动方向
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("toast_b.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(600.0f, 350.0f));
        listView->addEventListener(CC_CALLBACK_2(ChatWindow::listViewEvent, this));
        //设置默认 到低点
        listView->setGravity(cocos2d::ui::ListView::Gravity::BOTTOM);
        pageView->insertPage(listView,i);
        
    }
}

//点击 Layout 按钮时实现的功能  (输入框会跟键盘一起谈起);
void ChatWindow::listViewEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            
            auto userData = UserData::create();
            userData ->setAnchorPoint(Vec2::ZERO);
            string _userName = StringUtils::format("%s",static_cast<Button *>( static_cast<Layout *>( listView->getItem(listView->getCurSelectedIndex()))->getChildByTag(10))->getTitleText().c_str());
            userData ->setUserName(_userName);
            
            string _userData = StringUtils::format("%s",static_cast<Text *>( static_cast<Layout *>( listView->getItem(listView->getCurSelectedIndex()))->getChildByTag(11))->getString().c_str());
            
            userData ->setUserData1(_userData);
            bg -> addChild(userData,20);
            userData->setPosition(Vec2(0, 98));
            
            userData -> setTextField(textField);
            
            //发送至服务器代码
            
            break;
        }
        default:
            break;
    }
    
}


void ChatWindow::createTextField()
{
    
    textField = TextField::create("input words here","",35);
    textField->setAnchorPoint(Vec2(0, 0));
    textField->setPosition(Vec2(20,10));
    textField->addEventListener(CC_CALLBACK_2(ChatWindow::textFieldEvent, this));
    textField->setMaxLengthEnabled(true);
    textField->setMaxLength(30);
    textField->ignoreContentAdaptWithSize(false);
    textField->setSize(Size(530, 80));
    textField->setTextHorizontalAlignment(TextHAlignment::LEFT);
    textField->setTextVerticalAlignment(TextVAlignment::BOTTOM);
    
    bg->addChild(textField,1);
    textFieldBg = Sprite::create("toast_b.png");
    textFieldBg->setAnchorPoint(Vec2::ZERO);
    textFieldBg->setPosition(Vec2(0, 1));
    textFieldBg->setScale(1.96, 1.1);
    bg->addChild(textFieldBg);
    
    
}

void ChatWindow::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    switch (type)
    {
        case TextField::EventType::ATTACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            textFieldBg ->runAction(MoveBy::create(0.225f,
                                                   Vec2(0,winSize.height/2-120)));
            textField   ->runAction(MoveBy::create(0.225f,
                                                   Vec2(0,winSize.height/2-120)));
            submitButton->runAction(MoveBy::create(0.225f,
                                                   Vec2(0,winSize.height/2-120)));
        }
            break;
            
        case TextField::EventType::DETACH_WITH_IME:
        {
            TextField* textField = dynamic_cast<TextField*>(pSender);
            textFieldBg     ->runAction(MoveBy::create(0.175f, Vec2(0,-(winSize.height/2-120))));
            textField       ->runAction(MoveBy::create(0.175f, Vec2(0,-(winSize.height/2-120))));
            submitButton    ->runAction(MoveBy::create(0.175f, Vec2(0,-(winSize.height/2-120))));
            
        }
            break;
            
        case TextField::EventType::INSERT_TEXT:
            
            break;
            
        case TextField::EventType::DELETE_BACKWARD:
            
            break;
            
        default:
            
            break;
    }
}

void ChatWindow::buttonChange(Ref* ref,Widget::TouchEventType type){
    auto button = static_cast<Button *>(ref);
    switch (button -> getTag()) {
        case 1001:
            pageView->scrollToPage(0);
            break;
            
        case 1002:
            pageView->scrollToPage(1);
            break;
            
        case 1003:
            pageView->scrollToPage(2);
            break;
            
        default:
            static_cast<TextFieldTTF*>(textField->getVirtualRenderer())->detachWithIME();
            textField->setText("");
            break;
    }
}

void ChatWindow::insertData(const string text,int &idx)
{
    
    rapidjson::Document json;
    json.Parse<0>(text.c_str());
    
    rapidjson::Value& talk = json["talk"];
    for (int i = 0; i < talk.Size(); i++) {
        
        log("----%s, %s---", talk[i]["name"].GetString(), talk[i]["content"].GetString());
        Button* custom_button = Button::create("toast_b.png");
        custom_button->setName("Title Button");
        custom_button->setScale9Enabled(true);
        custom_button->setSize(Size(306,87));
        custom_button->setScale(.7, .8);
        custom_button->setTitleText(talk[i]["name"].GetString());
        custom_button->setTitleFontSize(35);
        custom_button->setAnchorPoint(Vec2(0, 1));
        
        Layout *custom_item = Layout::create();
        custom_item->setSize(custom_button->getContentSize());
        custom_item->addChild(custom_button);
        custom_button->setTag(10);
        
        Text* label = Text::create(talk[i]["content"].GetString(),"", 30);
        label->setAnchorPoint(Vec2(0,1));
        label->ignoreContentAdaptWithSize(false);
        label->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
        label->setTextVerticalAlignment(cocos2d::TextVAlignment::TOP);
        label->setTag(11);
        custom_item->addChild(label);
        string data = talk[i]["content"].GetString();
        if (data.size()>44){
            label->setContentSize(Size(330,125));
            custom_item->setContentSize(Size(350,125));
        }else if (data.size()>22){
            label->setContentSize(Size(330,90));
            custom_item->setContentSize(Size(350,100));
        }else{
            label->setContentSize(Size(250,35));
            custom_item->setContentSize(Size(350,80));
        }
        custom_button->setPosition(Vec2(20, custom_item->getContentSize().height -20));
        label->cocos2d::Node::setPosition(250,custom_item->getContentSize().height -35);
        
        pageView->getPage(idx)->addChild(custom_item);

    }
    

    
//    for (int i = 0; i < 6; i++)
//    {
//        Button* custom_button = Button::create("toast_b.png");
//        custom_button->setName("Title Button");
//        custom_button->setScale9Enabled(true);
//        custom_button->setSize(Size(306,87));
//        custom_button->setScale(.7, .8);
//        custom_button->setTitleText( text[i][0].c_str());
//        custom_button->setTitleFontSize(35);
//        custom_button->setAnchorPoint(Vec2(0, 1));
//        
//        Layout *custom_item = Layout::create();
//        custom_item->setSize(custom_button->getContentSize());
//        custom_item->addChild(custom_button);
//        custom_button->setTag(10);
//        
//        Text* label = Text::create(text[i][1].c_str(),"", 30);
//        label->setAnchorPoint(Vec2(0,1));
//        label->ignoreContentAdaptWithSize(false);
//        label->setTextHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
//        label->setTextVerticalAlignment(cocos2d::TextVAlignment::TOP);
//        label->setTag(11);
//        custom_item->addChild(label);
//        
//        if (text[i][1].size()>44){
//            label->setContentSize(Size(330,125));
//            custom_item->setContentSize(Size(350,125));
//        }else if (text[i][1].size()>22){
//            label->setContentSize(Size(330,90));
//            custom_item->setContentSize(Size(350,100));
//        }else{
//            label->setContentSize(Size(250,35));
//            custom_item->setContentSize(Size(350,80));
//        }
//        custom_button->setPosition(Vec2(20, custom_item->getContentSize().height -20));
//        label->cocos2d::Node::setPosition(250,custom_item->getContentSize().height -35);
//        
//        pageView->getPage(idx)->addChild(custom_item);
//
//    }
}


