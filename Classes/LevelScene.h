#ifndef LevelScene_h
#define LevelScene_h

#include "cocos2d.h"
USING_NS_CC;

class LevelScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(LevelScene);
    
private:
    void gameSceneCallback(Ref* sender);
    void levelTwoCallback(Ref* sender);

};
#endif /* LevelScene_h */
