#ifndef MenuScene_h
#define MenuScene_h

#include "cocos2d.h"
USING_NS_CC;

class MenuScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
private:
    void gameSceneCallback(Ref* Sender);
    void gameCloseCallback(Ref* Sender);
};
#endif /* MenuScene_h */
