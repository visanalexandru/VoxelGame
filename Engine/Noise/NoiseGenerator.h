#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#include"SimplexNoise.h"
#include"Heightmap.h"
#include"NoiseParameters.h"
#include"../../Game/ChunkData/Heightmap3d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class NoiseGenerator
{
public:
    NoiseGenerator(glm::vec3 pos,float seedy,NoiseParameters params);
    virtual ~NoiseGenerator();
    void generate_heightmap(Heightmap<float>&heightmap,int sizex,float unit);
    float get_noise_at(float x,float y);
    void generate_3d_heigthmap(Heightmap3d<BlockId>&h);
protected:

private:
    int octaves;
    SimplexNoise generator;
    NoiseParameters parameters;
    float xposition;
    float yposition;
    float seed;
};

#endif // NOISEGENERATOR_H
