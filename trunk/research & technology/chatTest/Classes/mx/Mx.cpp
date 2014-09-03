//
//  mx.cpp
//  mx_libs_0.1
//
//  Created by Rayln on 14-7-29.
//
//

#include "Mx.h"
#include <unistd.h>

typedef struct ImageFolder{
    string folder1 = "mdpi";
    string folder2 = "hdpi";
    string folder3 = "config";
    string folder4 = "shader";
}ImageFolder;

Mx* Mx::mxInstance = nullptr;


Mx* Mx::getInstance(){
    
    if (mxInstance == nullptr) {
        mxInstance = new Mx();
    }
    
    return mxInstance;
}

void Mx::init(){
    this->initConfig();
    this->initSearchPath();
    this->initLanguage();
    this->initResolution();
    
    this->loadingPicture();
}

Layer* Mx::getLayerForResolution(){
    auto layer = Layer::create();
    auto frameSize = Director::getInstance()->getVisibleSize();
    auto orgin = Director::getInstance()->getVisibleOrigin();
    
    float height = 9 * frameSize.width / 16;
    layer->setPosition(Size(orgin.x, (frameSize.height - height)/2));
    layer->setContentSize(Size(frameSize.width, height));
    return layer;
}

void Mx::initConfig(){
    Configuration::getInstance()->loadConfigFile("config.plist");
}

void Mx::initResolution(){
    auto config = Configuration::getInstance();
    auto map = config->getValue("setResolution").asValueMap();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto maxWidthByPhone = Configuration::getInstance()->getValue("maxWidthByPhone").asFloat();
    auto typeList = map.at("typeList").asValueMap();
    if (map.at("isResolution").asBool()) {
        auto view = Director::getInstance()->getOpenGLView();
        auto typeName = map.at("type").asString();
        auto type = typeList.at(typeName).asString();
//        auto size = Director::getInstance()->getWinSize();
        auto size = view->getFrameSize();
        
        float width = map.at("width").asFloat();
        float height = map.at("height").asFloat();
        float scale = 1.0;
        
        auto policy = ResolutionPolicy::EXACT_FIT;
        if (type == "FIXED_WIDTH") {
            policy = ResolutionPolicy::FIXED_WIDTH;
            scale = width / size.width;
            
        }else if (type == "FIXED_HEIGHT") {
            policy = ResolutionPolicy::FIXED_HEIGHT;
            scale = height / size.height;
            
        }else if (type == "EXACT_FIT") {
            policy = ResolutionPolicy::EXACT_FIT;
            
        }else if (type == "NO_BORDER") {
            policy = ResolutionPolicy::NO_BORDER;
            
            if (width / size.width > height / size.height) {
                scale = height / size.height;
            }else{
                scale = width / size.width;
            }
            
        }else if (type == "SHOW_ALL") {
            policy = ResolutionPolicy::SHOW_ALL;
            if (width / size.width < height / size.height) {
                scale =height / size.height;
            }else{
                scale =width / size.width;
            }
        }
        if (map.at("isScale").asBool()) {
            Director::getInstance()->setContentScaleFactor(scale);
        }
        
        if (frameSize.width > maxWidthByPhone && map.at("isOpenHD").asDouble()) {
            view->setDesignResolutionSize(width*2, height*2, policy);
        }else{
            view->setDesignResolutionSize(width, height, policy);
        }
        
    }
    
}

void Mx::initSearchPath(){
    auto map = Configuration::getInstance()->getValue("imageFolder").asValueMap();
    auto maxWidthByPhone = Configuration::getInstance()->getValue("maxWidthByPhone").asFloat();
    Size winSize = Director::getInstance()->getWinSize();
    ImageFolder folder;
    std::vector<std::string> searchPath;
    for (auto key : map) {
        if (folder.folder1 == key.first && winSize.width <= maxWidthByPhone) {
            string keystr = key.first;
            auto array = key.second.asValueVector();
            searchPath.push_back(keystr);
            for (auto value : array) {
                auto str = keystr + "/" + value.asString();
                searchPath.push_back(str);
            }
        }else if (folder.folder2 == key.first && winSize.width > maxWidthByPhone) {
            string keystr = key.first;
            auto array = key.second.asValueVector();
            searchPath.push_back(keystr);
            for (auto value : array) {
                auto str = keystr + "/" + value.asString();
                searchPath.push_back(str);
            }
        }
        
    }
    searchPath.push_back(folder.folder3);
    searchPath.push_back(folder.folder4);
    CCFileUtils::getInstance()->setSearchPaths(searchPath);
}

void Mx::initLanguage(){
    LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
    switch (currentLanguageType)
    {
        
        case LanguageType::CHINESE:
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::ENGLISH:
            //Configuration::getInstance()->loadConfigFile("config_language_en.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::FRENCH:
            //Configuration::getInstance()->loadConfigFile("config_language_fre.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::GERMAN:
//            Configuration::getInstance()->loadConfigFile("config_language_ger.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::ITALIAN:
//            Configuration::getInstance()->loadConfigFile("config_language_ita.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::RUSSIAN:
//            Configuration::getInstance()->loadConfigFile("config_language_rus.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::SPANISH:
//            Configuration::getInstance()->loadConfigFile("config_language_spa.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::KOREAN:
//            Configuration::getInstance()->loadConfigFile("config_language_kor.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::JAPANESE:
//            Configuration::getInstance()->loadConfigFile("config_language_jp.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::HUNGARIAN:
//            Configuration::getInstance()->loadConfigFile("config_language_hun.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::PORTUGUESE:
//            Configuration::getInstance()->loadConfigFile("config_language_port.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::ARABIC:
//            Configuration::getInstance()->loadConfigFile("config_language_ara.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::NORWEGIAN:
//            Configuration::getInstance()->loadConfigFile("config_language_norw.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::POLISH:
//            Configuration::getInstance()->loadConfigFile("config_language_polish.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        case LanguageType::DUTCH:
//            Configuration::getInstance()->loadConfigFile("config_language_dutch.plist");
            Configuration::getInstance()->loadConfigFile("config_language_zh.plist");
            break;
        default:
            CCASSERT(false, "Invalid language type.");
            break;
    }
}


HttpRequest* Mx::send(const char* url, const ccHttpRequestCallback& callback){
    return this->send(url, HttpRequest::Type::GET, callback);
}

HttpRequest* Mx::send(const char* url, HttpRequest::Type type, const ccHttpRequestCallback& callback){
    return this->send(url, type, true, callback);
}
HttpRequest* Mx::send(const char* url, HttpRequest::Type type, bool isImmediate, const ccHttpRequestCallback& callback){
    HttpRequest* request = new HttpRequest();
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(callback);
    if (isImmediate)
    {
        HttpClient::getInstance()->sendImmediate(request);
    }else
    {
        HttpClient::getInstance()->send(request);
    }
    request->release();
    
    return request;
}

rapidjson::Document Mx::getJson(string* str){
    rapidjson::Document json;;
    json.Parse<0>(str->c_str());
    return json;
}

void Mx::shaky(Node * node){
    this->shaky(node, 3, 5, .3);
}

void Mx::shaky(Node * node, float duration){
    int time = duration/.3;
    this->shaky(node, 3, time*5, duration);
}

void Mx::shaky(Node * node, float range = 3, int time = 5, float duration = .3){
    Vector<FiniteTimeAction *> vetor;
    for (int i = 0; i <= time; i++) {
        range = range - range*(i/time);
        
        auto move1 = MoveBy::create(0, Vec2(0, range));
        auto move2 = MoveBy::create(0, Vec2(0, -range));
        auto delay = DelayTime::create(duration/(time*2));
        vetor.pushBack(move1);
        vetor.pushBack(delay);
        vetor.pushBack(move2);
        vetor.pushBack(delay);
    }
    auto seq = Sequence::create(vetor);
    node->runAction(seq);
    
}

string Mx::MD5(string str){
    return md5(str);
}

void Mx::loadingPicture(){
    auto config = Configuration::getInstance();
    auto imageSync = config->getValue("imageLoadBySync").asValueVector();
    auto image = config->getValue("imageLoad").asValueVector();
    auto plist = config->getValue("imageLoadPlist").asValueVector();
    auto armature = config->getValue("imageLoadAmature").asValueVector();
    this->loadingPictureProgress.pictureCountNum = (armature.size()+image.size());
    
    for (auto value : image) {
        Director::getInstance()->getTextureCache()->addImageAsync(value.asString(), CC_CALLBACK_1(Mx::loadingPictureFinish, this));
    }
    for (auto value : plist) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(value.asString());
    }
    
    for (auto value : armature) {
//        auto temp = value.asValueVector();
//        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(temp.at(0).asString(), temp.at(1).asString(), temp.at(2).asString(), this, schedule_selector(Mx::loadingPictureFinish));
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(value.asString(), this, schedule_selector(Mx::loadingConfigFinish));
    }
    
    for (auto value : imageSync) {
        Director::getInstance()->getTextureCache()->addImage(value.asString());
    }
}

void Mx::loadingPictureFinish(Texture2D* text){
    this->loadingPictureProgress.finishNum += 1;
}

void Mx::loadingConfigFinish(float t){
    this->loadingPictureProgress.finishNum += 1;
//    log("===loadingPictureFinish: %i==%i=", loadingPictureProgress.finishNum, loadingPictureProgress.pictureCountNum);
}

void Mx::setShader(Sprite *sprite, SHADER_TYPE type){
    if (type == SHADER_TYPE::GREY_SCALE) {
        sprite->setGLProgramState(this->getGLProgramState("greyScale.fsh"));
    }
    
}

void Mx::setShader(Armature *armature, SHADER_TYPE type){
    if (type == SHADER_TYPE::GREY_SCALE) {
//        sprite->setGLProgramState(this->getGLProgramState("greyScale.fsh"));
        auto map = armature->getBoneDic();
        for (auto value : map) {
            auto bone = value.second->getDisplayRenderNode();
            bone->setGLProgramState(this->getGLProgramState("greyScale.fsh"));
        }
    }
}

GLProgramState* Mx::getGLProgramState(string fragmentFilename){
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragmentFilename);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //    _fragSource = fragSource;
    //#endif
    
    return GLProgramState::getOrCreateWithGLProgram(glprogram);
    
}

string Mx::getStrValue(string str){
    return Configuration::getInstance()->getValue(str).asString();
}

Layout * Mx::createDialog(Node* child, Node * parent, float width, float height){
    auto layout = Layout::create();
    parent->addChild(layout, 999);
    layout->setContentSize(parent->getContentSize());
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B::BLACK);
    layout->setBackGroundColorOpacity(150);
    layout->setTouchEnabled(true);
    
    
    return layout;
}
