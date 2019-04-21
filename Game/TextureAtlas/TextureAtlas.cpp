#include "TextureAtlas.h"
#include<iostream>
glm::vec2 TextureAtlas::get_origin_coords(BlockId block,int face)
{
    switch(block)
    {
    case BlockId::Dirt_block:
        if(face==4)
            return glm::vec2(0,15);
        if(face==5)
            return glm::vec2(2,15);
        return glm::vec2(1,15);
    case BlockId::Stone_block:
        return glm::vec2(3,15);
    case BlockId::Sand_block:
        return glm::vec2(7,15);
    case BlockId::Water_block:
        return glm::vec2(8,15);
    case BlockId::Wood_block:
        return glm::vec2(4,15);
    case BlockId::Leaf_block:
        return glm::vec2(6,15);
    default:
        return glm::vec2(10,10);
    }
}
