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
//class Interpreter {

  class Interpreter {
   private:
  // variables map
    map<string, double> varMap;
   public:
    /**
     * set variables
     * @param string1 new/updated variables
     *
    */
    void setVariables(string string1);
    /**
     * replace the variables by their value
     * @param str expression string
     * @return expression without variables, type Expression
     */
    Expression *interpret(string str);
    /**
      * get Variable From String
      * @param str string
      * @return Variable
      */
    string getVariableFromStr(string str);
    /**
     * get Value From String
     * @param str string
     * @return value
     */
    double getValueFromStr(string str);
    /**
     * check Variable Vaildation
     * @param tempStr variable
     * @return boolean value - variables validation
    */
    bool checkVariableVaildation(string tempStr);
    /**
     * check value Vaildation
     * @param tempStr value
     * @return boolean value - value validation
     */
    bool checkValueVaildation(string tempStr);
    /**
     * get Value expression
     * @param str Value constructor's argument
     * @return Value expression
     */
    Expression *getValueExp(string str);
    /**
     * get Variable expression
     * @param str Variable constructor's argument
     * @param num Variable constructor's argument
     * @return Variable expression
     */
    Expression *getVariableExp(string str, double num);
  };

  class Value : public Expression {
    double value;

   public:
    // constructor
    Value(double num);
    double calculate() override;
  };
  class Variable : public Expression {
    string name;
    double value;

   public:
    Variable(string name, double num);
    double calculate() override;
    // prefix increment operator
    Variable &operator++();
    // postfix increment operator
    Variable &operator++(int);
    // prefix decrement operator
    Variable &operator--();
    // postfix increment operator
    Variable &operator--(int);
    Variable &operator+=(double num);
    Variable &operator-=(double num);
  };

  class UnaryOperator : public Expression {
   protected:
    Expression *expression{nullptr};
    ~UnaryOperator();
  };

  class UPlus : public UnaryOperator {
   public:
    // constructor
    UPlus(Expression *expression1);
    double calculate() override;
  };

  class UMinus : public UnaryOperator {
   public:
    // constructor
    UMinus(Expression *expression1);
    double calculate() override;
  };

  class BinaryOperator : public Expression {
   protected:

    Expression *left{nullptr};
    Expression *right{nullptr};
    ~BinaryOperator();
  };

  class Plus : public BinaryOperator {
   public:
    // constructor
    Plus(Expression *left, Expression *right);
    double calculate() override;
  };

  class Minus : public BinaryOperator {
   public:
    // constructor
    Minus(Expression *left, Expression *right);
    double calculate() override;
  };

  class Mul : public BinaryOperator {
   public:
    // constructor
    Mul(Expression *left, Expression *right);
    double calculate() override;
  };

  class Div : public BinaryOperator {
   public:
    // constructor
    Div(Expression *left, Expression *right);
    double calculate() override;
  };
#endif //EX3_NEW__INTERPRETER_H_
