// updated Mon Apr 15 17:26:13 PDT 2019

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Game_object.h"
#include <string>

#include <GL/gl.h>
#include <GL/freeglut.h>


class Textbox : public Game_object
{
  public:
    Textbox(double red = 0.0, double green = 0.0, double blue = 0.0);

    Textbox(const Textbox &) = delete;
    const Textbox &operator=(const Textbox &) = delete;
  private:
    virtual void build_display_list();

    GLUquadricObj *m_quadric;
};

#endif // #ifndef TEXTBOX_H
