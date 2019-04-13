#ifndef SKYBOX_H
#define SKYBOX_H
#include"../Texture/Texture3d.h"
#include"../Mesh/Mesh.h"
class Skybox
{
public:
    Skybox(ShaderProgram&shaderprog,Texture3d&skybox_texture);
    virtual ~Skybox();
    Mesh mesh;
protected:
private:
};

#endif // SKYBOX_H
