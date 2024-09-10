#include "GameScene.h"

float frame = 0;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 격자 그리기
    drawGridMap();
    
    // 버튼
    auto label1 = Label::createWithSystemFont("Left", "arial", 10);
    auto label2 = Label::createWithSystemFont("Right", "arial", 10);
    auto label3 = Label::createWithSystemFont("Rotate", "arial", 10);
    
    auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameScene::leftBtnCallback, this));
    auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(GameScene::rightBtnCallback, this));
    auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(GameScene::rotateBtnCallback, this));
    
    Menu* menu = Menu::create(item1, item2, item3, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Point(300, 100));
    this->addChild(menu, 1);
    this->scheduleUpdate();
    
    // 테트로미노 생성하고 그리기
    drawTetromino();
    return true;
}

void GameScene::update(float fDelta)
{
    frame += fDelta;
    if(frame < FALL_DELAY_TIME)
    {
        return;
    }
    frame -= FALL_DELAY_TIME;
    
    // 현재 테트로미노가 다음에 충돌하면 새 블록 생성
    if(downCheck())
    {
        drawTetromino();
    }
    // 충돌하지 않으면 떨어지기
    else
    {
        fall();
    }
}

void GameScene::drawGridMap()
{
    // 가로줄
    for (int i = 0; i <= MAX_MAP; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(0, i * BLOCK_SIZE),
            Vec2(BLOCK_SIZE * MAX_MAP, i * BLOCK_SIZE),
            Color4F(Color3B::WHITE, 1));

        this->addChild(draw, 1);
    }

    // 세로줄
    for (int i = 0; i <= MAX_MAP; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(i * BLOCK_SIZE, 0),
            Vec2(i * BLOCK_SIZE, BLOCK_SIZE * MAX_MAP),
            Color4F(Color3B::WHITE, 1));
        this->addChild(draw, 1);
    }
}

void GameScene::drawTetromino()
{
    cur_tetro = gm.createTetromino();
    for (int i = 0; i < 4; ++i)
    {
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        board[cy][cx].state = BoardInfo::fallingblock;
        board[cy][cx].p_sprite = cur_tetro->block[i].sprite;
        
        board[cy][cx].p_sprite->setAnchorPoint(Point(0, 0));
        board[cy][cx].p_sprite->setPosition(150 + cx * BLOCK_SIZE, cy * BLOCK_SIZE);
        
        
        this->addChild(board[cy][cx].p_sprite);
        
    }
}

bool GameScene::downCheck()
{
    for (int i = 0; i < 4; ++i)
    {
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        // 제일 밑칸이거나 밑에 블록이 있다면
        if (cy == 0 || board[cy-1][cx].state == BoardInfo::obstacle)
        {
            // 부딪히므로 떨어지는 테트로미노(2)를 (1)로 바꿔주기
            for (int j = 0; j < 4; ++j)
            {
                int cx = cur_tetro->block[j].x;
                int cy = cur_tetro->block[j].y;
                board[cy][cx].state = BoardInfo::obstacle;
            }
            // 줄 가득 차면 땡겨오기
            for (int i = MAX_MAP_ROW; i >= 0; --i)
                checkLine(i);
            return true;
        }
    }
    return false;
}

void GameScene::fall()
{
    for (int i = 0; i < 4; ++i)
    {
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        board[cy - 1][cx].p_sprite = board[cy][cx].p_sprite;
    
        // 보드 수정
        board[cy - 1][cx].state = BoardInfo::tempblock;
        board[cy][cx].state = BoardInfo::None;
        board[cy][cx].p_sprite = nullptr;
        
        cur_tetro->block[i].y -= 1;
    }
    for (int i = 0; i < 4; ++i)
    {
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        auto moveDown = MoveBy::create(0, Point(0, -BLOCK_SIZE));
        board[cy][cx].state = BoardInfo::fallingblock;
        if(board[cy][cx].p_sprite == nullptr)
        {
            CCLOG("%i", i);
        }
        else {
            board[cy][cx].p_sprite->runAction(moveDown);
        }
    }
}

void GameScene::checkLine(int line)
{
    for (int i = 0; i < MAX_COL; ++i)
    {
        if(board[line][i].state == BoardInfo::None)
            return;
    }
    popLine(line);
}

void GameScene::popLine(int line)
{
    CCLOG("popLine : %i", line);
    for (int i = line; i <MAX_MAP_ROW; ++i)
    {
        for (int j = 0; j < MAX_COL; ++j)
        {
            // 윗줄 가져오기
            board[i][j].state = board[i + 1][i].state;
            board[i + 1][j].state = BoardInfo::None;
            
            // 원래 이미지 삭제하고 위의 이미지 보여주기
            if(board[i][j].p_sprite != nullptr)
                board[i][j].p_sprite->removeFromParent();
            //
            board[i][j].p_sprite = board[i + 1][j].p_sprite;
            Action* moveDown = MoveBy::create(0, Point(0, -BLOCK_SIZE));
            if (board[i][j].p_sprite != nullptr)
            {
                board[i][j].p_sprite->runAction(moveDown);
            }
            board[i + 1][j].p_sprite = nullptr;
        }
    }
}


void GameScene::leftBtnCallback(Ref* sender)
{
    cur_tetro->moveLeft(board);
}

void GameScene::rightBtnCallback(Ref* sender)
{
    cur_tetro->moveRight(board);
}

void GameScene::rotateBtnCallback(Ref* sender)
{
    cur_tetro->Rotate(board, cur_tetro->rotateidx);
}
