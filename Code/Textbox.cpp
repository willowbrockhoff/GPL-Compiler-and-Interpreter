// Sun 10 May 2020 05:28:29 PM PDT

#include <cassert>
#include "Textbox.h"

Textbox::Textbox(double red, double green, double blue)
  : Game_object(red, green, blue, gamelang::TEXTBOX)
{
  Register<std::string>("text", "");
  Register<double>("size", 0.1);
  Register<int>("spacing", 10);
  attribute<int>("h")=object_height=int(100 * attribute<double>("size")) + 1;
  attribute<int>("w")=read_attribute("spacing", object_width);
}

void Textbox::build_display_list()
{
  assert(m_display_list);

  glNewList(m_display_list, GL_COMPILE);
  glMatrixMode(GL_MODELVIEW);
  glColor3f(attribute<double>("red"), attribute<double>("green"), attribute<double>("blue"));
  double cur_x = attribute<int>("x");

  for(unsigned int i = 0; i < attribute<std::string>("text").length(); i++)
  {
    glPushMatrix();
    glTranslated(cur_x, attribute<int>("y"), 0);
    glScaled(attribute<double>("size"), attribute<double>("size"), 1);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, attribute<std::string>("text")[i]);
    glPopMatrix();
    cur_x += (glutStrokeWidth(GLUT_STROKE_ROMAN,attribute<std::string>("text")[i])+attribute<int>("spacing"))*attribute<double>("size");
  }
  glEndList();


  // update our height & width in case our size has changed
  attribute<int>("h")=object_height= int(100 * attribute<double>("size")) + 1;
  attribute<int>("w")=object_width = int(cur_x) - attribute<int>("x");
}
