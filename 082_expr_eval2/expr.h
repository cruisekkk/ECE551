#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <sstream>

class Expression {
 public:
  //long numb;
  explicit Expression() {};
  virtual std::string toString() = 0;
  //  virtual long get() = 0;
  virtual ~Expression() {};
  // only method can dynamically dispatched 
};

class NumExpression : public Expression {
 public:
  long numb;
  explicit NumExpression(long num): numb(num){};//function can be without ;
  NumExpression() {};
  //virtual long get(){return numb;}
  virtual std::string toString() {
    std::stringstream s;
    std::string str;
    s << numb;
    s >> str;
    s.clear();    
    return str;
  }; 
  virtual ~NumExpression(){
    //delete numb;
  };
};

class OpExpression : public Expression {
 public:
  Expression * left;
  Expression * right;
  std::string op;
  explicit OpExpression(Expression * a, Expression * b, std::string s) : left(a), right(b), op(s){}; // access member in
  virtual std::string toString(){
    std::stringstream s;
    std::string str;
    //string str_right;
    s << '(';
    s << left->toString() << op << right->toString();
    s << ')';
    str = s.str();
    //s >> str;
    s.clear();
    return str;
  }
  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};
class PlusExpression : public OpExpression {
 public:
  //virtual long get() {return -1;} // 继承后要实现所有母类的抽象方法
  explicit PlusExpression(Expression * a, Expression * b) : OpExpression(a, b, " + "){}

  //virtual ~PlusExpression() {
    //delete left;
    //delete right;
  //}
};

class MinusExpression : public OpExpression {
 public:
  explicit MinusExpression(Expression * a, Expression * b) : OpExpression(a, b, " - "){}
  
  //virtual ~MinusExpression() {}
};

class TimesExpression : public OpExpression {
 public:
  explicit TimesExpression(Expression * a, Expression * b) : OpExpression(a, b, " * "){}
  //virtual ~TimesExpression() {}
};

class DivExpression : public OpExpression {
 public:
  explicit DivExpression(Expression * a, Expression * b) : OpExpression(a, b, " / "){}
  //virtual ~DivExpression() {}
};


