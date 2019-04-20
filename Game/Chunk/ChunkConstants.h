#ifndef CHUNKCONSTANTS_H
#define CHUNKCONSTANTS_H
#include<iostream>
typedef uint8_t byte;
enum class BlockId:byte
{
    Air_block=0,
    Dirt_block=1,
    Stone_block=2,
    Sand_block=3,
    Water_block=4
};
class ChunkConstants
{
public:
    static const int chunk_width=16;
    static const int chunk_heigth=254;
    static bool is_block_transparent(BlockId block);
    static bool can_block_be_hit(BlockId block);
    static bool is_inside(int yposition);
private:
    static const bool transparency[5];
    static const bool can_be_hit[5];
};
#endif // CHUNKCONSTANTS_H
