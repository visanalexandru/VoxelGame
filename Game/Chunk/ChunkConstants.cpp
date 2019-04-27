#include"ChunkConstants.h"
const bool ChunkConstants::transparency[ChunkConstants::how_many_blocks]
{
    true,
    false,
    false,
    false,
    true,
    false,
    true,
    false,
    false
};
const bool ChunkConstants::can_be_hit[ChunkConstants::how_many_blocks]
{
    false,
    true,
    true,
    true,
    false,
    true,
    true,
    true,
    true
};
const bool ChunkConstants::does_collide[ChunkConstants::how_many_blocks]
{
    false,
    true,
    true,
    true,
    false,
    true,
    true,
    true,
    true
};
bool ChunkConstants::can_collide(BlockId block)
{
    return does_collide[(int)block];
}
bool ChunkConstants::is_block_transparent(BlockId block)
{
    int index=(int)block;
    return transparency[index];
}
bool ChunkConstants::is_inside(int x,int y,int z)
{
    return x>=0 &&x<chunk_width &&z>=0 && z<chunk_width && is_inside(y);

}
bool ChunkConstants::can_block_be_hit(BlockId block)
{
    return can_be_hit[(int)block];

}
bool ChunkConstants::is_inside(int yposition)
{
    return yposition>=0 && yposition<chunk_heigth;
}
