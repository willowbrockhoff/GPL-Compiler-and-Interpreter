#include "Variable.h"
#include "Symbol.h"
#include "Expression.h"
#include "scope_manager.h"
#include "symbol_table.h"
#include "error.h"
#include <iostream>

extern Scope_manager sm;

const Constant* Variable::evaluate() const {
    if(symbol_name == ""){
        return new Integer_constant(0);
    }
    Symbol* sym = sm.lookup(symbol_name);
    if(array_index_expression == nullptr){
        return sym->as_constant();
    }else{
        const Constant* cnst = array_index_expression->evaluate();
        if(sym->as_constant(cnst->as_int()) == nullptr){
            gamelang::error(gamelang::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(cnst->as_int()));
            return sym->as_constant(0);
        }
        return sym->as_constant(cnst->as_int());  
    }
}

std::unique_ptr<Locator> Variable::modify() const {
  assert(symbol_name.empty()==false);
  if(array_index_expression==nullptr)
    return sm.lookup(symbol_name)->as_lvalue();

  int index=std::unique_ptr<const Constant>(array_index_expression->evaluate())->as_int();

  std::unique_ptr<Locator> result=sm.lookup(symbol_name)->as_lvalue(index);
  if(result==nullptr) {
    gamelang::error(gamelang::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(index));
    result=sm.lookup(symbol_name)->as_lvalue(0); //7 not here
  }
  return result;
}

gamelang::Type Variable::type() const {
    if(symbol_name == ""){
        return gamelang::Type::INT;
    }  
    Symbol* sym = sm.lookup(symbol_name);
    return sym->get_type();
 }

const Constant* Member_variable::evaluate() const{
  //assert(false);
    if(symbol_name == ""){
        return new Integer_constant(0);
    }
    Symbol* sym = sm.lookup(symbol_name);
    if(array_index_expression == nullptr){
        //return sym->as_constant(0, attribute_name);
        return sym->as_constant(attribute_name); //WITH THIS
    }else{
   
        const Constant* cnst = array_index_expression->evaluate();
        if(sym->as_constant(cnst->as_int(), attribute_name) == nullptr){
            gamelang::error(gamelang::ARRAY_INDEX_OUT_OF_BOUNDS, full_name(), std::to_string(cnst->as_int()));
            //return sym->as_constant(0);
            return sym->as_constant(0, attribute_name); //WITH THIS
        }
        return sym->as_constant(cnst->as_int(), attribute_name);  
    }
}

std::unique_ptr<Locator> Member_variable::modify() const {
  assert(symbol_name.empty()==false);
  if(array_index_expression==nullptr)
    return sm.lookup(symbol_name)->as_lvalue(attribute_name);

  int index=std::unique_ptr<const Constant>(array_index_expression->evaluate())->as_int();

  std::unique_ptr<Locator> result=sm.lookup(symbol_name)->as_lvalue(index, attribute_name);
  if(result==nullptr) {
    gamelang::error(gamelang::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(index));
    result=sm.lookup(symbol_name)->as_lvalue(0, attribute_name); // 7 not here
  }
  //std::cerr << "Locator: " << symbol_name << "[" << index << "]." << attribute_name << std::endl;

  return result;
}

gamelang::Type Member_variable::type() const {

    if(symbol_name.empty()){
        return gamelang::INT;
    }
    Symbol* sym = sm.lookup(symbol_name);
    
        return sym->as_constant(attribute_name)->type();
}

std::string Member_variable::full_name() const {
    return symbol_name + "." + attribute_name;
}