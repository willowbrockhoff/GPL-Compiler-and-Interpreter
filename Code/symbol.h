#ifndef SYMBOL_H
#define SYMBOL_H
#include "types_and_ops.h"
#include "Constant.h"
#include "Game_object.h"
#include "Circle.h"
#include "Pixmap.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Rectangle.h"
#include <string>
#include <cassert>
#include "Locator.h"

class Symbol {

  public:
    Symbol(const std::string& name, double* value); // for double var
    Symbol(const std::string& name, double* value, int count); // for array
    Symbol(const std::string&name, int* value);
    Symbol(const std::string&name, int* value, int count);
    Symbol(const std::string&name, std::string* value);
    Symbol(const std::string&name, std::string* value, int count);
    Symbol(const std::string& name, Circle* value); 
    Symbol(const std::string& name, Circle* value, int count); 
    Symbol(const std::string& name, Rectangle* value); 
    Symbol(const std::string& name, Rectangle* value, int count); 
    Symbol(const std::string& name, Triangle* value); 
    Symbol(const std::string& name, Triangle* value, int count); 
    Symbol(const std::string& name, Pixmap* value); 
    Symbol(const std::string& name, Pixmap* value, int count); 
    Symbol(const std::string& name, Textbox* value); 
    Symbol(const std::string& name, Textbox* value, int count); 



    gamelang::Type get_type() const;
    std::string get_name() const;
    int get_count() const;
    friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
    virtual ~Symbol();
    Symbol(const Symbol&) = delete;
    Symbol& operator=(const Symbol&) = delete;
    const Constant* as_constant() const;          //Symbol value is not an array
    const Constant* as_constant(int index) const; //Symbol value is an array
    const Constant* as_constant(const std::string& attribute_name) const; // non-arrays
    const Constant* as_constant(int index, const std::string& attribute_name) const; // arrays
   
    
    std::unique_ptr<Locator> as_lvalue() const;
    std::unique_ptr<Locator> as_lvalue(int index) const;
    std::unique_ptr<Locator> as_lvalue(const std::string& attribute_name) const;
    std::unique_ptr<Locator> as_lvalue(int index, const std::string& attribute_name) const;

  protected:
    std::string name; 
    gamelang::Type type;
    int count; 
    
    union symbol_type {
      double* double_pointer;
      int* int_pointer;
      std::string* string_pointer;
      symbol_type(double* val) : double_pointer(val) {}
      symbol_type(int* val) : int_pointer(val) {}
      symbol_type(std::string* val) : string_pointer(val) {}


      Circle* circle_pointer;
      Rectangle* rectangle_pointer;
      Triangle* triangle_pointer;
      Pixmap* pixmap_pointer;
      Textbox* textbox_pointer;
      symbol_type(Circle* val) : circle_pointer(val) {}
      symbol_type(Rectangle* val) : rectangle_pointer(val) { }
      symbol_type(Triangle* val) : triangle_pointer(val) {}
      symbol_type(Pixmap* val) : pixmap_pointer(val) {}
      symbol_type(Textbox* val) : textbox_pointer(val) {}

    };
    symbol_type value; // contents of variable
    
};
#endif
