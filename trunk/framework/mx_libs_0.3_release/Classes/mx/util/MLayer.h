//
//  MLayer.h
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-31.
//
//

#ifndef __mx_libs_0_3__MLayer__
#define __mx_libs_0_3__MLayer__

#include <iostream>
#include "cocos2d.h"
#include "Factory.h"

USING_NS_CC;

using namespace std;

typedef struct _Progress{
    int now = 0;
    int sum = 0;
} _Progress;


class MLayer : public Layer {
    
public:
    CREATE_FUNC(MLayer);
//    MLayer * createInstance(std::string layername1);
//    MLayer * createInstance(std::string layername1, std::string layername2);
//    MLayer * createInstance(std::string layername1, std::string layername2, std::string layername3);
    void setLayerLoad(std::string layername1);
    void setLayerLoad(std::string layername1, std::string layername2);
    void setLayerLoad(std::string layername1, std::string layername2, std::string layername3);
    
private:
    CC_SYNTHESIZE(ValueMap, _imageLoad, _ImageLoad);
    CC_SYNTHESIZE(ValueVector, _imageSync, _ImageSync);
    CC_SYNTHESIZE(ValueVector, _imageAsync, _ImageAsync);
    CC_SYNTHESIZE(_Progress, _progress, _Progress);
    CC_SYNTHESIZE(Factory *, _factory, _Factory);
    
private:
    void _saveImage(std::string str);
    void _loadImage();
    void _removeImage();
    void _removeCache(std::string filename);
    void _insertCache(std::string filename, bool sync);
    void _finishProgressByJson(float i);
    void _finishProgressByImage(Texture2D* text);
    void _increaseProgress(int i);
    
    void onExit();
    void update(float delta);
    
public:
    // All image finish will run this function
    virtual void renderer();
    // Check image loading progress.
    virtual void progress(_Progress progress);
};

#endif /* defined(__mx_libs_0_3__MLayer__) */
