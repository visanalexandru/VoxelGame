#ifndef HEIGHTMAP3D_H
#define HEIGHTMAP3D_H
#include"../Chunk/ChunkConstants.h"
#include<iostream>
template<class datatype>
class Heightmap3d
{
public:
    Heightmap3d();
    virtual ~Heightmap3d();
    datatype get_value_at(int x,int y,int z) const;
    void set_value_at(int x,int y,int z,datatype value);
protected:

private:
    datatype values[ChunkConstants::chunk_heigth][ChunkConstants::chunk_width][ChunkConstants::chunk_width];
};
template<class datatype>
Heightmap3d<datatype>::Heightmap3d()
{

}
template<class datatype>
datatype Heightmap3d<datatype>::get_value_at(int x,int y,int z) const
{
    return values[y][x][z];

}
template<class datatype>
void Heightmap3d<datatype>::set_value_at(int x,int y,int z,datatype value)
{
    values[y][x][z]=value;

}
template<class datatype>
Heightmap3d<datatype>::~Heightmap3d()
{

}
#endif // HEIGHTMAP3D_H
