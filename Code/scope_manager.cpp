#include "scope_manager.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>

Scope_manager::Scope_manager(){
    tables.push_back(std::make_unique<Symbol_table>());
}

Scope_manager& Scope_manager::instance(){
    static Scope_manager instance;
    return instance;
}

void Scope_manager::push_table(){
    tables.push_back(std::make_unique<Symbol_table>());
}

void Scope_manager::pop_table(){
    if(tables.size() == 1){
        throw std::underflow_error("Can't pop global symbol table!");
    }else{
        tables.pop_back();
    }
}

bool Scope_manager::add_to_current_scope(Symbol* sym){
    bool test = tables[tables.size()-1]->insert(sym);
    return test;
}

Symbol* Scope_manager::lookup(const std::string& name){
    for(int i = tables.size() - 1; i >= 0; i--){
        Symbol* sym = tables[i]->lookup(name);
        if(sym != nullptr){
            return sym;
        }
    }
    return nullptr;
}

bool Scope_manager::defined_in_current_scope(const std::string& name){
   Symbol* sym = tables[tables.size()-1]->lookup(name);
   if(sym != nullptr){
    return true;
   }
   return false;
}

std::ostream& operator<<(std::ostream& os, const Scope_manager& sh){
    for(int i = sh.tables.size() - 1; i >= 0; i--){
       os << *sh.tables[i];
    }
    return os;
}