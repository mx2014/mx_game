//
//  NewPageView.cpp
//  companyChatTest
//
//  Created by Yawnsan on 14-8-19.
//
//

#include "NewPageView.h"


void NewPageView::interceptTouchEvent(TouchEventType event, Widget *sender, Touch *touch)
{
    Vec2 touchPoint = touch->getLocation();
    
    switch (event)
    {
        case TouchEventType::BEGAN:
            //no-op
            break;
        case TouchEventType::MOVED:
        {
            //            float offset = 0;
            //            offset = fabs(sender->getTouchBeganPosition().x - touchPoint.x);
            //            if (offset > _childFocusCancelOffset)
            //            {
            //                sender->setHighlighted(false);
            //                handleMoveLogic(touch);
            //            }
        }
            break;
        case TouchEventType::CANCELED:
        case TouchEventType::ENDED:
            handleReleaseLogic(touch);
            break;
    }
}
