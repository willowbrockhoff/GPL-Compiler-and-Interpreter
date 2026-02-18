#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H
#include "symbol_table.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Scope_manager {
    public:
        Scope_manager();
        static Scope_manager& instance();
        void push_table();
        void pop_table();
        bool add_to_current_scope(Symbol* sym);
        Symbol* lookup(const std::string& name);
        bool defined_in_current_scope(const std::string& name);
        friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sh);
    private:
        std::vector<std::unique_ptr<Symbol_table>> tables;
};
#endif