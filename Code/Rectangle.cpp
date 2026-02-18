// updated Thu Apr 25 21:55:03 PDT 2019

#include <cassert>
#include <GL/gl.h>
#include "Rectangle.h"

Rectangle::Rectangle(double red, double green, double blue)
  : Game_object(red, green, blue, gamelang::RECTANGLE)
{
  Register("rotation", 0.0);
}

/* virtual */ void Rectangle::build_display_list()
{
  assert(m_display_list);

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  if (attribute<double>("rotation") != 0)
  {
    double center_x = attribute<int>("x") + object_width/2.0;
    double center_y = attribute<int>("y") + object_height/2.0;
    glTranslated(center_x, center_y, 0);
    glRotated(attribute<double>("rotation"), 0, 0, 1);
    glTranslated(-center_x, -center_y, 0);
  }

  glColor3f(attribute<double>("red"), attribute<double>("green"), attribute<double>("blue"));
  glBegin(GL_QUADS);
    glVertex2i(attribute<int>("x"), attribute<int>("y"));
    glVertex2i(attribute<int>("x") + object_width, attribute<int>("y"));
    glVertex2i(attribute<int>("x") + object_width, attribute<int>("y") + object_height);
    glVertex2i(attribute<int>("x"), attribute<int>("y") + object_height);
  glEnd();
  glPopMatrix();
  glEndList();
}
