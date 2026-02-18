// updated Mon Apr 15 17:24:40 PDT 2019

#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include "Game_object.h"

class Circle : public Game_object
{
  public:
    Circle(double red = 0, double green = 0, double blue = 1);
    virtual ~Circle(){}

    Circle(const Circle &) = delete;
    const Circle &operator=(const Circle &) = delete;
  private:
    virtual void updated(const std::string& name);
    virtual void build_display_list();

    GLUquadricObj *m_quadric;
};

#endif // #ifndef CIRCLE_H
