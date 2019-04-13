#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include"Shader.h"

class FragmentShader:public Shader
{
public:
    FragmentShader();
    virtual ~FragmentShader();
    void load_shader(std::string path) override;
protected:

private:
    void check_for_shader_compilation_succes(std::string path) const;

};

#endif // FRAGMENTSHADER_H
