//
//  mx.cpp
//  mx_libs_0.1
//
//  Created by Rayln on 14-7-29.
//
//

#include "Mx.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <cctype>

Mx* Mx::mxInstance = nullptr;


Mx* Mx::getInstance(){
    
    if (mxInstance == nullptr) {
        mxInstance = new Mx();
    }
    
    return mxInstance;
}

void Mx::init(){
    this->initConfig();
    this->initSearchPath("sys_image");
    this->initSearchPath("custom_image");
    this->initLanguage();
    this->initResolution();
    
    this->loadingPicture("sys_image");
    this->loadingPicture("custom_image");
}

Layer* Mx::getLayerForResolution(){
    auto layer = Layer::create();
    auto frameSize = Director::getInstance()->getVisibleSize();
    auto orgin = Director::getInstance()->getVisibleOrigin();
    float height = 9 * frameSize.width / 16;
    factory = Factory::getInstance();
    
    layer->setPosition(Size(orgin.x, (frameSize.height - height)/2));
    layer->setContentSize(Size(frameSize.width, height));
    return layer;
}

void Mx::initConfig(){
//    auto shareFileUtil = FileUtils::getInstance();
    std::vector<std::string> path = FileUtils::getInstance()->getSearchPaths();
    path.push_back(imageFolder.config);
    path.push_back(imageFolder.shader);
    FileUtils::getInstance()->setSearchPaths(path);
    this->loadingPictureProgress.pictureCountNum = 0;
    
    Configuration::getInstance()->loadConfigFile("config.plist");
    Configuration::getInstance()->loadConfigFile("config_custom.plist");
}

void Mx::initResolution(){
    auto config = Configuration::getInstance();
    auto map = config->getValue("sys_resolution").asValueMap();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto maxWidthByPhone = Configuration::getInstance()->getValue("sys_max_width").asFloat();
    auto typeList = map.at("type_option").asValueMap();
    if (map.at("is_resolution").asBool()) {
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
        if (map.at("is_scale").asBool()) {
            Director::getInstance()->setContentScaleFactor(scale);
        }
        
        if (frameSize.width > maxWidthByPhone && map.at("is_openHD").asDouble()) {
            view->setDesignResolutionSize(width*2, height*2, policy);
        }else{
            view->setDesignResolutionSize(width, height, policy);
        }
    }
}



void Mx::initSearchPath(string sysfile){
    auto sysImage = Configuration::getInstance()->getValue(sysfile).asValueMap();
    auto map = sysImage.at("image_search_path").asValueMap();
    auto layer = sysImage.at("image_layer_load").asValueMap();
    auto maxWidthByPhone = Configuration::getInstance()->getValue("sys_max_width").asFloat();
    auto sharedFileUtils = FileUtils::getInstance();
    Size winSize = Director::getInstance()->getWinSize();
    
    std::vector<std::string> searchPath = sharedFileUtils->getSearchPaths();
    
    {
    
        string dpi = "";
        if (winSize.width <= maxWidthByPhone) {
            dpi = imageFolder.mdpi;
        }else{
            dpi = imageFolder.hdpi;
        }

        if (!factory->checkElement(searchPath, dpi + "/")) {
            searchPath.push_back(dpi);
        }
        
        auto array = map.at(dpi).asValueVector();
        for (auto value : array) {
            string path = dpi + "/" + value.asString();
            
            if (!factory->checkElement(searchPath, path)) {
                searchPath.push_back(path);
            }
            
        }
    }
    
    for (auto key : layer) {
        std::string folder = key.first;
        auto folderMap = key.second.asValueMap();
        for (auto key2 : folderMap) {
            std::string path = imageFolder.mdpi + "/" + imageFolder.layer + "/" + folder + "/" + key2.first;
            if (!factory->checkElement(searchPath, path)) {
                searchPath.push_back(path);
            }
        }
    }
//    for (auto str : searchPath) {
//        log("-------%s-------", str.c_str());
//    }
    
    sharedFileUtils->setSearchPaths(searchPath);
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

Parameter* Mx::getHttpParameter(){
    auto request = Parameter::create();
    return request;
}

HttpRequest* Mx::send(string urlEnd,Parameter* params, const ccHttpRequestCallback& callback){

    string portStr = "";
    auto sysRequest = Configuration::getInstance()->getValue("sys_request").asValueMap();
    auto map = sysRequest.at("http_request").asValueMap();
    auto ip = map.at("ip").asString();
    auto port = map.at("port").asString();
    
    if (port != "") {
        portStr = ":" + port;
    }
    auto url = "http://" + ip + portStr + "/" + urlEnd + "?" + params->toString();
//    log("==url: %s==", url.c_str());
    return this->send(url.c_str(), callback);
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
/**
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
        ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(value.asString(), this, schedule_selector(Mx::loadingConfigFinish));
    }
    
    for (auto value : imageSync) {
        Director::getInstance()->getTextureCache()->addImage(value.asString());
    }
}
**/

void Mx::loadingPicture(string imagePath){
    auto config = Configuration::getInstance();
    auto sysImage = config->getValue(imagePath).asValueMap();
    auto imageSync = sysImage.at("image_common_sync").asValueVector();
    auto image = sysImage.at("image_common_async").asValueVector();
    this->loadingPictureProgress.pictureCountNum += (imageSync.size() + image.size());
    
    for (auto value : image) {
        this->addFileToCache(value.asString(), false);
    }
    
    for (auto value : imageSync) {
        this->addFileToCache(value.asString(), true);
    }
}
void Mx::addFileToCache(std::string filename, bool sync){
    string suffix = factory->getSuffix(filename);
    if (suffix == "plist") {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
        this->loadingPictureProgress.finishNum += 1;
        
    }else if (suffix == "exportjson" || suffix == "json" || suffix == "csb"){
        if (sync) {
            ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
            this->loadingPictureProgress.finishNum += 1;
        }else{
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(filename, this, schedule_selector(Mx::loadingConfigFinish));
        }
        
    }else if (suffix == "png" || suffix == "jpg" || suffix == "tiff" || suffix == "bmp"){
        if (sync) {
            Director::getInstance()->getTextureCache()->addImage(filename);
            this->loadingPictureProgress.finishNum += 1;
        }else{
            Director::getInstance()->getTextureCache()->addImageAsync(filename, CC_CALLBACK_1(Mx::loadingPictureFinish, this));
        }
    }
}

void Mx::loadingPictureFinish(Texture2D* text){
    this->loadingPictureProgress.finishNum += 1;
}

void Mx::loadingConfigFinish(float t){
    this->loadingPictureProgress.finishNum += 1;
}

void Mx::setShader(Sprite *sprite, SHADER_TYPE type){
    if (type == SHADER_TYPE::GREY_SCALE) {
        sprite->setGLProgramState(this->getGLProgramState("greyScale.fsh"));
    }
    
}

void Mx::setShader(Armature *armature, SHADER_TYPE type){
    if (type == SHADER_TYPE::GREY_SCALE) {
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

Layout * Mx::toast(std::string content){
    DialogBtn button;
    button.buttonNum = 0;
//    return this->createDialog(child, parent, innerSize, button, "");
    return nullptr;
}
Layout * Mx::createDialog(Node* child, Node * parent, Size innerSize){
    DialogBtn button;
    button.buttonNum = 0;
    return this->createDialog(child, parent, innerSize, button, "");
}

Layout * Mx::createDialog(Node* child, Node * parent, Size innerSize, DialogBtn button){
    return this->createDialog(child, parent, innerSize, button, "");
}

Layout * Mx::createDialog(Node* child, Node * parent, Size innerSize, DialogBtn buttonStyle, string background){
    auto layout = Layout::create();
    auto size = parent->getContentSize();
    auto dialogSize = Size(innerSize.width + 30, innerSize.height + 30);
    parent->addChild(layout, 999);
    layout->setContentSize(size);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B::BLACK);
    layout->setBackGroundColorOpacity(150);
    layout->setTouchEnabled(true);

    auto diaLayout = Layout::create();
    layout->addChild(diaLayout);
    diaLayout->setContentSize(innerSize);
    diaLayout->setClippingEnabled(false);
    diaLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    diaLayout->setPosition(Vec2(dialogSize.width/2, dialogSize.height/2));
    diaLayout->setScale(0);
    diaLayout->setBackGroundImageScale9Enabled(true);
    if (background == "") {
        diaLayout->setBackGroundImage("sys_toast_b.png");
    }else{
        diaLayout->setBackGroundImage(background);
    }
    
    diaLayout->setPosition(size/2);
    
    if (child != nullptr) {
        diaLayout->addChild(child);
    }
    
    // set button;
    {
        if (buttonStyle.buttonNum != 0) {
        
            if (buttonStyle.closeText == "") {
                buttonStyle.closeText = this->getStrValue("close");
            }
            auto buttonConfirm = this->createDialogButton(buttonStyle, buttonStyle.confirmText);
            auto buttonClose = this->createDialogButton(buttonStyle, buttonStyle.closeText);

            if (buttonStyle.buttonNum == 1) {
                buttonConfirm->setPosition(Vec2((dialogSize/2).width, 0));
                diaLayout->addChild(buttonConfirm);
            }else{
            
                Size size = buttonConfirm->getContentSize()/2;
                Size center = dialogSize/2;
                buttonConfirm->setPosition(Vec2(center.width - size.width, 0));
                buttonClose->setPosition(Vec2(center.width + size.width, 0));
                diaLayout->addChild(buttonConfirm);
                diaLayout->addChild(buttonClose);
            }
        }
        if (buttonStyle.isVisibleClose) {
            auto buttonClose = this->createDialogCloseButton(buttonStyle, buttonStyle.closeText, layout, diaLayout);
            diaLayout->addChild(buttonClose);
            buttonClose->setPosition(diaLayout->getContentSize() - buttonClose->getContentSize()/2 + Size(25, 25));
        }
    }
    auto action = EaseBackOut::create(ScaleTo::create(.3, 1));
    diaLayout->runAction(action);
    return layout;
}

Button * Mx::createDialogButton(DialogBtn button, string text){
    auto buttonConfirm = Button::create("sys_dialog_button_normal.png","sys_dialog_button_down.png");
    buttonConfirm->setScale(.7);
    buttonConfirm->setTitleText(text);
    buttonConfirm->setTitleFontSize(22);
    
    return buttonConfirm;
}
Button * Mx::createDialogCloseButton(DialogBtn button, string text, Layout* layout, Layout* diaLayout){
    auto buttonConfirm = Button::create("sys_dialog_button_close.png");
    buttonConfirm->setScale(.7);
    buttonConfirm->addTouchEventListener(CC_CALLBACK_2(Mx::closeDialog, this, layout, diaLayout));
    return buttonConfirm;
}

void Mx::closeDialog(Ref *pSender, ui::Widget::TouchEventType type, Layout* layout, Layout* diaLayout){
    auto action = EaseBackIn::create(ScaleTo::create(.3, 0));
    auto func = CallFunc::create(CC_CALLBACK_0(Mx::closeDialogFunc, this, layout, diaLayout));
    auto seq = Sequence::create(action,func, NULL);
    
    diaLayout->runAction(seq);
    
    
}

void Mx::closeDialogFunc(Layout* layout, Layout* diaLayout){
    layout->removeFromParentAndCleanup(true);
    
}

Texture2D * Mx::getTexture2D(std::string filename){
    return Director::getInstance()->getTextureCache()->getTextureForKey(filename);
}

std::vector<std::string> Mx::getFilePathAtVec(std::string filePath)
{
    std::vector<std::string> path_vec;
    //    DIR *dp;
    //    struct dirent *entry;
    //    struct stat statbuf;
    //    int i=0;
    //
    //    if((dp=opendir(filePath.c_str()))==NULL)
    //    {
    ////        fprintf(stderr,cannot open %s,filePath.c_str());
    //        exit(1);
    //    }
    //    chdir(filePath.c_str());
    //
    //    while((entry=readdir(dp))!=NULL&&i<255)
    //    {
    //        stat(entry->d_name,statbuf);
    //        if(!S_ISREG(statbuf.st_mode))
    //            continue;
    //        log("%s", entry->d_name);
    ////        path_vec.push_back(std::StringUtils::format(%s,entry->d_name));
    //    }
    //    auto sharedFileUtils = FileUtils::getInstance();
    //    sharedFileUtils->purgeCachedEntries();
    //    std::vector<std::string> searchPath = sharedFileUtils->getSearchPaths();
    //    searchPath.insert(searchPath.begin(),   "Misc");
    //    for (std::string a : searchPath) {
    //        log("---searchPath--:%s --", a.c_str());
    //    }
    //    sharedFileUtils->setSearchPaths(searchPath);
    //
    //    std::vector<std::string> resolutionsOrder = sharedFileUtils->getSearchResolutionsOrder();
    //    resolutionsOrder.insert(resolutionsOrder.begin(), "resources-ipadhd");
    //    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    //    for (std::string a : resolutionsOrder) {
    //        log("---resolutionsOrder--:%s --", a.c_str());
    //    }
    //    sharedFileUtils->setSearchResolutionsOrder(resolutionsOrder);
    //
    //    log("---getWritablePath():----%s------", sharedFileUtils->getWritablePath().c_str());
    //    auto vm = sharedFileUtils->getValueMapFromFile("config");
    //    log("______vm: %zi_________", vm.size());
    //
    //    auto vv = sharedFileUtils->getValueVectorFromFile("config");
    //    log("______vv: %zi_____", vv.size());
    //
    //    std::unordered_map<std::string, std::string> map = sharedFileUtils->getFullPathCache();
    //    log("----count: %zi---", map.size());
    //    for (auto obj : map) {
    //        std::string k = obj.first;
    //        std::string v = obj.second;
    //        log("+++k: %s,  v: %s++++", k.c_str(), v.c_str());
    //    }
    //
    //    string s = FileUtils::getInstance()->fullPathForFilename("dialog_button_disable.png");
    
    //    log("====%s===", s.c_str());
    DIR* dirp;
    struct dirent* direntp;
    dirp = opendir( "assets/config" );
    if( dirp != NULL ) {
        log("------load dir----");
        for(;;) {
            direntp = readdir( dirp );
            if( direntp == NULL ) break;
            log( "%s", direntp->d_name );
        }
        closedir( dirp );
        //        return EXIT_SUCCESS;
    }
    
    std::unordered_map<std::string, std::string> map =FileUtils::getInstance()->getFullPathCache();
    string ss = FileUtils::getInstance()->getStringFromFile("config.plist");
    log("#########%zi#########", map.size());
    for (auto o : map) {
        log("-----key: %s, value: %s----------", o.first.c_str(), o.second.c_str());
    }
    return path_vec;
}

