//
//  mx.h
//  mx_libs_0.1
//
//  Created by Rayln on 14-7-29.
//
//

#ifndef __mx_libs_0_1__mx__
#define __mx_libs_0_1__mx__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "cocosGUI.h"
#include "network/HttpClient.h"

#include <netdb.h>
#include "MD5.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using namespace cocostudio;
using namespace ui;

using namespace network;

typedef struct LoadingPictureProgress{
    int pictureCountNum = 0;
    int finishNum = 0;
} LoadingPictureProgress;

typedef enum SHADER_TYPE{
    BLOOM,
    BLUR,
    CEL_SHADING,//celShading
    COLOR_BARS, //colorBars
    EDGE_DETECTION, // edgeDetection,
    FLOWER, // flower,
    HEART, // heart,
    HORIZONTAL_COLOR, // horizontalColor,
    JULIA, // julia,
    LEN_FLARE, // lensFlare,
    MANDELBROT, // mandelbrot,
    MONJORI, // monjori,
    MULTI_TEXTURE, // multiTexture,
    NOISY, // noisy,
    NORMAL, //normal,
    OUTLINE, // outline,
    PLASMA, // plasma,
    SEPIA, // sepia,
    TWIST, // twist,
    SHADERTOY_FIREBALL, // shadertoy_FireBall,
    SHADERTOY_GLOW, // shadertoy_Glow,
    SHADERTOY_LENSFLARE, // shadertoy_LensFlare,
    GREY_SCALE // greyScale
} SHADER_TYPE;


class Mx : public Ref{
    
public:
    static Mx *mxInstance;
    LoadingPictureProgress loadingPictureProgress;
    
    static Mx * getInstance();
    void init();
    
private:

    void initLanguage();
    void initConfig();
    void initSearchPath();
    void initResolution();
    
public:
    //send http request
    HttpRequest* send(const char* url, const ccHttpRequestCallback& callback);
    HttpRequest* send(const char* url, HttpRequest::Type type, const ccHttpRequestCallback& callback);
    HttpRequest* send(const char* url, HttpRequest::Type type, bool isImmediate, const ccHttpRequestCallback& callback);
    
    // parse Json format
    rapidjson::Document getJson(string* str);
    
    //screen shaky function
    void shaky(Node * node);
    void shaky(Node * node, float duration);
    void shaky(Node * node, float range, int time, float duration);
    
    //loading picture by async
    void loadingPicture();
    void loadingPictureFinish(Texture2D* text);
    void loadingConfigFinish(float t);
    
    //get Layer resolution
    Layer* getLayerForResolution();
    
    //get MD5 by string
    string MD5(string str);
    
    //set shader effect to node and armature
    void setShader(Sprite *sprite, SHADER_TYPE type);
    void setShader(Armature *armature, SHADER_TYPE type);
    GLProgramState* getGLProgramState(string fragmentFilename);
    
    //get language file string value
    string getStrValue(string str);
    
    Layout * createDialog(Node* child, Node * parent, float width, float height);
};

#endif /* defined(__mx_libs_0_1__mx__) */
