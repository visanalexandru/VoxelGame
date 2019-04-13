#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include"../Chunk/ChunkConstants.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class TextureAtlas
{
public:
    static glm::vec2 get_origin_coords(BlockId block,int face);
protected:

private:
};

#endif // TEXTUREATLAS_H
