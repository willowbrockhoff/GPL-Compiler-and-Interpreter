#ifndef SYMBOL_TABLE 
#define SYMBOL_TABLE
#include "symbol.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include<memory>

class Symbol_table {
  
  public:
    Symbol_table() = default;
    Symbol* lookup(const std::string& name);
    bool insert(Symbol* sym);
    friend std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab);
    Symbol_table(const Symbol_table&) = delete;
    Symbol_table& operator = (const Symbol_table&) = delete;

  private:
    std::unordered_map<std::string, std::unique_ptr<Symbol>> symbols;

};
#endif
