// updated Thu Apr 25 21:55:15 PDT 2019

#include "Circle.h"
#include <cassert>

Circle::Circle(double red, double green, double blue)
  : Game_object(red, green, blue, gamelang::CIRCLE), m_quadric(nullptr)
{
  Register("radius",10);
  //Deregister("h");
  //Deregister("w");

  // the width and height are derived from the radius
  attribute<int>("h")=attribute<int>("w")=object_width=object_height=2*attribute<int>("radius");
}

void Circle::updated(const std::string& name)
{
  //if "w" or "h" changes, immediately overwrite them
  //because in this derived class, w & h are derived from other values
  if (name == "radius")
  {
    attribute<int>("h")=attribute<int>("w")=object_width=object_height=2*attribute<int>("radius");
  }
  m_display_list_dirty = true;
}

void Circle::build_display_list()
{
  assert(m_display_list);
  if (m_quadric == nullptr)
  {
    m_quadric = gluNewQuadric();
    gluQuadricDrawStyle(m_quadric, GLU_FILL);
  }
  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(attribute<int>("x") + attribute<int>("radius"), attribute<int>("y") + attribute<int>("radius"), 0);
  glColor3f(attribute<double>("red"), attribute<double>("green"), attribute<double>("blue"));
  gluDisk(m_quadric,
      /* innerRadius = */ 0,    // creates a hole in center
      /* outerRadius = */ attribute<int>("radius"),
      /* slices = */ 200, // use to be 20
      /* rings = */ 1
      );
  glPopMatrix();
  glEndList();

  // width and height are derived from the radius
  attribute<int>("h")=attribute<int>("w")=object_width=object_height=2*attribute<int>("radius");
}
