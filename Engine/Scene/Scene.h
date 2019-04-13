#ifndef SCENE_H
#define SCENE_H
#include"../Drawable/Drawable3d.h"
#include<iostream>
#include<vector>
#include"../ShaderProgram/ShaderProgram.h"
#include"../Texture/Texture.h"
class Scene
{
public:
    const Texture&texture_to_bind;
    const ShaderProgram&shader_to_bind;
    Scene(const Texture&a,const ShaderProgram&b);
    virtual ~Scene();
    void add_drawable(const Drawable3d&to_add);
    void bind_resources() const;
    void clear_scene();
    vector<const Drawable3d*>to_draw;
protected:

private:

};

#endif // SCENE_H
