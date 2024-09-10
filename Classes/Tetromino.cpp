#include "Tetromino.h"

void Tetromino::moveLeft(BoardState board[][MAX_COL])
{
    // 움직일 수 있는지 체크
    for (int i = 0; i < 4; ++i)
    {
        if (board[block[i].y][block[i].x-1].state == BoardInfo::obstacle || block[i].x == 0)
        {
            return;
        }
    }
    
    // 이동
    for (int i = 3; i >= 0; --i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        board[cy][cx - 1].p_sprite = board[cy][cx].p_sprite;

        // 보드 수정
        board[cy][cx - 1].state = BoardInfo::tempblock;
        board[cy][cx].state = BoardInfo::None;
        board[cy][cx].p_sprite = nullptr;
        block[i].x -= 1;
    }
    
    for (int i = 3; i >= 0; --i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        auto moveLeft = MoveBy::create(0, Point(-BLOCK_SIZE, 0));
        board[cy][cx].state = BoardInfo::fallingblock;
        board[cy][cx].p_sprite->runAction(moveLeft);
    }
}

void Tetromino::moveRight(BoardState board[][MAX_COL])
{
    // 움직일 수 있는지 체크
    for (int i = 0; i < 4; ++i)
    {
        if (board[block[i].y][block[i].x+1].state == BoardInfo::obstacle || block[i].x == MAX_COL-1)
        {
            return;
        }
    }
    
    // 이동
    for (int i = 0; i < 4; ++i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        board[cy][cx + 1].p_sprite = board[cy][cx].p_sprite;

        // 보드 수정
        board[cy][cx + 1].state = BoardInfo::tempblock;
        board[cy][cx].state = BoardInfo::None;
        board[cy][cx].p_sprite = nullptr;
        block[i].x += 1;
    }
    
    for (int i = 0; i < 4; ++i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        auto moveRight = MoveBy::create(0, Point(BLOCK_SIZE, 0));
        board[cy][cx].state = BoardInfo::fallingblock;
        board[cy][cx].p_sprite->runAction(moveRight);
    }
}

void Tetromino::Rotate(BoardState board[][MAX_COL], int r_idx)
{
    // 회전 가능한지 확인
    for(int i = 0; i < 4; ++i)
    {
        int dx = delta_rotate[4 * shape + r_idx][2 * i];
        int dy = delta_rotate[4 * shape + r_idx][2 * i + 1];
        int nx = block[i].x + dx;
        int ny = block[i].y + dy;
        if (nx < 0 || nx >= MAX_COL || ny < 0 || board[ny][nx].state == BoardInfo::obstacle)
            return;
    }
    // 회전
    for (int i = 0; i < 4; ++i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        int dx = delta_rotate[4 * shape + r_idx][2 * i];
        int dy = delta_rotate[4 * shape + r_idx][2 * i + 1];
        board[cy+dy][cx+dx].p_sprite = board[cy][cx].p_sprite;
        
        board[cy+dy][cx+dx].state = BoardInfo::tempblock;
        
        if(board[cy][cx].state != BoardInfo::tempblock)
        {
            board[cy][cx].state = BoardInfo::None;
            board[cy][cx].p_sprite = nullptr;
        }
                
        block[i].x += dx;
        block[i].y += dy;
    }
    
    for (int i = 0; i < 4; ++i)
    {
        int cx = block[i].x;
        int cy = block[i].y;
        int dx = delta_rotate[4 * shape + r_idx][2 * i];
        int dy = delta_rotate[4 * shape + r_idx][2 * i + 1];
        auto rotate = MoveBy::create(0, Point(dx * BLOCK_SIZE, dy * BLOCK_SIZE));
        board[cy][cx].state = BoardInfo::fallingblock;
        board[cy][cx].p_sprite->runAction(rotate);
    }
    rotateidx += 1;
    rotateidx %= 4;
}
