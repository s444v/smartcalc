#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

enum operators_priority {
  OPEN_BRACKET = 0,
  PLUS,
  MINUS = 1,
  MULT,
  DIV = 2,
  MOD,
  POW = 3,
  UNARY_MINUS,
  UNARY_PLUS = 4,
  FUN = 5,
};

typedef struct stack_operators {
  int length;
  char tokens[MAX_SIZE];
} operators;

typedef struct stack_numbers {
  int length;
  long double* values;
} numbers;

char* toPostFix(char* str);
int operationPriority(int operator_code);
void stringWork(char** str, char c);
long double executeCalc(char s, long double first, long double second);
long double executeCalcOne(char s, long double first);
long double calculations(char* str, numbers* num);
int operatorsWithTwoNumberCheck(char c);
int operatorsWithOneNumberCheck(char c);
int dealWithFunctions(char* str, operators* op, char* postFix, int i);
double outputResult(const char* str, double x, int* flagForValidation);
bool isValidExpression(const char* expression);
bool isValidFunction(const char* func);
bool isValidOperator(char op);

long double graphResult(const char* str, double x, int* flagForValidation);
long double calculationsWithX(char* str, numbers* num, long double x);

operators* init_stack();
bool is_stack_empty(operators* stack);
bool is_stack_full(operators* stack);
void push(operators* stack, char* token);
char peek(operators* stack);
char pop(operators* stack);

numbers* init_double_stack();
bool is_double_stack_empty(numbers* stack);
bool is_double_stack_empty(numbers* stack);
void push_into_double(numbers* stack, long double value);
long double peek_double_stack(numbers* stack);
long double pop_double_stack(numbers* stack);
void remove_double_stack(numbers* stack);

#endif