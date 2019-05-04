#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
struct program_properties
{

    program_properties(int w,int h,float fovc,bool vsync,string prog)
    {
        width=w;
        height=h;
        fov=fovc;
        use_vsync=vsync;
        program_name=prog;

    }
    program_properties() //default settings
    {
        width=500;
        height=500;
        fov=100;
        use_vsync=true;
        program_name="program";
        port=8000;
        ip="127.0.0.1";
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
    void set_title(string&a)
    {
        program_name=a;
    }
    void set_ip(string&a)
    {
        ip=a;
    }
    string get_ip()
    {
        return ip;
    }
    void set_port(int x)
    {
        port=x;
    }
    int get_port()
    {
        return port;
    }
private:
    int width;
    int height;
    float fov;
    bool use_vsync;
    string program_name;
    string ip;
    int port;

};
class ConfigParser
{
public:
    ConfigParser(string path_to_config);
    virtual ~ConfigParser();
    program_properties Get_parsed();
protected:
private:
    program_properties w_properties;
    void parse(string path);

};

#endif // CONFIGPARSER_H
