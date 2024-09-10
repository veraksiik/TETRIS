#pragma once
#include "Headers.h"
#include "Tetromino.h"
#include "GameManager.h"



class GameScene : public Layer
{
public:
    Tetromino* cur_tetro;
    BoardState board[MAX_ROW][MAX_COL];
    static Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    
private:
    GameManager gm;
    
    void update(float fDelta) override;
    void drawGridMap();
    void drawTetromino();
    void checkLine(int line);
    void popLine(int line);
    
    void leftBtnCallback(Ref* sender);
    void rightBtnCallback(Ref* sender);
    void rotateBtnCallback(Ref* sender);
    
    bool downCheck();
    void fall();
};
