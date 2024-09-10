#include "MenuScene.h"
#include "LevelScene.h"

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MenuScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto item1 = MenuItemFont::create("Game Start", CC_CALLBACK_1(MenuScene::gameSceneCallback, this));
    auto item2 = MenuItemFont::create("Continue", CC_CALLBACK_1(MenuScene::gameSceneCallback, this));
    auto item3 = MenuItemFont::create("Shop", CC_CALLBACK_1(MenuScene::gameSceneCallback, this));
    auto item4 = MenuItemFont::create("Option", CC_CALLBACK_1(MenuScene::gameSceneCallback, this));
    auto item5 = MenuItemFont::create("Exit", CC_CALLBACK_1(MenuScene::gameCloseCallback, this));
    
    auto menu = Menu::create(item1, item2, item3, item4, item5, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    return true;
}

void MenuScene::gameSceneCallback(Ref *Sender)
{
    Director::getInstance()->replaceScene(LevelScene::createScene());
}

void MenuScene::gameCloseCallback(Ref *Sender)
{
    Director::getInstance()->end();
}
