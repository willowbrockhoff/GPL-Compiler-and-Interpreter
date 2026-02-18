// updated Mon Apr 15 17:28:55 PDT 2019

/*
  Pixmap provide an encapsulation for bitmaps.
  To create a pixmap, pass a filename to the constructor.
  The file will be read and the data stored in the Pixmap object.

  In order to provide simple bitmap animation, the file associated with a
  pixmap can be change.  Consider an animation of a stick figure walking.
  The animation can be achieved by having four different pixmaps and cycling
  through them.  Class Pixmap implements this with using the gpl
  attribute mechanism:  my_pixmap.filename = "person_2.bmp"

  The next time my_pixmap is drawn, the new bitmap will be used.

  In order to reduce run-time, a cache of all pixmaps used since program
  start up is kept.

  LIMITATIONS:
    Only works for pixmaps with 1 plane and 24 bits per plane
*/

#ifndef PIXMAP_H
#define PIXMAP_H

#include "Game_object.h"

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#include <string>
#include <map>
#include <memory>


class Pixmap : public Game_object
{
  public:
    Pixmap();
    void draw();
    static const unsigned char ALPHA_BLUE = 255;
    static const unsigned char ALPHA_GREEN = 0;
    static const unsigned char ALPHA_RED = 255;

    Pixmap(const Pixmap &) = delete;
    const Pixmap &operator=(const Pixmap &) = delete;
  private:

    class Pixmap_data
    {
      public:
        unsigned long m_width;
        unsigned long m_height;
        unsigned char *m_data;
        Pixmap_data(unsigned long width,
              unsigned long height,
              unsigned char *data)
          :m_width(width), m_height(height), m_data(data) { }
    };
    static std::shared_ptr<Pixmap_data> default_pixmap_data;
    static std::map<std::string, std::shared_ptr<Pixmap_data>> m_pixmap_cache;

    std::shared_ptr<Pixmap_data> m_pixmap_data;

    bool m_tried_to_read_current_file;

    void read_file();
    void build_display_list();
    void updated(const std::string& name);
};

#endif
