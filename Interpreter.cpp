//
// Created by gal on 19/12/2019.
//

#include "Expression.h"
#include "Interpreter.h"

void Interpreter::setVariables(string expression) {
  int i = 0, start = 0, end = 0;
  string sub = "";
  while (expression[i] != '\0') {
    if (expression[i] == ';') {
      end = i;
      sub = expression.substr(start, (end - start));
      createVars(sub);
      start = end + 1;
    }
    i++;
  }
  if (i - start >= 3) { // in case the last assignment isn't ended with a semi column.
    end = i;
    sub = expression.substr(start, (end - start));
    createVars(sub);
  }
}

void Interpreter::createVars(string toSplit) {
  int i = 0, buffer;
  string name, valAsStr;
  double val = 0;
  while (toSplit[i] != '=') {
    i++;
  }
  buffer = i;
  name = toSplit.substr(0, buffer);
  while (toSplit[i] != '\0') {
    i++;
  }
  valAsStr = toSplit.substr(buffer + 1, i - buffer);
  if (isValueLegal(valAsStr)) {
    val = stod(valAsStr, nullptr);
  } else {
    throw ("illegal variable assignment!");
  }
  if (isVariableNameLegal(name)) {
    if (isVariableExist(name)) { //updating value of a key in the map.
      variables.erase(name);
    }
    variables.insert(pair<string, double>(name, val));

  } else {
    throw ("illegal variable assignment!");
  }
}

Expression *Interpreter::interpret(string exp) {
  stack<string> operators;
  queue<string> postfix;
  string num = "", op = "";
  int i = 0;
  try {
    if (!isLegal(exp) || !mathLegality(exp)) { //check parenthesis and numbers
      throw "illegal math expression";
    } else {
      while (exp[i] != '\0') { //read to the end of the string.
        if (exp[i] == ')') { //closing parenthesis
          while (operators.top()[0] != '(') {
            op = operators.top();
            postfix.push(op);
            op.clear();
            operators.pop();
          }
          operators.pop();
          i++;
        } else if (isdigit(exp[i]) || exp[i] == '.' || (exp[i] >= 'a' && exp[i] <= 'z')
            || (exp[i] >= 'A' && exp[i] <= 'Z') || exp[i] == '_') { //digits
          while (isdigit(exp[i]) || exp[i] == '.' || (exp[i] >= 'a' && exp[i] <= 'z')
              || (exp[i] >= 'A' && exp[i] <= 'Z') || exp[i] == '_') {
            num += exp[i];
            i++;
          }
          postfix.push(num);
          num.clear();

        } else { //operation or open parenthesis.
          op += exp[i];
          if (exp[i] == '-' && i == 0) {
            operators.push("&");
            op.clear();
            i++;
          } else if (exp[i] == '+' && i == 0) {
            operators.push("$");
            op.clear();
            i++;
          } else if (!operators.empty()) {
            if (op[0] == '(') {
              if (exp[i + 1] == '-') { // unary Minus
                exp[i + 1] = '&';
              } else if (exp[i + 1] == '+') { //unary Plus
                exp[i + 1] = '$';
              }
              operators.push(op);
              op.clear();
              i++;
            } else if (op[0] == '&' || op[0] == '$') {
              operators.push(op);
              op.clear();
              i++;
            } else if ((operators.top()[0] != '(') && (getStrength(op) <= getStrength(operators.top()))) {
              postfix.push(operators.top());
              operators.pop();
              operators.push(op);
              op.clear();
              i++;
            } else {
              operators.push(op);
              op.clear();
              i++;
            }
          } else {
            operators.push(op);
            op.clear();
            i++;
          }
        }
      }
      while (!operators.empty()) {
        op = operators.top();
        postfix.push(op);
        operators.pop();
      }
      return (fromPostfix(postfix));
    }
  }
  catch (const char *e) {
    throw e;
  }

}

int Interpreter::getStrength(string oper) { // determine the precedence of the given sign: -,+, * or /.
  switch (oper[0]) {
    case '-':return 1;
    case '+':return 1;
    case '*':return 2;
    case '/':return 2;
    case '$':return 3;
    case '&':return 3;
    case '(':return 4;
    default: return 1;
  }
}

bool Interpreter::isLegal(string expression) { //parenthesis
  int counter = 0, i = 0;
  if (expression.length() == 1) { // check for one digit or variable assignment.
    if (isdigit(expression[0])) {
      return true;
    } else if (expression[0] >= 'a' && expression[0] <= 'z') {
      return true;
    } else if (expression[0] >= 'A' && expression[0] <= 'Z') {
      return true;
    } else if (expression[0] == '_') {
      return true;
    }
    return false;
  } else {
    while (expression[i] != '\0') {
      if (expression[i] == '(') {
        counter++;
      } else if (expression[i] == ')') {
        counter--;
      }
      i++;
    }
    return counter == 0 && (expression[i - 1] == ')'
        ||
            isdigit(expression[i - 1])
    );
  }
}

bool Interpreter::mathLegality(string exp) { //basic mathematical validity check.
  regex format("[(A-Za-z_0-9-][A-Za-z0-9_()+-/*]*");
  int regexLegality = 0, operatorsLegality = 0, i = 0;
  stack<char> parentheses;
  while (exp[i] != '\0') {
    if (exp[i] == '(') {
      parentheses.push(exp[i]);
    } else if (exp[i] == ')') {
      if (parentheses.empty()) {
        return false;
      }
      parentheses.top();
    }
    i++;
  }
  i = 1;
  regexLegality += (regex_match(exp, format)); // add 1 to the sum if there is a match => true.

  while (exp[i + 1] != '\0') { // read up to one before last char, so we wont get segmentation fault.
    if ((isOperator(exp[i]) && isOperator(exp[i - 1]))
        || (isOperator(exp[i]) && isOperator(exp[i + 1]))) { //two operators one after another - should never happen.
      operatorsLegality += 1;
    }
    i++;
  }
  return regexLegality == 1 && operatorsLegality == 0;
}
bool Interpreter::isOperator(char op) {
  return (op == '+') || (op == '-') || (op == '*') || (op == '/');
}
bool Interpreter::isVariableNameLegal(string expression) { //variable name validity, used in setVariables.
  regex format("[A-Za-z_][A-Za-z0-9_]*");
  return (regex_match(expression, format));
}

bool Interpreter::isValueLegal(string expression) { // //variable value validity, used in setVariables
  regex format("[-]?[0-9]+[.]?[0-9]*");
  return (regex_match(expression, format));
}

bool Interpreter::isVariableExist(string toCheck) {
  if (variables.count(toCheck)) {
    return true;
  }
  return false;
}

Expression *Interpreter::fromPostfix(queue<string> postfix) {
  stack < Expression * > expressions;
  Expression *first;
  Expression *second;
  string temp = "";
  double val;
  try {
    while (postfix.size() > 0) {
      temp = postfix.front();
      //check if temp is variable, number or operator.
      if (isValueLegal(temp)) { //if it's a legal number => it's a number and nothing else.
        expressions.push(new Value(stod(temp)));
      } else if (isVariableNameLegal(temp)) { // not a number & legal variable name => it's a variable.
        if (isVariableExist(temp)) {
          val = variables.find(temp)->second;
          expressions.push(new Variable(temp, val));
        } else {
          throw ("illegal math expression");
        }
        //beginning of creating a whole expressions.
      } else if (temp[0] == '+') {
        second = expressions.top();
        expressions.pop();
        first = expressions.top();
        expressions.pop();
        expressions.push(new Plus(first, second));
      } else if (temp[0] == '-') {
        second = expressions.top();
        expressions.pop();
        first = expressions.top();
        expressions.pop();
        expressions.push(new Minus(first, second));
      } else if (temp[0] == '*') {
        second = expressions.top();
        expressions.pop();
        first = expressions.top();
        expressions.pop();
        expressions.push(new Mul(first, second));
      } else if (temp[0] == '/') {
        second = expressions.top();
        expressions.pop();
        first = expressions.top();
        expressions.pop();
        expressions.push(new Div(first, second));
      } else if (temp[0] == '$') {
        first = expressions.top();
        expressions.pop();
        expressions.push(new UPlus(first));
      } else if (temp[0] == '&') {
        first = expressions.top();
        expressions.pop();
        expressions.push(new UMinus(first));
      }
      postfix.pop();
    }
    first = expressions.top();
    return first;
  } catch (const char *e) {
    throw e;
  }
}
//-------------------------------------------------BASE CLASSES---------------------------------------------------------
/*
 * class Variable
 */
Variable::Variable(string varName, double val) {
  this->name = varName;
  this->value = val;
}

Variable &Variable::operator++() {
  this->value = this->value + 1;
  return *this;
}
Variable &Variable::operator++(int) {
  this->value = this->value + 1;
  return *this;
}

Variable &Variable::operator--() {
  this->value = this->value - 1;
  return *this;
}
Variable &Variable::operator--(int) {
  this->value = this->value - 1;
  return *this;
}

Variable &Variable::operator+=(double d) {
  this->value = this->value + d;

  return *this;
}

Variable &Variable::operator-=(double d) {
  this->value = this->value - d;
  return *this;
}

double Variable::calculate() {
  return this->value;
}
/*
 * class Value
 */
Value::Value(double val) {
  this->value = val;
}
double Value::calculate() {
  return this->value;
}
//-------------------------------------------------UNARY---------------------------------------------------------

/*
 * class UPlus
 */
UPlus::UPlus(Expression *expression) {
  this->exp = expression;
}

double UPlus::calculate() {
  try {
    if (this->exp != nullptr) {
      return this->exp->calculate();
    } else {
      throw "Bad input!";
    }
  }
  catch (const char *e) {
    throw e;
  }
}
/*
 * class UMinus
 */
UMinus::UMinus(Expression *expression) {
  this->exp = expression;
}

double UMinus::calculate() {
  try {
    if (this->exp != nullptr) {
      return -1 * this->exp->calculate();
    } else {
      throw "Bad input!";
    }
  }
  catch (const char *e) {
    throw e;
  }
}



//-------------------------------------------------BINARY---------------------------------------------------------


/*
 * class Plus
 */

Plus::Plus(Expression *left, Expression *right) {
  this->leftExpression = left;
  this->rightExpression = right;
}
double Plus::calculate() {
  try {
    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
      return this->leftExpression->calculate() + this->rightExpression->calculate();
    } else {
      throw "Bad input!";
    }
  }
  catch (const char *e) {
    throw e;
  }

}

/*
 * class Minus
 */
Minus::Minus(Expression *left, Expression *right) {
  this->leftExpression = left;
  this->rightExpression = right;
}
double Minus::calculate() {
  try {
    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
      return this->leftExpression->calculate() - this->rightExpression->calculate();
    } else {
      throw "Bad input!";
    }
  }
  catch (const char *e) {
    throw e;
  }
}

/*
 * class Mul
 */

Mul::Mul(Expression *left, Expression *right) {
  this->leftExpression = left;
  this->rightExpression = right;
}
double Mul::calculate() {
  try {
    if (this->leftExpression != nullptr && this->rightExpression != nullptr) {
      return this->leftExpression->calculate() * this->rightExpression->calculate();
    } else {
      throw "Bad input!";
    }
  }
  catch (const char *e) {
    throw e;
  }

}

/*
 * class Div
 */

Div::Div(Expression *left, Expression *right) {
  this->leftExpression = left;
  this->rightExpression = right;
}
double Div::calculate() {
  try {
    if (this->rightExpression->calculate() == 0) {
      throw "division by zero";
    } else {
      return this->leftExpression->calculate() / this->rightExpression->calculate();
    }
  }
  catch (const char *e) {
    throw e;
  }
}