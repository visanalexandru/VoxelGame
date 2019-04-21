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
    Water_block=4,
    Wood_block=5,
    Leaf_block=6
};
class ChunkConstants
{
public:
    static const int chunk_width=16;
    static const int chunk_heigth=254;
    static const int tree_height=5;
    static const int tree_crown_diameter=2;
    static bool is_block_transparent(BlockId block);
    static bool can_block_be_hit(BlockId block);
    static bool is_inside(int yposition);
    static bool is_inside(int x,int y,int z);
private:
    static const bool transparency[7];
    static const bool can_be_hit[7];
};
#endif // CHUNKCONSTANTS_H
