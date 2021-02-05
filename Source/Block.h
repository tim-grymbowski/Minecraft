#pragma once

class Block
{
private:
    int block_type;
    int block_code;
public:
    Block();
    Block(int t, int c);

    int GetType();
    int GetCode();

    void SetType(int t);
    void SetCode(int c);
};
