#include<iostream>
#include <cstdlib>
#include "Statement.h"
#include "Constant.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Variable.h"
#include "Window.h"
#include "Event_manager.h"

void Statement::append_statement(Statement* atend)
{
  Statement* current=this;
  while(current->next != nullptr)
    current=current->next;
  current->next=atend;
}

Print_statement::~Print_statement(){
  delete argument;
}

void Print_statement::execute() const { 
  std::cout << "print[" << line_number << "]: ";
   
  if(argument == nullptr){
      std::cerr << "Error: Argument is null" << std::endl;
      return;
  }
  const Constant* result = argument->evaluate();

  if(result == nullptr) {
    std::cerr << "Error: Evaluation result is null" << std::endl;
    return;
  }

  std::cout << result->as_string();
  std::cout << std::endl;
  //THE LAST LINE OF EVERY EXECUTE MUST BE
  if(next!=nullptr){                    //
    next->execute();                    //
  }                                     //
  ////////////////////////////////////////
}

//##
// NullStatement
//##
void NullStatement::execute() const
{
}

Assign::~Assign() {
  delete r; // Release rhs
  delete lhs; // Release lhs
}

void Assign::execute() const  {

  std::unique_ptr<Locator> lvalue = lhs->modify();
  const Constant* constant = r->evaluate();
  //const Constant* constant = r->evaluate(lvalue->index());
  //const Constant* lvalue_int = 
  //std::cerr << "Evaluating r: " << constant->as_int() << " for LHS: " << lhs->symbol_name << std::endl;
  switch (lvalue->type()) {
    case gamelang::Type::INT:
      lvalue->mutate(constant->as_int());
      break;
    case gamelang::Type::DOUBLE:
      lvalue->mutate(constant->as_double());
      break;
    case gamelang::Type::STRING:
      lvalue->mutate(constant->as_string());
      break;
    default:
      assert(false);
  }

  if(next!=nullptr){                    
    next->execute();                    
  }    

}

Assign_plus::~Assign_plus() {
  delete r; // Release r
  delete lhs; // Release lhs
}

void Assign_plus::execute() const  {

  std::unique_ptr<Locator> lvalue = lhs->modify();
  const Constant* constant = r->evaluate();
  //const Constant* constant = r->evaluate(lvalue->index());
  //const Constant* lvalue_int = 
  //std::cerr << "Evaluating r: " << constant->as_int() << " for LHS: " << lhs->symbol_name << std::endl;
  switch (lvalue->type()) {
    case gamelang::Type::INT:
    //std::cerr << "lhs->evaluate()->as_int() = " << lhs->evaluate()->as_int() << "||||||||| " << " constant->as_int()" << constant->as_int() << std::endl;
      lvalue->mutate(lhs->evaluate()->as_int() + constant->as_int());
      break;
    case gamelang::Type::DOUBLE:
      //std::cerr << "lhs->evaluate()->as_double() = " << lhs->evaluate()->as_double() << "||||||||| " << " constant->as_double()" << constant->as_double() << std::endl;

      lvalue->mutate(lhs->evaluate()->as_double() + constant->as_double());
      break;
    case gamelang::Type::STRING:
      //std::cerr << "lhs->evaluate()->as_string() = " << lhs->evaluate()->as_string() << "||||||||| " << " constant->as_string()" << constant->as_string() << std::endl;
      lvalue->mutate(lhs->evaluate()->as_string() + constant->as_string());
      break;
    default:
      assert(false);
  }

  if (next != nullptr) {
    //std::cerr << "Executing next at address: " << next << std::endl;
    next->execute();
}  

}


Assign_minus::~Assign_minus() {
  delete r; // Release r
  delete lhs; // Release lhs
}

void Assign_minus::execute() const  {

  std::unique_ptr<Locator> lvalue = lhs->modify();
  const Constant* constant = r->evaluate();
  switch (lvalue->type()) {
    case gamelang::Type::INT:
      lvalue->mutate(lhs->evaluate()->as_int() - constant->as_int());
      break;
    case gamelang::Type::DOUBLE:
      if(constant->type() == gamelang::INT){
        lvalue->mutate(lhs->evaluate()->as_double() - constant->as_int());
      }else if(constant->type() == gamelang::DOUBLE){
        lvalue->mutate(lhs->evaluate()->as_double() - constant->as_double());
      }
      break;
    default:
      assert(false);
  }

  if (next != nullptr) {
    //std::cerr << "Executing next at address: " << next << std::endl;
    next->execute();
}  

}



PlusPlus::~PlusPlus() {
  delete lhs; // Release lhs
}

void PlusPlus::execute() const  {

  std::unique_ptr<Locator> lvalue = lhs->modify();
  switch (lvalue->type()) {
    case gamelang::Type::INT:
      lvalue->mutate(lhs->evaluate()->as_int() +1);
      break;
    case gamelang::Type::DOUBLE:
      lvalue->mutate(lhs->evaluate()->as_double() + 1);
      break;
    default:
      assert(false);
  }

  if (next != nullptr) {
    next->execute();
}  

}

MinusMinus::~MinusMinus() {
  delete lhs; // Release lhs
}

void MinusMinus::execute() const  {

  std::unique_ptr<Locator> lvalue = lhs->modify();
  switch (lvalue->type()) {
    case gamelang::Type::INT:
      lvalue->mutate(lhs->evaluate()->as_int() - 1);
      break;
    case gamelang::Type::DOUBLE:
      lvalue->mutate(lhs->evaluate()->as_double() - 1);
      break;
    default:
      assert(false);
  }

  if (next != nullptr) {
    next->execute();
}  

}

If::~If() {
  delete if_stmt; 
  delete else_stmt;
  delete exp;
}

void If::execute() const  {

  const Constant* condition = exp->evaluate();
  /*std::cerr << "condition = " << condition << std::endl;
  std::cerr << "condition->as_int() = " << condition->as_int() << std::endl;
  std::cerr << "exp->evaluate()->as_int() = " << exp->evaluate()->as_int() << std::endl;*/
  
  if(condition->as_int() != 0){
    if_stmt->execute();
  }else if(else_stmt != nullptr){
    else_stmt->execute();
  }

  if (next != nullptr) {
      next->execute();
  }  

  

}

For::~For() {
  delete initializer; 
  delete condition;
  delete incrementor;
  delete body;
}


void For::execute() const {
  assert(initializer != nullptr);
    assert(condition != nullptr);
    assert(incrementor != nullptr);
    assert(body != nullptr);
  initializer->execute();
  /*std::cerr << "initializer: " << initializer << std::endl;
  std::cerr << "incrementor: " << incrementor << std::endl;
  std::cerr << "condition = " << condition->evaluate()->as_int() << std::endl;*/
  //std::cerr << "body: " << 
  while(condition->evaluate()->as_int() != 0){
    body->execute();
    incrementor->execute();
  }

  if (next != nullptr) {
      next->execute();
  }  
}

Exit::~Exit() {
  delete status; 
}

void Exit::execute() const {
 
  const Constant* status_constant = status->evaluate();
  int status_int = status_constant->as_int();
  //std::cout << "exit(" << status << ")" << std::endl;
  std::cout << "gpl[" << line_number << "]: exit(" << status_int << ")" << std::endl;

  exit(status_int);

  if (next != nullptr) {
      next->execute();
  } 
}
