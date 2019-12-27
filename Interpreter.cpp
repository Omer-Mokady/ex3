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


///*
//void Interpreter::setVariables(string expression) {
//  int i = 0, start = 0, end = 0;
//  string sub = "";
//  while (expression[i] != '\0') {
//    if (expression[i] == ';') {
//      end = i;
//      sub = expression.substr(start, (end - start));
//      createVars(sub);
//      start = end + 1;
//    }
//    i++;
//  }
//  if (i - start >= 3) { // in case the last assignment isn't ended with a semi column.
//    end = i;
//    sub = expression.substr(start, (end - start));
//    createVars(sub);
//  }
//}
//
//void Interpreter::createVars(string toSplit) {
//  int i = 0, buffer;
//  string name, valAsStr;
//  double val = 0;
//  while (toSplit[i] != '=') {
//    i++;
//  }
//  buffer = i;
//  name = toSplit.substr(0, buffer);
//  while (toSplit[i] != '\0') {
//    i++;
//  }
//  valAsStr = toSplit.substr(buffer + 1, i - buffer);
//  if (isValueLegal(valAsStr)) {
//    val = stod(valAsStr, nullptr);
//  } else {
//    throw ("illegal variable assignment!");
//  }
//  if (isVariableNameLegal(name)) {
//    if (isVariableExist(name)) { //updating value of a key in the map.
//      variables.erase(name);
//    }
//    variables.insert(pair<string, double>(name, val));
//
//  } else {
//    throw ("illegal variable assignment!");
//  }
//}
//
//Expression *Interpreter::interpret(string exp) {
//  stack<string> operators;
//  queue<string> postfix;
//  string num = "", op = "";
//  int i = 0;
//  try {
//    if (!isLegal(exp) || !mathLegality(exp)) { //check parenthesis and numbers
//      throw "illegal math expression";
//    } else {
//      while (exp[i] != '\0') { //read to the end of the string.
//        if (exp[i] == ')') { //closing parenthesis
//          while (operators.top()[0] != '(') {
//            op = operators.top();
//            postfix.push(op);
//            op.clear();
//            operators.pop();
//          }
//          operators.pop();
//          i++;
//        } else if (isdigit(exp[i]) || exp[i] == '.' || (exp[i] >= 'a' && exp[i] <= 'z')
//            || (exp[i] >= 'A' && exp[i] <= 'Z') || exp[i] == '_') { //digits
//          while (isdigit(exp[i]) || exp[i] == '.' || (exp[i] >= 'a' && exp[i] <= 'z')
//              || (exp[i] >= 'A' && exp[i] <= 'Z') || exp[i] == '_') {
//            num += exp[i];
//            i++;
//          }
//          postfix.push(num);
//          num.clear();
//
//        } else { //operation or open parenthesis.
//          op += exp[i];
//          if (exp[i] == '-' && i == 0) {
//            operators.push("&");
//            op.clear();
//            i++;
//          } else if (exp[i] == '+' && i == 0) {
//            operators.push("$");
//            op.clear();
//            i++;
//          } else if (!operators.empty()) {
//            if (op[0] == '(') {
//              if (exp[i + 1] == '-') { // unary Minus
//                exp[i + 1] = '&';
//              } else if (exp[i + 1] == '+') { //unary Plus
//                exp[i + 1] = '$';
//              }
//              operators.push(op);
//              op.clear();
//              i++;
//            } else if (op[0] == '&' || op[0] == '$') {
//              operators.push(op);
//              op.clear();
//              i++;
//            } else if ((operators.top()[0] != '(') && (getStrength(op) <= getStrength(operators.top()))) {
//              postfix.push(operators.top());
//              operators.pop();
//              operators.push(op);
//              op.clear();
//              i++;
//            } else {
//              operators.push(op);
//              op.clear();
//              i++;
//            }
//          } else {
//            operators.push(op);
//            op.clear();
//            i++;
//          }
//        }
//      }
//      while (!operators.empty()) {
//        op = operators.top();
//        postfix.push(op);
//        operators.pop();
//      }
//      return (fromPostfix(postfix));
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//
//}
//
//int Interpreter::getStrength(string oper) { // determine the precedence of the given sign: -,+, * or /.
//  switch (oper[0]) {
//    case '-':return 1;
//    case '+':return 1;
//    case '*':return 2;
//    case '/':return 2;
//    case '$':return 3;
//    case '&':return 3;
//    case '(':return 4;
//    default: return 1;
//  }
//}
//
//bool Interpreter::isLegal(string expression) { //parenthesis
//  int counter = 0, i = 0;
//  if (expression.length() == 1) { // check for one digit or variable assignment.
//    if (isdigit(expression[0])) {
//      return true;
//    } else if (expression[0] >= 'a' && expression[0] <= 'z') {
//      return true;
//    } else if (expression[0] >= 'A' && expression[0] <= 'Z') {
//      return true;
//    } else if (expression[0] == '_') {
//      return true;
//    }
//    return false;
//  } else {
//    while (expression[i] != '\0') {
//      if (expression[i] == '(') {
//        counter++;
//      } else if (expression[i] == ')') {
//        counter--;
//      }
//      i++;
//    }
//    return counter == 0 && (expression[i - 1] == ')'
//        ||
//            isdigit(expression[i - 1])
//    );
//  }
//}
//
//bool Interpreter::mathLegality(string exp) { //basic mathematical validity check.
//  regex format("[(A-Za-z_0-9-][A-Za-z0-9_()+-/*]*");
//  int regexLegality = 0, operatorsLegality = 0, i = 0;
//  stack<char> parentheses;
//  while (exp[i] != '\0') {
//    if (exp[i] == '(') {
//      parentheses.push(exp[i]);
//    } else if (exp[i] == ')') {
//      if (parentheses.empty()) {
//        return false;
//      }
//      parentheses.top();
//    }
//    i++;
//  }
//  i = 1;
//  regexLegality += (regex_match(exp, format)); // add 1 to the sum if there is a match => true.
//
//  while (exp[i + 1] != '\0') { // read up to one before last char, so we wont get segmentation fault.
//    if ((isOperator(exp[i]) && isOperator(exp[i - 1]))
//        || (isOperator(exp[i]) && isOperator(exp[i + 1]))) { //two operators one after another - should never happen.
//      operatorsLegality += 1;
//    }
//    i++;
//  }
//  return regexLegality == 1 && operatorsLegality == 0;
//}
//bool Interpreter::isOperator(char op) {
//  return (op == '+') || (op == '-') || (op == '*') || (op == '/');
//}
//bool Interpreter::isVariableNameLegal(string expression) { //variable name validity, used in setVariables.
//  regex format("[A-Za-z_][A-Za-z0-9_]*");
//  return (regex_match(expression, format));
//}
//
//bool Interpreter::isValueLegal(string expression) { // //variable value validity, used in setVariables
//  regex format("[-]?[0-9]+[.]?[0-9]*");
//  return (regex_match(expression, format));
//}
//
//bool Interpreter::isVariableExist(string toCheck) {
//  if (variables.count(toCheck)) {
//    return true;
//  }
//  return false;
//}
//
//Expression *Interpreter::fromPostfix(queue<string> postfix) {
//  stack < Expression * > expressions;
//  Expression *first;
//  Expression *second;
//  string temp = "";
//  double val;
//  try {
//    while (postfix.size() > 0) {
//      temp = postfix.front();
//      //check if temp is variable, number or operator.
//      if (isValueLegal(temp)) { //if it's a legal number => it's a number and nothing else.
//        expressions.push(new Value(stod(temp)));
//      } else if (isVariableNameLegal(temp)) { // not a number & legal variable name => it's a variable.
//        if (isVariableExist(temp)) {
//          val = variables.find(temp)->second;
//          expressions.push(new Variable(temp, val));
//        } else {
//          throw ("illegal math expression");
//        }
//        //beginning of creating a whole expressions.
//      } else if (temp[0] == '+') {
//        second = expressions.top();
//        expressions.pop();
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new Plus(first, second));
//      } else if (temp[0] == '-') {
//        second = expressions.top();
//        expressions.pop();
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new Minus(first, second));
//      } else if (temp[0] == '*') {
//        second = expressions.top();
//        expressions.pop();
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new Mul(first, second));
//      } else if (temp[0] == '/') {
//        second = expressions.top();
//        expressions.pop();
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new Div(first, second));
//      } else if (temp[0] == '$') {
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new UPlus(first));
//      } else if (temp[0] == '&') {
//        first = expressions.top();
//        expressions.pop();
//        expressions.push(new UMinus(first));
//      }
//      postfix.pop();
//    }
//    first = expressions.top();
//    return first;
//  } catch (const char *e) {
//    throw e;
//  }
//}
////-------------------------------------------------BASE CLASSES---------------------------------------------------------
///*
// * class Variable
// */
//Variable::Variable(string varName, double val) {
//  this->name = varName;
//  this->value = val;
//}
//
//Variable &Variable::operator++() {
//  this->value = this->value + 1;
//  return *this;
//}
//Variable &Variable::operator++(int) {
//  this->value = this->value + 1;
//  return *this;
//}
//
//Variable &Variable::operator--() {
//  this->value = this->value - 1;
//  return *this;
//}
//Variable &Variable::operator--(int) {
//  this->value = this->value - 1;
//  return *this;
//}
//
//Variable &Variable::operator+=(double d) {
//  this->value = this->value + d;
//
//  return *this;
//}
//
//Variable &Variable::operator-=(double d) {
//  this->value = this->value - d;
//  return *this;
//}
//
//double Variable::calculate() {
//  return this->value;
//}
///*
// * class Value
// */
//Value::Value(double val) {
//  this->value = val;
//}
//double Value::calculate() {
//  return this->value;
//}
////-------------------------------------------------UNARY---------------------------------------------------------
//
///*
// * class UPlus
// */
//UPlus::UPlus(Expression *expression) {
//  this->exp = expression;
//}
//
//double UPlus::calculate() {
//  try {
//    if (this->exp != nullptr) {
//      return this->exp->calculate();
//    } else {
//      throw "Bad input!";
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//}
///*
// * class UMinus
// */
//UMinus::UMinus(Expression *expression) {
//  this->exp = expression;
//}
//
//double UMinus::calculate() {
//  try {
//    if (this->exp != nullptr) {
//      return -1 * this->exp->calculate();
//    } else {
//      throw "Bad input!";
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//}
//
//
//
////-------------------------------------------------BINARY---------------------------------------------------------
//
//
///*
// * class Plus
// */
//
//Plus::Plus(Expression *left, Expression *right) {
//  this->leftExpression = left;
//  this->rightExpression = right;
//}
//double Plus::calculate() {
//  try {
//    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
//      return this->leftExpression->calculate() + this->rightExpression->calculate();
//    } else {
//      throw "Bad input!";
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//
//}
//
///*
// * class Minus
// */
//Minus::Minus(Expression *left, Expression *right) {
//  this->leftExpression = left;
//  this->rightExpression = right;
//}
//double Minus::calculate() {
//  try {
//    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
//      return this->leftExpression->calculate() - this->rightExpression->calculate();
//    } else {
//      throw "Bad input!";
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//}
//
///*
// * class Mul
// */
//
//Mul::Mul(Expression *left, Expression *right) {
//  this->leftExpression = left;
//  this->rightExpression = right;
//}
//double Mul::calculate() {
//  try {
//    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
//      return this->leftExpression->calculate() * this->rightExpression->calculate();
//    } else {
//      throw "Bad input!";
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//
//}
//
///*
// * class Div
// */
//
//Div::Div(Expression *left, Expression *right) {
//  this->leftExpression = left;
//  this->rightExpression = right;
//}
//double Div::calculate() {
//  try {
//    if (this->rightExpression->calculate() == 0) {
//      throw "division by zero";
//    } else {
//      return this->leftExpression->calculate() / this->rightExpression->calculate();
//    }
//  }
//  catch (const char *e) {
//    throw e;
//  }
//}