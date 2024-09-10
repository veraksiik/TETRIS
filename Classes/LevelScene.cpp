#include "LevelScene.h"
#include "GameScene.h"

Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LevelScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool LevelScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto item1 = MenuItemFont::create("Level 1", CC_CALLBACK_1(LevelScene::gameSceneCallback, this));
    auto item2 = MenuItemFont::create("Level 2", CC_CALLBACK_1(LevelScene::gameSceneCallback, this));
    
    auto levelMenu = Menu::create(item1, item2, NULL);
    levelMenu->alignItemsVertically();
    this->addChild(levelMenu);
    return true;
}

void LevelScene::gameSceneCallback(Ref *sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}
