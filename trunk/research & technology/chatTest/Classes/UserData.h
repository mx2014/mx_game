//
//  UserData.h
//  companyChatTest
//
//  Created by Yawnsan on 14-8-15.
//
//

#ifndef __companyChatTest__UserData__
#define __companyChatTest__UserData__

#include <iostream>
#include "mx/Mx.h"

class UserData :public Layout {

private:
    
public:
    
    static Layout* createLayout();
    
    virtual bool init();
    
    CREATE_FUNC(UserData);
    
    void onEnter();

public:
    void createLayoutBg();
    
    void createLayoutDate();
    
    void createLayoutButton();
    
    void buttonChange(Ref* ref,Widget::TouchEventType type);
    
    CC_SYNTHESIZE(float, buttonHeight, ButtonHeight);
    
    CC_SYNTHESIZE(Layout *, layoutWin, LayoutWin);
    
    CC_SYNTHESIZE(string, userName, UserName);
    
    CC_SYNTHESIZE(string, userData1, UserData1);
    
    CC_SYNTHESIZE(TextField *, textField , TextField);


};

#endif /* defined(__companyChatTest__UserData__) */
