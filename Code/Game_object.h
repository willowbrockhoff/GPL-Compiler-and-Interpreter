// Tue Nov  2 05:25:49 PM PDT 2021
// * convert to gamelang::Type
// Mon May 17 09:24:15 PDT 2021
// * added GetGPLType() wrapper to const version of Property::PropertyVal()
// Sun 17 May 2020 12:58:31 AM PDT
// * changed static all_game_objects from a vector to a set
// Thu 07 May 2020 05:59:33 PM PDT
// * Removed list of deleted game objects
// Mon Oct 14 13:01:55 PDT 2019
// * Redesign of dynamic attribute registry
// * removed set_member_variable. Have get_member_variable return member variable by reference
// Mon Apr 22 16:31:13 PDT 2019

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
/****

Introduction:

  class Game_object is a pure virtual base class for all gpl objects such as:

    class Circle : public Game_object
    class Triangle : public Game_object
    class Rectangle : public Game_object

  It provides support for two main parts of a gpl object
    
    1) attribute variables (named variables of type int, double, string)
    2) graphics (animation, drawing, calculations (e.g. touches))

  Users of Game_object (and the classes that inherit it) should focus
  on its public member functions.  In other words, you can use Game_object
  without fully understanding how it works.


Member variables

    Game object attributes in GPL (a triangle's skew, any game object's x & y
    location, etc.) require an equivalent C++ representation. There is no
    simple way to programatically map the string scanned from GPL (e.g.
    mytriangle.skew) to the equivalent private data member in the C++ Triangle
    class. The Computer Science terms for being able to do this are
    "introspection" and "reflection". Some programming languages, such
    as Python do have this ability.

 Solution:

    Function templates and Prop (base) & Property (derived) classes keep a
    registry of variables that can be written/read from GPL.

    This registry is implemented in class Game_object.

  Registry

      The Register() member function maps the name of the variable
      as a string to a dynamically allocated variable. The type of
      the variable is inferred by the type of the value used to
      initialize the registered variable.
  
  Access:
      typename T represents the type of the variable being read/written.


      T& write_attribute(const std::string& name, const T& var)
      T& read_attribute(const std::string& name, T& var)

      Available as a convenience function for accessing registered variables
      T& attribute(const std::string& name)

      Exceptions thrown by read/write functions:
      + if name is unregistered: out_of_range
      + if var doesn't match member type: gamelang::Type of attribute


Graphics

  All graphics are done using OpenGL display lists.

  In order to define the graphics for an object, it must override the
  pure virtual function:
  
      virtual void build_display_list() = 0;

  in this function the graphics should be drawn to the display list
  m_display_list.

  Updating display list
  
    When a member variable is changed, build_display_list() is called before
    the object is redrawn.

    A class can redefine this behavior by providing the following function:

      virtual void updated(string name) {m_display_list_dirty = true;}

    If a member variable is not linked to the graphics, then don't
    mark the display list as dirty when that variable changes

  Drawing order

    By default game objects are drawn in the order in which they are declared.
    The Game_object attribute "drawing_order" can override this specifying the
    object's drawing order.  Game_objects with smaller numbers are drawn before
    Game_objects with larger numbers.  Thus the Game_object with the largest
    drawing_order number is drawn last and will thus appear on top of all other
    game objects.

****/
#include<GL/gl.h>
#include<memory>
#include "types_and_ops.h"

#include <string>
#include <set>
#include <iostream>

#include <unordered_map>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <memory>

///////////////////////////////////////////////////
// Prop
///////////////////////////////////////////////////
//
//Base class for managing dynamic class properties
//
class Prop
{
  private:
    static std::unordered_map<std::type_index, gamelang::Type> typemap;
  protected:
    const std::type_index proptype;
    static gamelang::Type GetGPLType(std::type_index ti)
    { return typemap.at(ti); }
  public:
    gamelang::Type GetGPLType() const
    { return typemap.at(proptype); }

    Prop(const std::type_index& proptype)
      :proptype(proptype)
    {}

    virtual ~Prop()
    { }
};

///////////////////////////////////////////////////
// Property<T>
///////////////////////////////////////////////////
//
//Derived template class. Each object is a property of type
//specified by the template parameter
//
template<typename T>
class Property : public Prop
{
  private:
    T data;
  public:
    virtual ~Property()
    { }

    //"The lifetime of the object returned by typeid extends to the end of the program."
    Property(const T& d)
      : Prop(std::type_index(typeid(T))), data(d) 
    { }

    //If T does not match property type, throw gamelang::Type of property
    T& PropertyVal()
    {
      //Long, sordid tale for why GetGPLType must wrap the operands in the if-statement. 
      //Bottom line: this is the least-painful way to get the const and non-const
      //Animation* to map as equivalent 
      //(T will be const on the rhs of the assign expression).
      //Otherwise would have been: if(std::type_index(typeid(T)) != proptype)
      if(GetGPLType(std::type_index(typeid(T))) != GetGPLType())
        throw GetGPLType();
      return data;
    }
    const T& PropertyVal() const
    {
      //Above note here as well. Because "const" Animation_code* can appear
      //as argument to read_attribute()
      //Otherwise would have been: if(std::type_index(typeid(T)) != proptype)
      if(GetGPLType(std::type_index(typeid(T))) != GetGPLType())
        throw GetGPLType();
      return data;
    }
};

class Animation_code; 

class Game_object
{
  public:
    Game_object(double red, double green, double blue, gamelang::Type got);
    virtual ~Game_object();

    /////////////
    // Register a dynamic property
    /////////////
    template<typename T>
      void Register(const std::string& name, const T& data)
      {
        properties[name] = std::make_unique<Property<T>>(data);
      }

    /////////////
    // Deregister a dynamic property
    /////////////
    void Deregister(const std::string& name)
    {
      properties.erase(name);
    }

    /////////////
    // Return the gamelang::Type of the attribute
    // + Throws out_of_range if name is unregistered 
    /////////////
    gamelang::Type attribute_type(const std::string& name) const
    {
      Prop* p=properties.at(name).get();
      return p->GetGPLType();
    }

    /////////////
    // Assign attribute to var
    // + Throws out_of_range if name is unregistered 
    // + Throws gamelang::Type of attribute if var doesn't match member type
    /////////////
    template<typename T>
      const T& read_attribute(const std::string& name, T& var) const
      {
        const Property<T>* p =
          static_cast<const Property<T>*>(properties.at(name).get());
        return var=p->PropertyVal();
      }

    /////////////
    // Assign var to attribute
    // + Throws out_of_range if name is unregistered 
    // + Throws gamelang::Type of attribute if var doesn't match member type
    /////////////
    template<typename T>
      T& write_attribute(const std::string& name, const T& var)
      {
        if (name == "drawing_order")
          all_game_objects.erase(this);
        Property<T>* p =
          static_cast<Property<T>*>(properties.at(name).get());
        p->PropertyVal()=var;//assign before return statement to support updating the drawing order
        graphics_dirty = true;
        updated(name);
        if (name == "drawing_order")
          all_game_objects.insert(this);
        return p->PropertyVal();
      }

    /////////////
    // Return const attribute
    // + Throws out_of_range if name is unregistered 
    // + Throws gamelang::Type of attribute if var doesn't match member type
  protected:
    template<typename T>
      const T& attribute(const std::string& name) const
      {
        const Property<T>* p = static_cast<const Property<T>*>(properties.at(name).get());
        return p->PropertyVal();
      }

    /////////////
    // Return mutable attribute. 
    // The benefit of this over write_attribute is that it is safe to use
    // inside the virtual updated() function.
    // + Throws out_of_range if name is unregistered 
    // + Throws gamelang::Type of attribute if var doesn't match member type
  protected:
    template<typename T>
      T& attribute(const std::string& name)
      {
        Property<T>* p = static_cast<Property<T>*>(properties.at(name).get());
        return p->PropertyVal();
      }

  public:
    void draw();

    int touches(const Game_object *obj) const;
    int near(const Game_object *obj) const;

    // if no objects have changed, do not draw
    static bool graphics_out_of_date_with_last_rendering();

    // draw all game objects in the set all_game_objects
    static void draw_all_game_objects();

    static void animate_all_game_objects();
    void animate();

    friend std::ostream& operator<<(std::ostream& os, const Game_object& go);

  protected:

    // each object that inherits us must implement build_display_list()
    virtual void build_display_list() = 0;

    // the default is to mark the display list as dirty when any member
    // variable changes. "h" and "w" are written to the protected data
    // members object_height and object_width respectively.
    // Subclasses can redefine this behavior if the
    // display list changes only when some members fields are changed
    virtual void updated(const std::string& name);

  protected:
    GLuint m_display_list;
    bool m_display_list_dirty;
    int  object_height;
    int  object_width;
  private:
    std::map<std::string, std::unique_ptr<Prop>> properties;
    unsigned int serial_number;


    static bool graphics_dirty;

    //This class allows the all_game_objects set to sort by drawing order.
    //The comparison is also used by set to determine uniqueness. That is
    //If two objects have the same drawing order, then they are considered
    //the same in the set (set::insert() will replace the existing object with
    //the new object). The solution to this is to assign each game object
    //a serial number that is used as a secondary sort criteria if the
    //drawing order is the same. The serial number also ensures that 
    //objects are drawn in the order they are declared in the GPL.
    class compare_by_drawing_order {
      public:
        bool operator() (const Game_object* lhs, const Game_object* rhs) const
        { 
          int lhs_order=lhs->attribute<int>("drawing_order");
          int rhs_order=rhs->attribute<int>("drawing_order");
          return lhs_order==rhs_order ? lhs->serial_number < rhs->serial_number : lhs_order < rhs_order;
        }
    };
    static std::set<Game_object *, compare_by_drawing_order> all_game_objects;
    static unsigned int serial_number_dispenser;

    Game_object(const Game_object &) = delete;
    Game_object &operator=(const Game_object &) = delete;

};

#endif // #ifndef GAME_OBJECT_H
