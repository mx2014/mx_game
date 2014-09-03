//
//  NewPageView.h
//  companyChatTest
//
//  Created by Yawnsan on 14-8-19.
//
//

#ifndef __companyChatTest__NewPageView__
#define __companyChatTest__NewPageView__

#include <iostream>
#include "mx/Mx.h"

class NewPageView : public PageView {
    
public:
    CREATE_FUNC(NewPageView);
    
public:
    void interceptTouchEvent(TouchEventType event, Widget *sender, Touch *touch) override;
};

#endif /* defined(__companyChatTest__NewPageView__) */
