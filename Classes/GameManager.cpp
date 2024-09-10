#include "GameManager.h"

void setDeltaShape(Tetromino* t, int delta[]);

Tetromino* GameManager::createTetromino()
{
    // 랜덤 테트로미노 생성
    int randint = RandomHelper::random_int(0, 6);
    Tetromino* tetromino = new Tetromino();
    
    switch (6)
    {
        // J 블록
        case Shape::J:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("blue.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeJ[] = {0, 0, 0, 1, 0, 2, -1, 0};
            setDeltaShape(tetromino, delta_shapeJ);
            tetromino->shape = Shape::J;
            break;
        }
        // I 블록
        case Shape::I:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("skyblue.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeI[] = {0, 0, 0, 1, 0, 2, 0, 3};
            setDeltaShape(tetromino, delta_shapeI);
            tetromino->shape = Shape::I;
            break;
        }
        // O 블록
        case Shape::O:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("yellow.png", Rect(15, 15, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeO[] = {0, 0, 0, 1, -1, 0, -1, 1};
            setDeltaShape(tetromino, delta_shapeO);
            tetromino->shape = Shape::O;
            break;
        }
        // h 블록
        case Shape::H:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("purple.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeH[] = {0, 0, -1, -1, -1, 0, -1, 1};
            setDeltaShape(tetromino, delta_shapeH);
            tetromino->shape = Shape::H;
            break;
        }
        // L 블록
        case Shape::L:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("orange.png", Rect(15, 15, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeL[] = {0, 0, -1, 0, -1, 1, -1, 2};
            setDeltaShape(tetromino, delta_shapeL);
            tetromino->shape = Shape::L;
            break;
        }
        // S 블록
        case Shape::S:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("green.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeS[] = {0, 0, 0, 1, -1, 1, -1, 2};
            setDeltaShape(tetromino, delta_shapeS);
            tetromino->shape = Shape::S;
            break;
        }
        // Z 블록
        case Shape::Z:
        {
            for (int i = 0; i < 4; ++i)
            {
                tetromino->block[i].sprite = Sprite::create("red.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
            }
            
            int delta_shapeZ[] = {0, 0, 0, 1, -1, -1, -1, 0};
            setDeltaShape(tetromino, delta_shapeZ);
            tetromino->shape = Shape::Z;
            break;
        }
    }
    
    return tetromino;
}

void setDeltaShape(Tetromino* t, int delta[])
{
    int _x = t->originX;
    int _y = t->originY;
    int delta_idx = 0;
    
    for(int i = 0; i < 4; ++i)
    {
        t->block[i].x = _x + delta[delta_idx];
        t->block[i].y = _y + delta[delta_idx + 1];
        delta_idx += 2;
    }
}
