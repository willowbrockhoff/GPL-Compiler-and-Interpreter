//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <memory>
#include "types_and_ops.h"
class Constant;
class Expression {
  public:
    Expression() = default;
    virtual const Constant* evaluate() const=0;
    virtual gamelang::Type type() const=0;
    virtual ~Expression() = default;
    Expression& operator=(const Expression&) = delete;
  protected:
    Expression(const Expression&) = default;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
  protected:
    std::unique_ptr<const Expression> lhs;
    std::unique_ptr<const Expression> rhs;
};

class Add : public Binary_operator {
  public:
    Add(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Sub : public Binary_operator {
  public:
    Sub(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Mod : public Binary_operator {
  public:
    Mod(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Or : public Binary_operator {
  public:
    Or(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class And : public Binary_operator {
  public:
    And(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class LessEqual : public Binary_operator {
  public:
    LessEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class GreatEqual : public Binary_operator {
  public:
    GreatEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Greater : public Binary_operator {
  public:
    Greater(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Lesser : public Binary_operator {
  public:
    Lesser(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Equal : public Binary_operator {
  public:
    Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class NotEqual : public Binary_operator {
  public:
    NotEqual(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
};

class Neg : public Expression {
  public:
    Neg(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Not : public Expression {
  public:
    Not(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Sin : public Expression {
  public:
    Sin(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Cos : public Expression {
  public:
    Cos(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Tan : public Expression {
  public:
    Tan(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Asin : public Expression {
  public:
    Asin(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Acos : public Expression {
  public:
    Acos(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Atan : public Expression {
  public:
    Atan(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Sqrt : public Expression {
  public:
    Sqrt(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Abs : public Expression {
  public:
    Abs(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Floor : public Expression {
  public:
    Floor(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};

class Rand : public Expression {
  public:
    Rand(const Expression* exp) : exp(exp){};
    virtual const Constant* evaluate() const;
    virtual gamelang::Type type() const;
  private:
    std::unique_ptr<const Expression> exp;
};
#endif
