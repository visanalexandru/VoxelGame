#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#include "../Engine/Drawable/Drawable2d.h"
class Crosshair:public Drawable2d
{
public:
    Crosshair(const ShaderProgram&prog,const Texture2d&tex,glm::vec2 postion,glm::vec2 size);
    virtual ~Crosshair();
protected:
    void create_data();
private:
};

#endif // CROSSHAIR_H
