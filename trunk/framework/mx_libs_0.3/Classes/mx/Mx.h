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
#include "entity/Parameter.h"

#include "util/MD5.h"
#include "util/MLayer.h"
#include "util/Factory.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using namespace cocostudio;
using namespace ui;

using namespace network;

// Loading picture
typedef struct LoadingPictureProgress{
    int pictureCountNum = 0;
    int finishNum = 0;
} LoadingPictureProgress;

// Dialog button
typedef struct DialogBtn{
    string confirmText = "";
    string closeText = "";
    int fontSize = 22;
    int buttonNum = 2;
    bool isVisibleBtn = true;
    bool isVisibleClose = true;
} DialogBtn;

typedef struct ImageFolder{
    string mdpi = "_mdpi";
    string hdpi = "_hdpi";
    string config = "_config";
    string shader = "_shader";
    string layer = "_layer";
} ImageFolder;


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
    static Mx * mxInstance;
    Factory * factory;
    ImageFolder imageFolder;
    LoadingPictureProgress loadingPictureProgress;
    
    static Mx * getInstance();
    void init();
    
private:

    void initLanguage();
    void initConfig();
    void initResolution();
    void initSearchPath(string sysImage);
    
public:
//    CC_SYNTHESIZE(Layout*, diaLayout, DiaLayout);
    
public:
    //send http request
    Parameter* getHttpParameter();
    HttpRequest* send(string urlEnd, Parameter* params, const ccHttpRequestCallback& callback);
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
    void loadingPicture(string imagePath);
    void loadingPictureFinish(Texture2D* text);
    void loadingConfigFinish(float t);
    void addFileToCache(std::string filename, bool sync);
    
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
    
    Layout * toast(std::string content);
    Layout * createDialog(Node* child, Node * parent, Size innerSize);
    Layout * createDialog(Node* child, Node * parent, cocos2d::Size innerSize, DialogBtn button);
    Layout * createDialog(Node* child, Node * parent, cocos2d::Size dialogSize, DialogBtn button, string background);
    Button * createDialogButton(DialogBtn button, string text);
    Button * createDialogCloseButton(DialogBtn button, string text, Layout* layout, Layout* diaLayout);
    void closeDialog(Ref *pSender, ui::Widget::TouchEventType type, Layout* layout, Layout* diaLayout);
    void closeDialogFunc(Layout* layout, Layout* diaLayout);
    
    //get Texture2D
    Texture2D * getTexture2D(std::string filename);
    
    //get file list
    std::vector<std::string> getFilePathAtVec(std::string filePath);
    void dfsFolder(string folderPath,int depth);
};

#endif /* defined(__mx_libs_0_1__mx__) */
