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
                    h.set_value_at(k,p,i,BlockId::Air_block);
                }
            }
        }
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
NoiseGenerator::~NoiseGenerator()
{
    //dtor
}
