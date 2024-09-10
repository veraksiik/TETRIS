#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <cocos2d.h>

USING_NS_CC;

class HelloWorld : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    
private:
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuSceneCallback(Ref* sender);
};
#endif // __HELLOWORLD_SCENE_H__
