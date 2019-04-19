#include"ChunkConstants.h"
const bool ChunkConstants::transparency[4]
{
    true,
    false,
    false,
    false
};
bool ChunkConstants::is_block_transparent(BlockId block)
{
    int index=(int)block;
    return transparency[index];
}
bool ChunkConstants::is_inside(int yposition)
{
    return yposition>=0 && yposition<chunk_heigth;
}
