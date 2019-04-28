#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
struct window_camera_properties
{

    window_camera_properties(int w,int h,float fovc,bool vsync,string prog)
    {
        width=w;
        height=h;
        fov=fovc;
        use_vsync=vsync;
        program_name=prog;

    }
    window_camera_properties() //default settings
    {
        width=500;
        height=500;
        fov=100;
        use_vsync=true;
        program_name="program";
    }
    int get_width()
    {
        return width;
    }
    void set_width(int x)
    {
        width=x;
    }
    int get_height()
    {
        return height;
    }
    void set_height(int x)
    {
        height=x;
    }
    float get_fov()
    {
        return fov;
    }
    void set_fov(float a)
    {
        fov=a;
    }
    bool do_use_vsync()
    {
        return use_vsync;
    }
    void set_vsync(bool f)
    {
        use_vsync=f;
    }
    string get_title()
    {
        return program_name;
    }
    void set_title(string a)
    {
        program_name=a;
    }
private:
    int width;
    int height;
    float fov;
    bool use_vsync;
    string program_name;

};
class ConfigParser
{
public:
    ConfigParser(string path_to_config);
    virtual ~ConfigParser();
    window_camera_properties Get_parsed();
protected:
private:
    window_camera_properties w_properties;
    void parse(string path);

};

#endif // CONFIGPARSER_H
