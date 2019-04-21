#ifndef STRUCTURE_BUILDER_H
#define STRUCTURE_BUILDER_H
#include"../ChunkData/Heightmap3d.h"
#include"ChunkConstants.h"
class Structure_Builder
{
public:
    Structure_Builder(Heightmap3d<BlockId>&data_in);
    virtual ~Structure_Builder();
    void add_tree_at(int x,int y,int z);
protected:

private:
    Heightmap3d<BlockId>&data;

};

#endif // STRUCTURE_BUILDER_H
