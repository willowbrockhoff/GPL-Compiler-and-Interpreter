#include "symbol.h"
#include "Game_object.h"
#include "Constant.h"
#include<cassert>
#include <iostream>
#include <string>

Symbol::Symbol(const std::string& name, double* value)
  : name(name), type(gamelang::Type::DOUBLE), count(0), value{value} {}
Symbol::Symbol(const std::string& name, double* value, int count)
  : name(name), type(gamelang::Type::DOUBLE), count(count), value{value} {} 
Symbol::Symbol(const std::string& name, int* value)
  : name(name), type(gamelang::Type::INT), count(0), value{value} {}
Symbol::Symbol(const std::string& name, int* value, int count)
  : name(name), type(gamelang::Type::INT), count(count), value{value} {}
Symbol::Symbol(const std::string& name, std::string* value)
  : name(name), type(gamelang::Type::STRING), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, std::string* value, int count)
  : name(name), type(gamelang::Type::STRING), count(count), value{value} {}
Symbol::Symbol(const std::string& name, Circle* value)
  : name(name), type(gamelang::Type::CIRCLE), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, Circle* value, int count)
  : name(name), type(gamelang::Type::CIRCLE), count(count), value{value} {}
Symbol::Symbol(const std::string& name, Rectangle* value)
  : name(name), type(gamelang::Type::RECTANGLE), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, Rectangle* value, int count)
  : name(name), type(gamelang::Type::RECTANGLE), count(count), value{value} {}
Symbol::Symbol(const std::string& name, Triangle* value)
  : name(name), type(gamelang::Type::TRIANGLE), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, Triangle* value, int count)
  : name(name), type(gamelang::Type::TRIANGLE), count(count), value{value} {}
Symbol::Symbol(const std::string& name, Pixmap* value)
  : name(name), type(gamelang::Type::PIXMAP), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, Pixmap* value, int count)
  : name(name), type(gamelang::Type::PIXMAP), count(count), value{value} {}
Symbol::Symbol(const std::string& name, Textbox* value)
  : name(name), type(gamelang::Type::TEXTBOX), count(0), value{value} {} 
Symbol::Symbol(const std::string& name, Textbox* value, int count)
  : name(name), type(gamelang::Type::TEXTBOX), count(count), value{value} {}

Symbol::~Symbol(){
  if (count == 0){
    switch(type){
      case gamelang::Type::DOUBLE: 
        delete value.double_pointer; 
        break;
      case gamelang::Type::INT :
        delete value.int_pointer;
        break;
      case gamelang::Type::STRING:
        delete value.string_pointer;
        break;
      case gamelang::Type::CIRCLE:
        delete value.circle_pointer;
        break;
      case gamelang::Type::RECTANGLE:
        delete value.rectangle_pointer;
        break;
      case gamelang::Type::TRIANGLE:
        delete value.triangle_pointer;
        break;
      case gamelang::Type::PIXMAP:
        delete value.pixmap_pointer;
        break;
      case gamelang::Type::TEXTBOX:
        delete value.textbox_pointer;
        break;
      default :
        assert(false);
    }
  }else{
    switch(type){
      case gamelang::Type::DOUBLE:
        delete[] value.double_pointer;
        break;
      case gamelang::Type::INT:
        delete[] value.int_pointer;
        break;
      case gamelang::Type::STRING:
        delete[] value.string_pointer;
        break;
      case gamelang::Type::CIRCLE:
        delete[] value.circle_pointer;
        break;
      case gamelang::Type::RECTANGLE:
        delete[] value.rectangle_pointer;
        break;
      case gamelang::Type::TRIANGLE:
        delete[] value.triangle_pointer;
        break;
      case gamelang::Type::PIXMAP:
        delete[] value.pixmap_pointer;
        break;
      case gamelang::Type::TEXTBOX:
        delete[] value.textbox_pointer;
        break;
      default :
        assert(false);
    }
  }
}

std::string Symbol::get_name() const{
  return name;
}

gamelang::Type Symbol::get_type() const{
  return type;
}

int Symbol::get_count() const{
  return count;
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym)
{
  if(sym.count == 0){
    switch(sym.type){
      case gamelang::Type::DOUBLE :
        os << "double " << sym.name << " = " << *sym.value.double_pointer << std::endl;
        break;
      case gamelang::Type::INT :
        os << "int " << sym.name << " = " << *sym.value.int_pointer << std::endl;
        break;
      case gamelang::Type::STRING :    //NOT HERE    
        os << "string " << sym.name << " = \"" << *sym.value.string_pointer << "\"" << std::endl;
        break;
      case gamelang::Type::CIRCLE :        
        os << "circle " << sym.name <<  *sym.value.circle_pointer <<  std::endl;
        break;
      case gamelang::Type::RECTANGLE :        
        os << "rectangle " << sym.name <<  *sym.value.rectangle_pointer <<  std::endl;
        break;
      case gamelang::Type::TRIANGLE :        
        os << "triangle " << sym.name <<  *sym.value.triangle_pointer << std::endl;
        break;
      case gamelang::Type::PIXMAP :        
        os << "pixmap " << sym.name <<  *sym.value.pixmap_pointer <<  std::endl;
        break;
      case gamelang::Type::TEXTBOX :        
        os << "textbox " << sym.name <<  *sym.value.textbox_pointer <<  std::endl;
        break;
      default :
        assert(false);
    }
  }else{
    switch(sym.type){
      case gamelang::Type::DOUBLE :
        for(int i = 0; i < sym.count; i++){
          os << "double " << sym.name << "[" << i << "] = " 
             << sym.value.double_pointer[i] << std::endl;
        } 
        break;
       case gamelang::Type::INT :
        for(int i = 0; i < sym.count; i++){
          os << "int " << sym.name << "[" << i << "] = "
             << sym.value.int_pointer[i] << std::endl;
        }
         break;
       case gamelang::Type::STRING :
        for(int i = 0; i < sym.count; i++){
           os << "string " << sym.name << "[" << i << "] = \"" 
              << sym.value.string_pointer[i]  << "\"" << std::endl;
        }
         break;
        case gamelang::Type::CIRCLE :
        for(int i = 0; i < sym.count; i++){
           os << "circle " << sym.name << "[" << i << "]" 
              << sym.value.circle_pointer[i]  << std::endl;
        }
        break;
        case gamelang::Type::RECTANGLE :
        for(int i = 0; i < sym.count; i++){
           os << "rectangle " << sym.name << "[" << i << "]" 
              << sym.value.rectangle_pointer[i]  << std::endl;
        }
        break;
        case gamelang::Type::TRIANGLE :
        for(int i = 0; i < sym.count; i++){
           os << "triangle " << sym.name << "[" << i << "]" 
              << sym.value.triangle_pointer[i]  << std::endl;
        }
        break;
        case gamelang::Type::PIXMAP :
        for(int i = 0; i < sym.count; i++){
           os << "pixmap " << sym.name << "[" << i << "]" 
              << sym.value.pixmap_pointer[i]  << std::endl;
        }
         break;
        case gamelang::Type::TEXTBOX :
        for(int i = 0; i < sym.count; i++){
           os << "textbox " << sym.name << "[" << i << "]" 
              << sym.value.textbox_pointer[i]  << std::endl;
        }
         break;
       default :
         assert(false);
    }
  }
  return os;
}

const Constant* Symbol::as_constant() const{
  if(type == gamelang::Type::DOUBLE){
    return new Double_constant(*value.double_pointer);
  }else if(type == gamelang::Type::INT){
    return new Integer_constant(*value.int_pointer);
  }else if(type == gamelang::Type::STRING){
    return new String_constant(*value.string_pointer);
  }else{
    throw type;
  }
}          

const Constant* Symbol::as_constant(int index) const{
  
  if(index < 0 || index >= count){
    return nullptr;
  }
  if(type == gamelang::Type::DOUBLE){
    return new Double_constant(value.double_pointer[index]);
  }else if(type == gamelang::Type::INT){
    return new Integer_constant(value.int_pointer[index]);
  }else if(type == gamelang::Type::STRING){
    return new String_constant(value.string_pointer[index]);
  }else{
    throw type;
  }
}

const Constant* Symbol::as_constant(const std::string& attribute_name) const{
    
  if(type == gamelang::Type::CIRCLE){
    return new Game_attribute_constant(value.circle_pointer, attribute_name);
  }else if(type == gamelang::Type::RECTANGLE){
    return new Game_attribute_constant(value.rectangle_pointer, attribute_name);
  }else if(type == gamelang::Type::TRIANGLE){
    return new Game_attribute_constant(value.triangle_pointer, attribute_name);
  }else if(type == gamelang::Type::PIXMAP){
    return new Game_attribute_constant(value.pixmap_pointer, attribute_name);
  }else if(type == gamelang::Type::TEXTBOX){
    return new Game_attribute_constant(value.textbox_pointer, attribute_name);
  }else{
    throw type;
  }
} 

const Constant* Symbol::as_constant(int index, const std::string& attribute_name) const{

  if(index < 0 || index >= count){
    return nullptr;
  }  
  if(type == gamelang::Type::CIRCLE){
    return new Game_attribute_constant(&value.circle_pointer[index], attribute_name);
  }else if(type == gamelang::Type::RECTANGLE){
    return new Game_attribute_constant(&value.rectangle_pointer[index], attribute_name);
  }else if(type == gamelang::Type::TRIANGLE){
    return new Game_attribute_constant(&value.triangle_pointer[index], attribute_name);
  }else if(type == gamelang::Type::PIXMAP){
    return new Game_attribute_constant(&value.pixmap_pointer[index], attribute_name);
  }else if(type == gamelang::Type::TEXTBOX){
    return new Game_attribute_constant(&value.textbox_pointer[index], attribute_name);
  }else{
    throw type;
  }

  
}

std::unique_ptr<Locator> Symbol::as_lvalue() const {
    if (type == gamelang::Type::DOUBLE) {
        return std::make_unique<Double_locator>(*value.double_pointer);
    } else if (type == gamelang::Type::INT) {
        return std::make_unique<Integer_locator>(*value.int_pointer);
    } else if (type == gamelang::Type::STRING) {
        return std::make_unique<String_locator>(*value.string_pointer);
    } else {
        throw type;
    }
}

std::unique_ptr<Locator> Symbol::as_lvalue(int index) const {
    if (index < 0 || index >= count) {
        return nullptr;
    }
    if (type == gamelang::Type::DOUBLE) {
        return std::make_unique<Double_locator>(value.double_pointer[index]);
    } else if (type == gamelang::Type::INT) {
        return std::make_unique<Integer_locator>(value.int_pointer[index]);
    } else if (type == gamelang::Type::STRING) {
        return std::make_unique<String_locator>(value.string_pointer[index]);
    } else {
        throw type;
    }
}

std::unique_ptr<Locator> Symbol::as_lvalue(const std::string& attribute_name) const {
    if (type == gamelang::Type::CIRCLE) {
        return std::make_unique<Game_attribute_locator>(value.circle_pointer, attribute_name);
    } else if (type == gamelang::Type::RECTANGLE) {
        return std::make_unique<Game_attribute_locator>(value.rectangle_pointer, attribute_name);
    } else if (type == gamelang::Type::TRIANGLE) {
        return std::make_unique<Game_attribute_locator>(value.triangle_pointer, attribute_name);
    } else if (type == gamelang::Type::PIXMAP) {
        return std::make_unique<Game_attribute_locator>(value.pixmap_pointer, attribute_name);
    } else if (type == gamelang::Type::TEXTBOX) {
        return std::make_unique<Game_attribute_locator>(value.textbox_pointer, attribute_name);
    } else {
        throw type;
    }
}

std::unique_ptr<Locator> Symbol::as_lvalue(int index, const std::string& attribute_name) const {
    if (index < 0 || index >= count) {
        return nullptr;
    }
    if (type == gamelang::Type::CIRCLE) {
        //std::cerr << "AS_LVALUE: INDEX: " << index << ", ATTRIBUTE_NAME: " << attribute_name << "ATTRIBUTE VALUE: " << value.circle_pointer[index] << std::endl;
        return std::make_unique<Game_attribute_locator>(&value.circle_pointer[index], attribute_name);
    } else if (type == gamelang::Type::RECTANGLE) {
        return std::make_unique<Game_attribute_locator>(&value.rectangle_pointer[index], attribute_name);
    } else if (type == gamelang::Type::TRIANGLE) {
        return std::make_unique<Game_attribute_locator>(&value.triangle_pointer[index], attribute_name);
    } else if (type == gamelang::Type::PIXMAP) {
        return std::make_unique<Game_attribute_locator>(&value.pixmap_pointer[index], attribute_name);
    } else if (type == gamelang::Type::TEXTBOX) {
        return std::make_unique<Game_attribute_locator>(&value.textbox_pointer[index], attribute_name);
    } else {
        throw type;
    }
}
