//
//  ChatWindow.h
//  companyChatTest
//
//  Created by Yawnsan on 14-8-15.
//
//

#ifndef __companyChatTest__ChatWindow__
#define __companyChatTest__ChatWindow__

#include <iostream>
#include "mx/Mx.h"
#include "UserData.h"
#include "NewPageView.h"

class ChatWindow : public Layout {
private:
    
public:
    static Layout * createLayout();
    
    virtual bool init();
    
    CREATE_FUNC(ChatWindow);
    
public:
    CC_SYNTHESIZE(Sprite *, bg, Bg);
    
    CC_SYNTHESIZE(Size, winSize, WinSize);
    
    CC_SYNTHESIZE(Button *, submitButton, SubmitButton);
    
    CC_SYNTHESIZE(NewPageView *, pageView, PageView);
    
    CC_SYNTHESIZE(TextField*, textField , TextField);
    
    CC_SYNTHESIZE(Sprite *, textFieldBg, TextFieldBg);


public:
    void createChatUi();
    
    void createChatBackground();
    
    void createChatButton();

    void createChatPageView();
    
    void createChatListView();
    
    void createTextField();
    
    void textFieldEvent(Ref *pSender, TextField::EventType type);
    
    void listViewEvent(Ref *pSender, ListView::EventType type);
    
    void buttonChange(Ref* ref,Widget::TouchEventType type);
    
    void showChatUi(Ref* ref,Widget::TouchEventType type);
    
    void insertData(const string text,int &idx);
};

#endif /* defined(__companyChatTest__ChatWindow__) */
