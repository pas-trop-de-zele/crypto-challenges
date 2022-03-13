#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include <iomanip>

class Block
{
    friend std::ostream &operator<<(std::ostream &os, const Block &block);

private:
    unsigned char data[4][4] = {0};

public:
    Block() = default;
    virtual int get(int row, int col) const;
    virtual void set(int row, int col, int val);
    Block(const Block &source);
};

#endif