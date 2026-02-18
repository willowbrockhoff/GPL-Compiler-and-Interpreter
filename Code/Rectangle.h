// updated Mon Apr 15 17:23:19 PDT 2019

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Game_object.h"

class Rectangle : public Game_object
{
  public:
    Rectangle(double red = 1.0, double green = 0.0, double blue = 0.0);

    // Disable default copy constructor and default assignment
    // This will prevent accidental use.
    Rectangle(const Rectangle &) = delete;
    const Rectangle &operator=(const Rectangle &) = delete;
  private:
    virtual void build_display_list();
};

#endif // #ifndef RECTANGLE_H
