#include "NoiseGenerator.h"
#include<iostream>
#include"../../Game/Chunk/ChunkConstants.h"
NoiseGenerator::NoiseGenerator(glm::vec3 pos,float seedy,NoiseParameters params)
{
    //ctor
    seed=seedy;
    xposition=pos.x;
    yposition=pos.z;
    parameters=params;
    generator=SimplexNoise(params.frequency,params.amplitude,params.lacunarity,params.persistence);
    octaves=params.octaves;

}
void NoiseGenerator::generate_heightmap(Heightmap<float>&heightmap,int sizex,float unit)
{
    SimplexNoise noise;
    for(int y=0; y<sizex; y++)
    {
        for(int x=0; x<sizex; x++)
        {
            float offx=(float)x/unit+xposition;
            float offy=(float)y/unit+yposition;
            float noiseresult=get_noise_at(offx,offy);
            heightmap.values[y][x]=noiseresult;

        }

    }

}
void NoiseGenerator::generate_3d_heigthmap(Heightmap3d<BlockId>&h)
{
    std::vector<glm::vec3>trees;
    for(int i=0; i<ChunkConstants::chunk_width; i++)
    {
        for(int k=0; k<ChunkConstants::chunk_width; k++)
        {
            int value=get_noise_at(seed+xposition+k,seed+yposition+i);
            for(int p=ChunkConstants::chunk_heigth-1; p>=0; p--)
            {
                if(p<=value)
                {
                    if(p>30)
                        h.set_value_at(k,p,i,BlockId::Dirt_block);
                    else if(p>20)
                    {
                        h.set_value_at(k,p,i,BlockId::Sand_block);
                    }
                    else
                        h.set_value_at(k,p,i,BlockId::Stone_block);

                }
                else
                {
                    if(p>24)
                        h.set_value_at(k,p,i,BlockId::Air_block);
                    else
                        h.set_value_at(k,p,i,BlockId::Water_block);
                }

            }
            float flora_value=get_flora_at(seed+xposition+k,seed+yposition+i);
            if(value>30 &&flora_value>7)
            {
                trees.push_back(glm::vec3(k,value+1,i));

            }
        }
    }
    generate_trees(trees,h);
}
void NoiseGenerator::generate_trees(std::vector<glm::vec3>&where_to_add_trees,Heightmap3d<BlockId>&h)
{
    Structure_Builder builder(h);
    for(unsigned i=0; i<where_to_add_trees.size(); i++)
    {
        glm::vec3 pos=where_to_add_trees[i];
        builder.add_tree_at(pos.x,pos.y,pos.z);
    }
}
float NoiseGenerator::get_noise_at(float x,float y)
{
    float div=parameters.scale;
    float a=generator.fractal(octaves,x/div/3,y/div/3)*10;
    float b=generator.fractal(octaves,x/div/10,y/div/10)*100;
    b=std::max(b,20.f);
    return a+b;
}
float NoiseGenerator::get_flora_at(float x,float y)
{
    float b=generator.fractal(octaves,x,y)*10;
    return b;
}
NoiseGenerator::~NoiseGenerator()
{
    //dtor
}
