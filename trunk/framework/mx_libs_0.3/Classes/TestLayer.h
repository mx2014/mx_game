//
//  TestLayer.h
//  mx_libs_0.3
//
//  Created by Rayln on 14-9-1.
//
//

#ifndef __mx_libs_0_3__TestLayer__
#define __mx_libs_0_3__TestLayer__

#include <iostream>
#include "mx/Mx.h"
#include "HelloWorldScene.h"

class TestLayer : public MLayer {
    
public:
    CREATE_FUNC(TestLayer);
    virtual bool init();
    static Scene * createScene();
    virtual void renderer();
    void onEnter();
    void progress(_Progress p);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__mx_libs_0_3__TestLayer__) */
