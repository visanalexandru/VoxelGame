#include"ChunkConstants.h"
const bool ChunkConstants::transparency[5]
{
    true,
    false,
    false,
    false,
    true
};
const bool ChunkConstants::can_be_hit[5]
{
    false,
    true,
    true,
    true,
    false
};
bool ChunkConstants::is_block_transparent(BlockId block)
{
    int index=(int)block;
    return transparency[index];
}
bool ChunkConstants::can_block_be_hit(BlockId block)
{
    return can_be_hit[(int)block];

}
bool ChunkConstants::is_inside(int yposition)
{
    return yposition>=0 && yposition<chunk_heigth;
}
