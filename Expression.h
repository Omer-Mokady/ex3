//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW_CMAKE_BUILD_DEBUG_EXPRESSION_H_
#define EX3_NEW_CMAKE_BUILD_DEBUG_EXPRESSION_H_
using namespace std;
/**
 * Expression Interface
 */
class Expression {
 public:
  /**
   * calculate the expression
   * @return expression's double value
   */
  virtual double calculate() = 0;
  /**
   * destructor
   */
  virtual ~Expression() {}
};

#endif //EX3_NEW_CMAKE_BUILD_DEBUG_EXPRESSION_H_
