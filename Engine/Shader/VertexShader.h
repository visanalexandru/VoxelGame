#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include"Shader.h"

class VertexShader:public Shader
{
public:
    VertexShader();
    virtual ~VertexShader();
    void load_shader(std::string path) override;
protected:

private:
    void check_for_shader_compilation_succes(std::string path) const;

};

#endif // VERTEXSHADER_H
