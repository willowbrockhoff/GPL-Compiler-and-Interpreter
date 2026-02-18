// updated Sun 10 May 2020 05:26:27 PM PDT


#include <cassert>
#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <memory>
#include "Game_object.h"
#include "Animation_code.h"
#include "error.h"
using std::string;


//Map of C++ type to gamelang::Type
/* static */  std::unordered_map<std::type_index, gamelang::Type> Prop::typemap {
    {std::type_index(typeid(int)),                   gamelang::INT},
    {std::type_index(typeid(std::string)),           gamelang::STRING},
    {std::type_index(typeid(double)),                gamelang::DOUBLE},
    {std::type_index(typeid(Animation_code*)),       gamelang::ANIMATION_BLOCK},
    {std::type_index(typeid(const Animation_code*)), gamelang::ANIMATION_BLOCK},
};

// all game objects that have been created but not deleted
// used for drawing all game objects
/* static */ std::set<Game_object*, Game_object::compare_by_drawing_order> Game_object::all_game_objects;
/* static */ unsigned int Game_object::serial_number_dispenser=0;



/* static */ bool Game_object::graphics_dirty = true;


void Game_object::updated(const std::string& name) 
{
  if(name=="h")
    read_attribute("h", object_height);
  if(name=="w")
    read_attribute("w", object_width);
  m_display_list_dirty = true;
}


/* static */ bool Game_object::graphics_out_of_date_with_last_rendering()
{
  bool result = graphics_dirty;
  graphics_dirty = false;
  return result;
}

/* static */ void Game_object::animate_all_game_objects()
{
  for(Game_object* obj : all_game_objects)
      obj->animate();
}

/* static */ void Game_object::draw_all_game_objects()
{
  for(Game_object* obj : all_game_objects)
    obj->draw();
}

Game_object::Game_object(double red /* =  0.5 */,
    double green /* = 0.5 */,
    double blue /* =  0.5 */,
    gamelang::Type got) :
    m_display_list(0),
    m_display_list_dirty(true),
    object_height(10),
    object_width(10),
    serial_number(++serial_number_dispenser)
{
  Register("x",              0);
  Register("y",              0);
  Register("w",              10);
  Register("h",              10);
  Register("red",            red);
  Register("green",          green);
  Register("blue",           blue);
  //Specify type directly to eliminate nullptr ambiguity
  Register("animation_block", new Animation_code("NULL", got));
  Register("visible",        1);
  Register("proximity",      4);
  Register("drawing_order",  0);
  Register("user_int",       0);
  Register("user_double",  0.0);
  //option (1) for coping with const char* vs std::string
  Register<std::string> ("user_string",   "");
  Register("user_int2",      0);
  Register("user_double2", 0.0);
  //option (2) for coping with const char* vs std::string
  Register("user_string2",  std::string());
  Register("user_int3",      0);
  Register("user_double3", 0.0);
  Register("user_string3",  std::string());
  Register("user_int4",      0);
  Register("user_double4", 0.0);
  Register("user_string4",  std::string());
  Register("user_int5",      0);
  Register("user_double5", 0.0);
  Register("user_string5",  std::string());

  all_game_objects.insert(this);
}


Game_object::~Game_object()
{
  all_game_objects.erase(this);
}

void Game_object::draw()
{
  if (attribute<int>("visible")==false)
    return;
  if (m_display_list_dirty)
  {
    if (m_display_list == 0)
      m_display_list = glGenLists(1);

    build_display_list();
    m_display_list_dirty = false;
  }
  //   it might be more efficient to move the translation for m_x and m_y
  //   out of the display list
  //   a) if most objects move, it will probably be faster to take it out of
  //      the display list
  //   b) if most objects don't move, it will be faster to leave it in
  //   unclear if there is an efficiency problem...

  glCallList(m_display_list);
}

static bool overlap(int ax1, int ay1, int ax2, int ay2,
    int bx1, int by1, int bx2, int by2)
{
  return !(ax2 < bx1 || ax1 > bx2 || ay1 > by2 || ay2 < by1);
}

// since gpl does not have a bool, touches() and near() return an int to reduce
// confusion between ints and bools
int Game_object::touches(const Game_object *obj) const
{

  /*****
    LIMITATION

    touches uses the bounding box of the object which is created at object
    construction.

    The bounding box is not a very good representation of triangles or circles.
    And it does not take into account the rotation of either triangles
    or rectangles.

    It would make the touches mechanism better if objects were represented
    with a more accurate boundary.

    Idea 1:  use a polygon to represent the bounding boxes.  Each type of
    object could create and update their polygon.  When line segments of the
    polygons of two objects intersect the two objects would be considered touching.
    This approach does not handle containment (when one object is completely
    inside another).

    Idea 2: represent each object as a set of triangles.  When segments of
    triangles of two objects intersect, the objects touch.  Could also look
    for a vertex inside of another object's triangle.
   *****/


  // true if the bounding boxes of this and obj overlap
  auto x=attribute<int>("x");
  auto y=attribute<int>("y");
  
  auto obj_x=obj->attribute<int>("x");
  auto obj_y=obj->attribute<int>("y");

  return overlap(x,         y,     x +      object_width,     y +      object_height,
                 obj_x, obj_y, obj_x + obj->object_width, obj_y + obj->object_height);
}

int Game_object::near(const Game_object *obj) const
{

  // expand the bounding boxes of this and obj by their respective attribute<int>("proximity")
  // true if the expanded bounding boxes of this and obj overlap
  auto x=attribute<int>("x");
  auto y=attribute<int>("y");
  auto proximity=attribute<int>("proximity");
  
  auto obj_x=obj->attribute<int>("x");
  auto obj_y=obj->attribute<int>("y");
  auto obj_proximity=obj->attribute<int>("proximity");

  return overlap(x     - proximity, 
                 y     - proximity,
                 x     + object_width  + proximity, 
                 y     + object_height + proximity,
                 obj_x - obj_proximity, 
                 obj_y - obj_proximity,
                 obj_x + obj->object_width + obj_proximity,
                 obj_y + obj->object_height + obj_proximity);
}

void Game_object::animate()
{
  if (attribute<Animation_code*>("animation_block"))
  {
    // Call our own animation block
    // Animation blocks are special type of statement block that ALWAYS
    // contain a pointer to a symbol in the symbol_table that represent
    // a parameter.

    // When this object calls its animation block, it must pass itself
    // <this> to the execute function of the animation_block

    attribute<Animation_code*>("animation_block")->execute(this);
  }
}

// symbol_name should include the [#] for arrays
// for example:  "rects[2]"
// for non-arrays, leave out the [#]
// for example:  "my_rectangle"
std::ostream& operator<<(std::ostream& os, const Game_object& go)
{
  os << std::endl << "{" << std::endl;

  auto iter=go.properties.begin();
  for (; iter != go.properties.end(); iter++)
  {
    string cur_name = iter->first;
    auto cur_member = iter->second.get();

    if (iter != go.properties.begin())
      os << ",\n";
    os << "    " << cur_name << " = ";
    switch (cur_member->GetGPLType())
    {
      case gamelang::INT:
        {
          os << "int(" << go.attribute<int>(cur_name) << ")";
          break;
        }
      case gamelang::DOUBLE:
        {
          os << "double(" << go.attribute<double>(cur_name) << ")";
          break;
        }
      case gamelang::STRING:
        {
          os << "string(\"" << go.attribute<std::string>(cur_name) << "\")";
          break;
        }
      case gamelang::ANIMATION_BLOCK:
        {
            //os << go.attribute<Animation_code*>(cur_name)->get_block_name();
            os << go.attribute<Animation_code*>("animation_block")->get_block_name();
          break;
        }
      default:
        // there is a programming bug if this is ever executed
        assert(false);
    }
  } // for loop iterating through all registered member variables
  os << std::endl << "}";
  return os;
}

