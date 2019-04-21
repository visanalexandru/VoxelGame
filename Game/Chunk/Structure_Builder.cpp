#include "Structure_Builder.h"
using namespace std;
Structure_Builder::Structure_Builder(Heightmap3d<BlockId>&data_in):data(data_in)
{
    //ctor
}
void Structure_Builder::add_tree_at(int x,int y,int z)
{
    int height=ChunkConstants::tree_height;
    if(ChunkConstants::is_inside(x,y,z))
    {
        for(int i=0; i<height; i++)
        {
            data.set_value_at(x,y+i,z,BlockId::Wood_block);
        }
    }
    int iter=ChunkConstants::tree_crown_diameter;
    int h=y+height;
    while(iter>=0)
    {
        for(int i=-iter; i<=iter; i++)
        {
            for(int k=-iter; k<=iter; k++)
            {
                if(ChunkConstants::is_inside(x+i,y+h,z+k))
                    data.set_value_at(x+i,h,z+k,BlockId::Leaf_block);
            }
        }
        h++;
        iter--;
    }


}
Structure_Builder::~Structure_Builder()
{
    //dtor
}
