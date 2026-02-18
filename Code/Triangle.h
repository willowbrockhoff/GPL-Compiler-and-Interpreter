// updated Mon Apr 15 17:27:22 PDT 2019

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Game_object.h"
#include <string>

class Triangle : public Game_object
{
  public:
    Triangle(double red = 0.0, double green = 1.0, double blue = 0.0);

    Triangle(const Triangle &) = delete;
    const Triangle &operator=(const Triangle &) = delete;
  private:
    virtual void updated(const std::string& name);
    virtual void build_display_list();

};

#endif // #ifndef TRIANGLE_H
