#ifndef STATEMENT_H
#define STATEMENT_H

class Expression;
class Variable;
class Statement {
  public:
    void append_statement(Statement* atend);
    Statement() {}
    virtual void execute() const=0;
    virtual ~Statement() {delete next;}
  //protected:
    Statement* next{nullptr};
};

//##
// NullStatement
//##
class NullStatement : public Statement {
  public:
    NullStatement(){}
    virtual void execute() const;
};

class Print_statement : public Statement {
  public: 
    Print_statement(int line_number, const Expression* argument) : line_number(line_number), argument(argument){}
    virtual void execute() const;
    virtual ~Print_statement();
  private:
    int line_number;
    const Expression* argument;
};

class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* r) : lhs(lhs), r(r){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* r;
}; 

class Assign_plus : public Statement {
  public:
    Assign_plus(const Variable* lhs, const Expression* r) : lhs(lhs), r(r){}
    virtual void execute() const;
    virtual ~Assign_plus();
  private:
    const Variable* lhs;
    const Expression* r;
};

class Assign_minus : public Statement {
  public:
    Assign_minus(const Variable* lhs, const Expression* r) : lhs(lhs), r(r){}
    virtual void execute() const;
    virtual ~Assign_minus();
  private:
    const Variable* lhs;
    const Expression* r;
};

class PlusPlus : public Statement {
  public:
    PlusPlus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~PlusPlus();
  private:
    const Variable* lhs;
};

class MinusMinus : public Statement {
  public:
    MinusMinus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~MinusMinus();
  private:
    const Variable* lhs;
};

class If : public Statement {
  public: 
    If(const Expression* exp, const Statement* if_stmt) 
      : exp(exp), if_stmt(if_stmt), else_stmt(nullptr){}
    If(const Expression* exp, const Statement* if_stmt, const Statement* else_stmt) 
      : exp(exp), if_stmt(if_stmt), else_stmt(else_stmt){}
    virtual void execute() const;
    virtual ~If();
  private: 
    const Expression* exp;
    const Statement* if_stmt;
    const Statement* else_stmt;

};

class For : public Statement {
  public: 
    For(const Statement* initializer, const Expression* condition, 
        const Statement* incrementor, const Statement* body)
        : initializer(initializer), condition(condition), 
          incrementor(incrementor), body(body) {}
    virtual void execute() const;
    virtual ~For();
  private: 
    const Statement* initializer;
    const Expression* condition;
    const Statement* incrementor;
    const Statement* body;

};

class Exit : public Statement {
  public:
    Exit(int line_number, const Expression* status) : line_number(line_number), status(status){}
    virtual void execute() const;
    virtual ~Exit();
  private:
    int line_number;
    const Expression* status;
};

#endif
