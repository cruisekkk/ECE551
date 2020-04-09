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
  
class PlusExpression : public Expression {
 public:
  Expression * left;
  Expression * right;
  //virtual long get() {return -1;} // 继承后要实现所有母类的抽象方法
  explicit PlusExpression(Expression * a, Expression * b) : left(a), right(b){}; // access member in 
  virtual std::string toString(){
    std::stringstream s;
    std::string str;
    //string str_right;
    s << '(';
    s << left->toString();
    s << ' ';
    s << '+';
    s << ' ';
    s << right->toString();
    s << ')';
    str = s.str();
    //s >> str;
    s.clear();
    return str;
  };
  virtual ~PlusExpression() {
    delete left;
    delete right;
    //delete left;
    //delete right;
  };
};


