//
// Created by gal on 19/12/2019.
//

#include "Expression.h"
#include "Interpreter.h"

// interpreter class:
/* '#' is Unary Plus sign
 * '%' is Unary Minus sign
 */
Expression* Interpreter::interpret(string str) {
  int parenthesesCount = 0;
  stack <char> operStack;
  queue <string> strQueue;
  string operStr = "+-*/()";
  string operStrUnary = "+-*/()%#";
  string tempStr;
  int lastOperatorIndex = 0;
  map<char , int> opPrecedence;
  opPrecedence.insert(pair<char, int>('(', 0));
  opPrecedence.insert(pair<char, int>('%', 0));
  opPrecedence.insert(pair<char, int>('#', 0));
  opPrecedence.insert(pair<char, int>('+', 1));
  opPrecedence.insert(pair<char, int>('-', 1));
  opPrecedence.insert(pair<char, int>('*', 2));
  opPrecedence.insert(pair<char, int>('/', 2));
  for(unsigned  int i=0; i<str.length(); i++) {
    // check if the character is an operator
    if(operStr.find(str.at(i)) != std::string::npos) {
      // it's an operator
      // when the right character if unary operator
      if(i==0) {
        if (str.at(i) == '-') {
          operStack.push('%');
          lastOperatorIndex = i + 1;
          continue;
        } else if (str.at(i) == '+') {
          operStack.push('#');
          lastOperatorIndex = i + 1;
          continue;
        } else if (str.at(i) == '(') {
          operStack.push('(');
          parenthesesCount++;
          lastOperatorIndex = i + 1;
          continue;
        }
        // if the operator is not in the first index
      } else {
        string tempOperators = "+-*/";
        // check if there is illegal more than one operator consecutively
        if(tempOperators.find(str.at(i)) != std::string::npos) {
          if(tempOperators.find(str.at(i-1)) != std::string::npos)
          {
            throw "illegal math expression";
          }
        }
        // add number that is before the operator, to the queue
        tempStr = str.substr(lastOperatorIndex, (i - lastOperatorIndex));
        if(!tempStr.empty()) {
          strQueue.push(tempStr);
        }
        // add the operators to the operator's stack
        if(str.at(i) == '(') {
          operStack.push(str.at(i));
          parenthesesCount++;
        } else if(str.at(i) == ')') {
          parenthesesCount--;
          while(operStack.top() != '(' ) {
            strQueue.push(string(1,operStack.top()));
            operStack.pop();
            if(operStack.empty()) {
              throw "before ')'suppose to be '('";
            }
          }
          operStack.pop();
        } else if ((str.at(i) == '+') && (str.at(i-1) == '(')) {
          operStack.push('#');
        } else if ((str.at(i) == '-') && (str.at(i-1) == '(')) {
          operStack.push('%');
        } else if(operStack.empty()) {
          operStack.push(str.at(i));
        } else {
          while(opPrecedence.at(str.at(i)) <= opPrecedence.at(operStack.top())) {
            strQueue.push(string(1,operStack.top()));
            operStack.pop();
            if(operStack.empty()) {
              break;
            }
          }
          operStack.push(str.at(i));
        }
      }
      lastOperatorIndex = i + 1;
    }
  }
  // no more operators were found
  tempStr = str.substr(lastOperatorIndex, (str.length() - lastOperatorIndex));
  if(!tempStr.empty()) {
    strQueue.push(tempStr);
  }
  // add all the operators from the stack
  while(!operStack.empty()) {
    strQueue.push(string(1,operStack.top()));
    operStack.pop();
  }
  //    make Expression object
  stack<Expression*> expStack;
  Expression* tempExp;
  while(!strQueue.empty()) {
    if(operStrUnary.find(strQueue.front()) != std::string::npos) {
      if(strQueue.front() == "#") {
        expStack.top() = new UPlus(expStack.top());
      } else if (strQueue.front() == "%") {
        expStack.top() = new UMinus(expStack.top());
      } else if (strQueue.front() == "*") {
        tempExp = expStack.top();
        expStack.pop();
        expStack.top() = new Mul(expStack.top(), tempExp);
      } else if (strQueue.front() == "+") {
        tempExp = expStack.top();
        expStack.pop();
        expStack.top() = new Plus(expStack.top(), tempExp);
      } else if (strQueue.front() == "-") {
        tempExp = expStack.top();
        expStack.pop();
        expStack.top() = new Minus(expStack.top(), tempExp);
      } else if (strQueue.front() == "/") {
        tempExp = expStack.top();
        expStack.pop();
        expStack.top() = new Div(expStack.top(), tempExp);
      }
      strQueue.pop();
      // string value from queue is not an operator
    } else {
      // check if it's a variable
      if(checkVariableVaildation(strQueue.front())) {
        if(this->varMap.count(strQueue.front()) == 1) {
          expStack.push(new Variable(strQueue.front(), this->varMap.at(strQueue.front())));
          strQueue.pop();
        } else {
          throw "variable does not exist in the map";
        }
        // check if it's a value
      } else if (checkValueVaildation(strQueue.front())) {
        expStack.push(new Value(stod(strQueue.front())));
        strQueue.pop();
      } else {
        throw "syntax error";
      }
    }
  }
  // check parentheses validation
  if(parenthesesCount != 0) {
    throw "parentheses error";
  }
  return expStack.top();
}

Expression* Interpreter::getVariableExp(string str, double num) {
  Expression* newExp = new Variable(str, num);
  return newExp;
}

Expression* Interpreter::getValueExp(string str) {
  Expression* newExp = new Value(stod(str));
  return newExp;
}

bool Interpreter::checkVariableVaildation(string tempStr) {
  bool checkValue = true;
  if(tempStr.empty()) {
    throw "there is no variable imput";
  }
  if(((tempStr.at(0) >= 'A') && (tempStr.at(0) <='Z')) ||
      ((tempStr.at(0) >= 'a') && (tempStr.at(0) <='z')) || (tempStr.at(0) =='_'))
  {
    for(unsigned int i = 0; i < tempStr.length(); i++) {
      if(((tempStr.at(i) >= 'A') && (tempStr.at(i) <='Z')) ||
          ((tempStr.at(i) >= 'a') && (tempStr.at(i) <='z')) ||
          ((tempStr.at(i) >= '0') && (tempStr.at(i) <='9')) ||
          (tempStr.at(i) == '_')) {
        continue;
      } else {
        checkValue = false;
        break;
      }
    }
  } else {
    checkValue = false;
  }
  return checkValue;
}


bool Interpreter::checkValueVaildation(string tempStr) {
  bool checkValue = true;
  int pCounter = 0;
  if(tempStr.empty()) {
    throw "there is no value imput";
  }
  if(  (((tempStr.at(0) >= '0') && (tempStr.at(0) <='9'))
      || ((tempStr.at(0) == '-') && ((tempStr.at(1) >= '0') && (tempStr.at(1) <='9'))) )
      && ((tempStr.at(tempStr.length() - 1) >= '0') && (tempStr.at(tempStr.length() - 1) <='9')) ) {
    for (unsigned int i = 1; i < tempStr.length(); i++) {
      if ((tempStr.at(i) >= '0') && (tempStr.at(i) <= '9')) {
        continue;
      } else if (tempStr.at(i) == '.') {
        pCounter++;
        continue;
      } else {
        checkValue = false;
        break;
      }
    }
  }
  else {
    checkValue = false;
  }
  // check if there is only one "."
  if (pCounter > 1) {
    checkValue = false;
  }
  return checkValue;
}


// return the number value from the equation
string Interpreter::getVariableFromStr(string str) {
  string tempStr = str.substr(0, str.find('='));
  //check return value:
  if(!checkVariableVaildation(tempStr)) {
    throw "illegal variable assignment!";
  }
  return tempStr;
}

// return the variable value from the equation
double Interpreter::getValueFromStr(string str) {
  string tempStr = str.substr(str.find('=') + 1, str.length() - str.find('=') - 1);
  // check validation of the value
  if(!checkValueVaildation(tempStr)) {
    throw "illegal value assignment!";
  }
  return stod(tempStr);
}

void Interpreter::setVariables(string str) {
  string tempStr;
  int startP = 0;
  for(unsigned int i = 0; i < str.length(); i++) {
    // separate substrings by ";"
    if(str.at(i) == ';') {
      tempStr = str.substr(startP, i - startP);
      this->varMap.insert(pair<string, double>(getVariableFromStr(tempStr), getValueFromStr(tempStr)));
      startP = i+1;
    }
  }
  tempStr = str.substr(startP, str.length() - startP);
  this ->varMap[getVariableFromStr(tempStr)] = getValueFromStr(tempStr);
}


// Value class
Value::Value(double num) {
  this->value = num;
}

double Value::calculate() {
  return this->value;
}

// Variable class
Variable::Variable(string name1, double num) {
  this->name = name1;
  this->value = num;
}


double Variable::calculate() {
  return this->value;
}

// prefix increment operator
Variable& Variable::operator++() {
//    this->value = ++(this->value);
  ++(this->value);
  return *this;
}

// postfix increment operator
Variable& Variable::operator++(int) {
  ++(this->value);
  return *this;
}

// prefix decrement operator
Variable& Variable::operator--() {
  --(this->value);
  return *this;
}

// postfix decrement operator
Variable& Variable::operator--(int) {
  --(this->value);
  return *this;
}

Variable& Variable::operator+=(double num) {
  this->value += num;
  return *this;
}
Variable& Variable::operator-=(double num) {
  this->value -= num;
  return *this;
}

// Unary Classes:
// UPLus class
UPlus::UPlus(Expression* expression1) {
  this->expression = expression1;
}
double UPlus::calculate() {
  return this->expression->calculate();
}

UMinus::UMinus(Expression* expression1) {
  this->expression = expression1;
}
double UMinus::calculate() {
  return -(this->expression->calculate());
}
// Unary class
UnaryOperator::~UnaryOperator() {
  if(this->expression != nullptr)
  {
    delete this->expression;
  }
}


// Binary class
BinaryOperator::~BinaryOperator() {
  if(this->right != nullptr)
  {
    delete this->right;
  }
  if(this->left != nullptr) {
    delete this->left;
  }
}

// Plus class

Plus::Plus(Expression* leftNum, Expression* rightNum) {
  this->left = leftNum;
  this->right = rightNum;
}

double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}

// Minus class
Minus::Minus(Expression* leftNum, Expression* rightNum) {
  this->left = leftNum;
  this->right = rightNum;
}

double Minus::calculate() {
  return this->left->calculate() - this->right->calculate();
}

// Mul class
Mul::Mul(Expression* leftNum, Expression* rightNum) {
  this->left = leftNum;
  this->right = rightNum;
}

double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}

//Div class
Div::Div(Expression* leftNum, Expression* rightNum) {
  if(rightNum->calculate() == 0) {
    throw "division by zero";
  } else {
    this->left = leftNum;
    this->right = rightNum;
  }
}

double Div::calculate() {
  return this->left->calculate() / this->right->calculate();
}