#ifndef VARIABLE_H
#define VARIABLE_H
#include "Expression.h"
#include "types_and_ops.h"
#include "Symbol.h"
#include <iostream>


class Variable : public Expression {
  public:
    // initialize unused array_index_expression to nullptr
    Variable(const std::string& symbol_name) :
    symbol_name(symbol_name), array_index_expression(nullptr) {}

    // initialize array_index_expression to index_expr
    Variable(const std::string& symbol_name, const Expression* index_expr) :
    symbol_name(symbol_name), array_index_expression(index_expr) {}

    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
    virtual ~Variable()=default;

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;

    virtual std::unique_ptr<Locator> modify() const;

  //protected: //allow derived class access
    std::string symbol_name;
    std::unique_ptr<const Expression> array_index_expression;
};

class Member_variable : public Variable {

  private:
    std::string attribute_name;
    std::unique_ptr<const Expression> array_index_expression;

  public:
   virtual const Constant* evaluate() const override;
   virtual gamelang::Type type() const override;

   virtual std::unique_ptr<Locator> modify() const;
   std::string full_name() const;

  Member_variable(const std::string& symbol_name, const std::string& name) :
    Variable(symbol_name), attribute_name(name), array_index_expression(nullptr) {}

    // initialize array_index_expression to index_expr
  Member_variable(const std::string& symbol_name, const std::string& name, const Expression* index_expr) :
    Variable(symbol_name), attribute_name(name), array_index_expression(index_expr) {}

};


#endif