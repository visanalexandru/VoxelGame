#ifndef CHUNKCONSTANTS_H
#define CHUNKCONSTANTS_H
#include<iostream>
typedef uint8_t byte;
class ChunkConstants
{
public:
    static const int chunk_width=16;
    static const int chunk_heigth=255;
};
enum class BlockId:byte
{
    Air_block=0,
    Dirt_block=1,
    Stone_block=2,
};
#endif // CHUNKCONSTANTS_H
