#include "symbol_table.h"
#include <string>
#include <unordered_map>
#include<vector>
#include<memory>
#include <algorithm>

Symbol* Symbol_table::lookup(const std::string &name){
  auto find = symbols.find(name);
  if(find != symbols.end()){
    return find->second.get();
  }
  return nullptr;
}

bool Symbol_table::insert(Symbol* sym){
  if(symbols.find(sym->get_name()) != symbols.end()){
    return false;
  }
  symbols[sym->get_name()] = std::unique_ptr<Symbol>(sym);
  return true;
}

std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab){
  std::vector<std::pair<std::string, Symbol*>> sorted;
  for(const auto& enter : symtab.symbols){
    sorted.emplace_back(enter.first, enter.second.get());
  }
  std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b){ return a.first < b.first; }); // Sort by name.
  for(const auto& pair : sorted){
    Symbol* sym = pair.second; 
    os << *sym;  
  }
  return os;
}