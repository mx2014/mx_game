//
//  MLayer.cpp
//  mx_libs_0.3
//
//  Created by Rayln on 14-8-31.
//
//

#include "MLayer.h"

#define SYSTEM_IMAGE "sys_image"
#define CUSTOM_IMAGE "custom_image"
#define IMAGE_LAYER_LOAD "image_layer_load"
#define IMAGE_LOAD_SYNC "image_load_sync"
#define IMAGE_LOAD_ASYNC "image_load_async"

void MLayer::setLayerLoad(std::string str1){
    MLayer::setLayerLoad(str1, "", "");
}

void MLayer::setLayerLoad(std::string str1, std::string str2){
    MLayer::setLayerLoad(str1, str2, "");
}

void MLayer::setLayerLoad(std::string str1, std::string str2, std::string str3){
    auto config = Configuration::getInstance();
    auto customImage = config->getValue(CUSTOM_IMAGE).asValueMap();
    
    this->set_Factory(Factory::getInstance());
    this->set_ImageLoad(customImage.at(IMAGE_LAYER_LOAD).asValueMap());
    this->_saveImage(str1);
    this->_saveImage(str2);
    this->_saveImage(str3);
    this->_loadImage();

}

void MLayer::update(float delta){
    
}

void MLayer::_saveImage(std::string str){
    if (str != "") {
        auto imageLoad = this->get_ImageLoad();
        auto imageMap = imageLoad.at(str);
        auto imageLayer = imageMap.asValueMap();
        auto imageSync = imageLayer.at(IMAGE_LOAD_SYNC).asValueVector();
        auto imageAsync = imageLayer.at(IMAGE_LOAD_ASYNC).asValueVector();
        for (auto v : imageSync) {
            _imageSync.push_back(v);
        }
        for (auto v : imageAsync) {
            _imageAsync.push_back(v);
        }
        
    }
}

void MLayer::_loadImage(){
    this->_progress.sum = _imageSync.size() + _imageAsync.size();
    
    for (auto v : _imageSync) {
        std::string file = v.asString();
        this->_insertCache(file, true);
    }
    for (auto v : _imageAsync) {
        std::string file = v.asString();
        this->_insertCache(file, false);
    }
}

void MLayer::_insertCache(std::string filename, bool sync){
    std::string suffix = _factory->getSuffix(filename);
    if (suffix == "csb" || suffix == "json" || suffix == "exportjson") {
        if (sync) {
            ArmatureDataManager::getInstance()->addArmatureFileInfo(filename);
            this->_increaseProgress(1);
        }else{
            ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(filename, this, schedule_selector(MLayer::_finishProgressByJson));
        }
    }else if (suffix == "png" || suffix == "jpg" || suffix == "tiff" || suffix == "bmp"){
        if (sync) {
            Director::getInstance()->getTextureCache()->addImage(filename);
            this->_increaseProgress(1);
        }else{
            Director::getInstance()->getTextureCache()->addImageAsync(filename, CC_CALLBACK_1(MLayer::_finishProgressByImage, this));
        }
    }else if (suffix == "plist"){
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
        this->_increaseProgress(1);
    }
}
void MLayer::_finishProgressByImage(Texture2D* text){
    this->_increaseProgress(1);
}

void MLayer::_finishProgressByJson(float i){
    this->_increaseProgress(1);
}

void MLayer::_increaseProgress(int i){
    _progress.now += i;
    this->progress(_progress);
    if (_progress.now == _progress.sum) {
        this->renderer();
    }
    
}

void MLayer::renderer(){
//    log("ArmatureDataManager==%zi==", ArmatureDataManager::getInstance()->getArmatureDatas().size());

}

void MLayer::_removeImage(){
    for (auto v : _imageSync) {
        std::string file = v.asString();
        this->_removeCache(file);
    }
    for (auto v : _imageAsync) {
        std::string file = v.asString();
        this->_removeCache(file);
    }
}

void MLayer::progress(_Progress progress){
    
}

void MLayer::onExit(){
    this->_removeImage();
//    GUIReader::getInstance()->destroyInstance();
//    ArmatureDataManager::getInstance()->destroyInstance();
    Layer::onExit();
}

void MLayer::_removeCache(std::string filename){
    std::string suffix = _factory->getSuffix(filename);
    if (suffix == "csb" || suffix == "json" || suffix == "exportjson") {
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(filename);
    }else if (suffix == "png" || suffix == "jpg" || suffix == "tiff" || suffix == "bmp"){
        Director::getInstance()->getTextureCache()->removeTextureForKey(filename);
    }else if (suffix == "plist"){
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(filename);
    }
}

