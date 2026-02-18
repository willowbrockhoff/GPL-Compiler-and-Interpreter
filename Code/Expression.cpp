// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include<string>
#include <cmath>
#include<numbers>
#include<random>
#include<cassert>
using std::string;


const Constant* Add::evaluate() const{
  
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  //std::cerr << "rhs_constant type = " << gamelang::to_string(rht) << std::endl;
  //if(rhs_constant == nullptr){ std::cerr << "NULL RHS ADD" << std::endl; }
  //std::cerr << "trying as int " << rhs_constant->as_int() << std::endl;
  
  if(lht==gamelang::STRING || rht==gamelang::STRING)
    return new String_constant(lhs_constant->as_string() + 
                               rhs_constant->as_string()); // here seg fault
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return new Double_constant(lhs_constant->as_double() + 
                               rhs_constant->as_double());
  return new Integer_constant(lhs_constant->as_int() +     
                              rhs_constant->as_int());
}

gamelang::Type Add::type() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::STRING || rht==gamelang::STRING)
    return gamelang::STRING;
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
}

const Constant* Sub::evaluate() const 
{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  if(lhs->type() == gamelang::Type::STRING && rhs->type() == gamelang::Type::STRING){
    throw std::invalid_argument("Invalid operands -");
  }else if(lhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid left operand -");
  }else if(rhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid right operand -");    
  }
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return new Double_constant(lhs_constant->as_double() - //<--subtraction
                               rhs_constant->as_double());
  return new Integer_constant(lhs_constant->as_int() -     //<--subtraction
                              rhs_constant->as_int());
}

gamelang::Type Sub::type() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::STRING || rht==gamelang::STRING)
    return gamelang::STRING;
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Multiply::evaluate() const{
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  if(lhs->type() == gamelang::Type::STRING && rhs->type() == gamelang::Type::STRING){
    throw std::invalid_argument("Invalid operands *");
  }else if(lhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid left operand *");
  }else if(rhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid right operand *");    
  }
    if(lhs->type()==gamelang::DOUBLE || rhs->type()==gamelang::DOUBLE){
      return new Double_constant(lhs_constant->as_double() * //<--multiply
                               rhs_constant->as_double());
    } 
    return new Integer_constant(lhs_constant->as_int() *     //<--multiply
                              rhs_constant->as_int());
}

gamelang::Type Multiply::type() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
}

const Constant* Divide::evaluate() const{
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  if(lhs->type() == gamelang::Type::STRING && rhs->type() == gamelang::Type::STRING){
    throw std::invalid_argument("Invalid operands /");
  }else if(lhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid left operand /");
  }else if(rhs->type()==gamelang::Type::STRING){
      throw std::invalid_argument("Invalid right operand /");    
  }

  double rhs_val=rhs_constant->as_double();
  if(!gamelang::runtime() && rhs_val==0.0)
  {
    gamelang::error(gamelang::DIVIDE_BY_ZERO_AT_PARSE_TIME);
    return new Integer_constant(0);
  }
  if(lhs->type()==gamelang::DOUBLE || rhs->type()==gamelang::DOUBLE){
    return new Double_constant(lhs_constant->as_double() / //<--divide
                               rhs_constant->as_double());
  } 
  return new Integer_constant(lhs_constant->as_int() /     //<--divide
                              rhs_constant->as_int());
}

gamelang::Type Divide::type() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  if(lht==gamelang::DOUBLE || rht==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
}

const Constant* Or::evaluate() const {
  
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();

  /*if(lht == gamelang::STRING || rht == gamelang::STRING){
    assert(false);
  }*/
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
 
  if(lht == gamelang::DOUBLE || rht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() || rhs_constant->as_double());
  }
  
    return new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int());

}

gamelang::Type Or::type() const{
  
  return gamelang::INT;
}

const Constant* And::evaluate() const 
{


 gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());
  
  int l = -1;
  int r = -1;
  if(lht == gamelang::DOUBLE || rht == gamelang::DOUBLE){
    double dl = lhs_constant->as_double();
    double dr = rhs_constant->as_double();
    return new Integer_constant(dl && dr);
  }
  
    l = lhs_constant->as_int();
    r = rhs_constant->as_int();
    return new Integer_constant(l && r);
 
}

gamelang::Type And::type() const{
  
  return gamelang::INT;
}

const Constant* Mod::evaluate() const 
{
  
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if((lhs->type() == gamelang::Type::STRING || lhs->type() == gamelang::Type::DOUBLE) && 
     (rhs->type() == gamelang::Type::STRING || rhs->type() == gamelang::Type::DOUBLE)){
        throw std::invalid_argument("Invalid operands %");
  }else if(lhs->type()==gamelang::Type::STRING || lhs->type()==gamelang::Type::DOUBLE){
      throw std::invalid_argument("Invalid left operand %");
  }else if(rhs->type()==gamelang::Type::STRING || rhs->type()==gamelang::Type::DOUBLE){
      throw std::invalid_argument("Invalid right operand %");    
  }
  double rhs_val=rhs_constant->as_double();
  if(!gamelang::runtime() && rhs_val==0.0)
  {
  gamelang::error(gamelang::MOD_BY_ZERO_AT_PARSE_TIME);
  return new Integer_constant(0);
  }
  return new Integer_constant(lhs_constant->as_int() %     //<--mod
                              rhs_constant->as_int());
}

gamelang::Type Mod::type() const{
  
  return gamelang::INT;
}

const Constant* LessEqual::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht==gamelang::STRING || rht==gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() <=     //<--divide
                              rhs_constant->as_string());
  }else if(rht == gamelang::DOUBLE || lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() <=     //<--divide
                              rhs_constant->as_double());
  }
  return new Integer_constant(lhs_constant->as_int() <=     //<--divide
                              rhs_constant->as_int());
  

}

gamelang::Type LessEqual::type() const{
 
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* GreatEqual::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht==gamelang::STRING || rht==gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() >=     //<--divide
                              rhs_constant->as_string());
  }else if(rht == gamelang::DOUBLE || lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() >=     //<--divide
                              rhs_constant->as_double());
  }
  return new Integer_constant(lhs_constant->as_int() >=     //<--divide
                              rhs_constant->as_int());
}

gamelang::Type GreatEqual::type() const{
  
  return gamelang::INT;
}

const Constant* Greater::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht==gamelang::STRING || rht==gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() >     //<--divide
                              rhs_constant->as_string());
  }else if(rht == gamelang::DOUBLE || lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() >     //<--divide
                              rhs_constant->as_double());
  }
  return new Integer_constant(lhs_constant->as_int() >     //<--divide
                              rhs_constant->as_int());

}

gamelang::Type Greater::type() const{


  return gamelang::INT;
}

const Constant* Lesser::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht==gamelang::STRING || rht==gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() <     //<--divide
                              rhs_constant->as_string());
  }else if(rht == gamelang::DOUBLE || lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() <     //<--divide
                              rhs_constant->as_double());
  }
  return new Integer_constant(lhs_constant->as_int() <     //<--divide
                              rhs_constant->as_int());
}

gamelang::Type Lesser::type() const{
 
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Equal::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht == gamelang::STRING || rht == gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() == rhs_constant->as_string());
  }
  else if(lht == gamelang::INT && rht == gamelang::INT){
    return new Integer_constant(lhs_constant->as_int() ==     //<--divide
                              rhs_constant->as_int());
  }else if(rht == gamelang::DOUBLE && lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() ==     //<--divide
                              rhs_constant->as_double());
  }else{
    return new Integer_constant(0);
  }

}

gamelang::Type Equal::type() const{
  
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* NotEqual::evaluate() const{
  gamelang::Type lht=lhs->type();
  gamelang::Type rht=rhs->type();
  std::unique_ptr<const Constant> lhs_constant(lhs->evaluate());
  std::unique_ptr<const Constant> rhs_constant(rhs->evaluate());

  if(lht != rht){
    return new Integer_constant(1);
  }else if(rht == gamelang::INT && lht == gamelang::INT){
    return new Integer_constant(lhs_constant->as_int() !=     //<--divide
                              rhs_constant->as_int());
  }else if(rht == gamelang::DOUBLE && lht == gamelang::DOUBLE){
    return new Integer_constant(lhs_constant->as_double() !=     //<--divide
                              rhs_constant->as_double());
  }else if(rht == gamelang::STRING && lht == gamelang::STRING){
    return new Integer_constant(lhs_constant->as_string() !=     //<--divide
                              rhs_constant->as_string());
  }else{
    return new Integer_constant(0);
  }

}

gamelang::Type NotEqual::type() const{
 
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}


const Constant* Neg::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand -");    
  }else if(ext == gamelang::DOUBLE){
    
    double d = exp_constant->as_double();
    return new Double_constant(- d);
  } 
    
    int i = exp_constant->as_int();
    return new Integer_constant(-i
    );
  
  
}

gamelang::Type Neg::type() const{
  gamelang::Type ext=exp->type();
  
  if(ext==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Not::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  if(ext ==gamelang::STRING){
    throw std::invalid_argument("Invalid right operand !");    
  }else if(ext == gamelang::INT){
      if(exp_constant->as_int() == 0){
        return new Integer_constant(1);
      }else if(exp_constant->as_int() == 1){
          return new Integer_constant(0);
      }
  }else{
    if(exp_constant->as_double() == 0.0){
      return new Integer_constant(1);
    }else if(exp_constant->as_double() == 1.0){
      return new Integer_constant(0);    
      }
  }
  return new Integer_constant(0);
   
}

gamelang::Type Not::type() const{
  
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Sin::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand sin");    
  }else{
    if(ext == gamelang::INT){
      double rads = exp_constant->as_int() * (std::numbers::pi / 180.0);
      double result = sin(rads);
      return new Double_constant(result);
    }else{
      double rads = exp_constant->as_double() * (std::numbers::pi / 180.0);
      double result = sin(rads);
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Sin::type() const{
      return gamelang::DOUBLE;

}

const Constant* Cos::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand cos");    
  }else{
    if(ext == gamelang::INT){
      double rads = exp_constant->as_int() * (std::numbers::pi / 180.0);
      double result = cos(rads);
      return new Double_constant(result);
    }else{
      double rads = exp_constant->as_double() * (std::numbers::pi / 180.0);
      double result = cos(rads);
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Cos::type() const{
     return gamelang::DOUBLE;

}

const Constant* Tan::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand tan");    
  }else{
    if(ext == gamelang::INT){
      double rads = exp_constant->as_int() * (std::numbers::pi / 180.0);
      double result = tan(rads);
      return new Double_constant(result);
    }else{
      double rads = exp_constant->as_double() * (std::numbers::pi / 180.0);
      double result = tan(rads);
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Tan::type() const{
      return gamelang::DOUBLE;

}

const Constant* Asin::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  double rads;
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand asin");    
  }else{
    if(ext == gamelang::INT){
      rads = asin(exp_constant->as_int());
    }else{
      rads = asin(exp_constant->as_double());
    }
    double degrees = rads * (180.0 / std::numbers::pi);
    return new Double_constant(degrees);
  }
}

gamelang::Type Asin::type() const{
  
    return gamelang::DOUBLE;
}

const Constant* Acos::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  double rads;
  if(ext ==gamelang::STRING){

      throw std::invalid_argument("Invalid right operand acos");    
  }else{
    if(ext == gamelang::INT){
       rads = acos(exp_constant->as_int());
    }
    else{
       rads = acos(exp_constant->as_double());
    }

    double degrees = rads * (180.0 / std::numbers::pi);
    return new Double_constant(degrees);
  } 
}


gamelang::Type Acos::type() const{
     return gamelang::DOUBLE;

}

const Constant* Atan::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand atan");    
  }else{
    if(ext == gamelang::INT){
      double rads = atan(exp_constant->as_int());
      double result = rads * (180.0 / std::numbers::pi);
      return new Double_constant(result);
    }else{
      double rads = atan(exp_constant->as_double());
      double result = rads * (180.0 / std::numbers::pi);
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Atan::type() const{
      return gamelang::DOUBLE;

}

const Constant* Sqrt::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand sqrt");    
  }else{
    if(ext == gamelang::INT){
      double result = sqrt(exp_constant->as_int());
      return new Double_constant(result);
    }else{
      double result = sqrt(exp_constant->as_double());
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Sqrt::type() const{
  gamelang::Type ext=exp->type();
  if(ext==gamelang::STRING)
    return gamelang::STRING;
  if(ext==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Abs::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext ==gamelang::STRING){
      throw std::invalid_argument("Invalid right operand abs");    
  }else{
    if(ext == gamelang::INT){
      int result = std::abs(exp_constant->as_int());
      return new Integer_constant(result);
    }else{
      double result = std::abs(exp_constant->as_double());
      return new Double_constant(result);
    }
  }
  
  
}

gamelang::Type Abs::type() const{
  gamelang::Type ext=exp->type();
  if(ext==gamelang::STRING)
    return gamelang::STRING;
  if(ext==gamelang::DOUBLE)
    return gamelang::DOUBLE;
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Floor::evaluate() const{
 
  gamelang::Type ext=exp->type();
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  
  if(ext == gamelang::INT){
    int result = std::floor(exp_constant->as_int());
    return new Integer_constant(result);
  }else{
    int result = std::floor(exp_constant->as_double());
    return new Integer_constant(result);
  }
}

gamelang::Type Floor::type() const{
  
  return gamelang::INT;
  //return gamelang::NO_TYPE; //REPLACE THIS. Here to suppress errors.
}

const Constant* Rand::evaluate() const{
 
  
  std::unique_ptr<const Constant> exp_constant(exp->evaluate());
  int top = floor(exp_constant->as_double());
  if(top<2){
    gamelang::error(gamelang::INVALID_ARGUMENT_FOR_RANDOM, exp_constant->as_string());
    top =2;
  }
  return new Integer_constant(rand()%top);  
}

gamelang::Type Rand::type() const{  
  return gamelang::INT;


}
