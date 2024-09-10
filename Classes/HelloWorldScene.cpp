#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorld::init()
{
    CCLOG("Load");
    auto item = MenuItemFont::create("Press start", CC_CALLBACK_1(HelloWorld::menuSceneCallback, this));
    auto menu = Menu::create(item, NULL);
    menu->alignItemsHorizontally();
    this->addChild(menu);
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void HelloWorld::menuSceneCallback(Ref *sender)
{
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
