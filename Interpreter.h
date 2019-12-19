//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW__INTERPRETER_H_
#define EX3_NEW__INTERPRETER_H_
#include <iostream>
#include <cstring>
#include <map>
#include <stack>
#include <queue>
#include <regex>
#include "Expression.h"
class Interpreter {
 public:
  void setVariables(string expression);
  Expression *interpret(string expression);
  void createVars(string expression);
  int getStrength(string oper);
 private:
  bool isOperator(char op);
  bool mathLegality(string(expression));
  bool isVariableExist(string toCheck);
  bool isVariableNameLegal(string expression);
  bool isValueLegal(string expression);
  bool isLegal(string expression); // check parenthesis.
  Expression *fromPostfix(queue<string>);
  map<string, double> variables;
};

class Variable : public Expression {
 public:
  Variable(string name, double value);
  Variable &operator++();
  Variable &operator++(int);
  Variable &operator--();
  Variable &operator--(int);
  Variable &operator+=(double);
  Variable &operator-=(double);
  double calculate() override;
 private:
  string name;
  double value;
};

class Value : public Expression {
 public:
  Value(double val);
  double calculate();
 private:
  double value;
};

//-------------------------------------------------UNARY---------------------------------------------------------


/*
 * class UnaryOperator
 */
class UnaryOperator : public Expression {
 public:
  virtual ~UnaryOperator() override {
    delete (this->exp);
  }
 protected:
  Expression *exp;
};

/*
 * class UPlus
 */
class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *exp);
  double calculate();
};

/*
 * class UMinus
 */
class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *exp);
  double calculate();
};

//-------------------------------------------------BINARY---------------------------------------------------------

/*
 * class BinaryOperator
 */

class BinaryOperator : public Expression {
 public:
  virtual ~BinaryOperator() override {
    delete (this->leftExpression);
    delete (this->rightExpression);
  }
 protected:
  Expression *rightExpression;
  Expression *leftExpression;

};

/*
 * class Plus
 */
class Plus : public BinaryOperator {
 public:
  Plus(Expression *left, Expression *right);
  double calculate();
};

/*
 * class Plus
 */
class Minus : public BinaryOperator {
 public:
  Minus(Expression *left, Expression *right);
  double calculate();
};

/*
 * class Mul
 */
class Mul : public BinaryOperator {
 public:
  Mul(Expression *left, Expression *right);
  double calculate();
};

/*
 * class Div
 */
class Div : public BinaryOperator {
 public:
  Div(Expression *left, Expression *right);
  double calculate();
};
#endif //EX3_NEW__INTERPRETER_H_
