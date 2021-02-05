#include "./Block.h"


Block::Block()
{
    this->block_type = 0;
    this->block_code = 0;
}

Block::Block(int t, int c)
{
    this->block_type = t;
    this->block_code = c;
}

int Block::GetType()
{
    return this->block_type;
}

int Block::GetCode()
{
    return this->block_code;
}

void Block::SetType(int t)
{
    this->block_type = t;
}

void Block::SetCode(int c)
{
    this->block_code = c;
}
