#include "s21_smartcalc.h"

double outputResult(const char* str, double x, int* flagForValidation) {
  long double result = 0;
  if (!isValidExpression(str)) {
    *flagForValidation = 1;
  } else {
    numbers* num = init_double_stack();
    char* s = calloc(MAX_SIZE, sizeof(char));
    strcpy(s, str);
    char* p = toPostFix(s);
    if (strchr(str, 'x')) {
      result = calculationsWithX(p, num, x);
    } else {
      result = calculations(p, num);
    }
    remove_double_stack(num);
    free(s);
    free(p);
    free(num);
    *flagForValidation = 0;
  }
  return result;
}

long double graphResult(const char* str, double x, int* flagForValidation) {
  long double result = 0.0;
  if (!isValidExpression(str)) {
    *flagForValidation = 1;
  } else {
    numbers* num = init_double_stack();
    char* s = calloc(MAX_SIZE, sizeof(char));
    strcpy(s, str);
    char* p = toPostFix(s);
    result = calculationsWithX(p, num, x);
    free(s);
    free(p);
    remove_double_stack(num);
    free(num);
    *flagForValidation = 0;
  }
  return result;
}

long double calculationsWithX(char* str, numbers* num, long double x) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (str[i] == 'x') {
      push_into_double(num, x);
    } else if (isdigit(str[i]) || str[i] == '.') {
      char* endPtr;
      long double tmp_numb = strtod(&str[i], &endPtr);
      push_into_double(num, tmp_numb);
      i = endPtr - str - 1;
    } else if (operatorsWithTwoNumberCheck(str[i])) {
      long double second = pop_double_stack(num);
      long double first = pop_double_stack(num);
      push_into_double(num, executeCalc(str[i], first, second));
    } else if (operatorsWithOneNumberCheck(str[i])) {
      long double number = pop_double_stack(num);
      push_into_double(num, executeCalcOne(str[i], number));
    }
  }
  return pop_double_stack(num);
}

long double calculations(char* str, numbers* num) {
  for (size_t i = 0; i < strlen(str); i++) {
    if (isdigit(str[i]) || str[i] == '.') {
      char* endPtr;
      long double tmp_numb = strtod(&str[i], &endPtr);
      push_into_double(num, tmp_numb);
      i = endPtr - str - 1;
    } else if (operatorsWithTwoNumberCheck(str[i])) {
      long double second = pop_double_stack(num);
      long double first = pop_double_stack(num);
      push_into_double(num, executeCalc(str[i], first, second));
    } else if (operatorsWithOneNumberCheck(str[i])) {
      long double number = pop_double_stack(num);
      push_into_double(num, executeCalcOne(str[i], number));
    }
  }
  return pop_double_stack(num);
}

int operatorsWithTwoNumberCheck(char c) {
  int flag = 0;
  if (strchr("+/*^-%", c)) {
    flag = 1;
  }
  return flag;
}

int operatorsWithOneNumberCheck(char c) {
  int flag = 0;
  if (strchr("sctlgqioa~", c)) {
    flag = 1;
  }
  return flag;
}

long double executeCalc(char s, long double first, long double second) {
  long double result = 0.0;
  if (s == '+') {
    result = first + second;
  } else if (s == '/')
    result = first / second;
  else if (s == '-')
    result = first - second;
  else if (s == '*')
    result = first * second;
  else if (s == '^')
    result = pow(first, second);
  else if (s == '%')
    result = fmod(first, second);
  return result;
}

long double executeCalcOne(char s, long double first) {
  long double result = 0.0;
  if (s == '~') {
    result = (0.0 - first);
  } else if (s == 's')
    result = sin(first);
  else if (s == 'c')
    result = cos(first);
  else if (s == 't')
    result = tan(first);
  else if (s == 'l')
    result = log(first);
  else if (s == 'g')
    result = log10(first);
  else if (s == 'q')
    result = sqrt(first);
  else if (s == 'i')
    result = asin(first);
  else if (s == 'o')
    result = acos(first);
  else if (s == 'a')
    result = atan(first);
  return result;
}

char* toPostFix(char* str) {
  char* postfixExp = calloc(1, sizeof(char));
  operators* op = init_stack();
  int n = 20;
  for (size_t i = 0; i < strlen(str); i++) {
    if ((isdigit(str[i]) || str[i] == '.') || str[i] == 'x') {
      if (str[i] == 'x') {
        postfixExp =
            realloc(postfixExp, (strlen(postfixExp) + n) * sizeof(char));
        stringWork(&postfixExp, 'x');
      } else {
        char* endPtr;
        long double tmp_numb = strtod(&str[i], &endPtr);
        char* buffer = calloc(n, sizeof(char));
        snprintf(buffer, n, "%Lf", tmp_numb);
        stringWork(&buffer, ':');
        postfixExp =
            realloc(postfixExp, (strlen(postfixExp) + n) * sizeof(char));
        strcat(postfixExp, buffer);
        i = endPtr - str - 1;
        free(buffer);
      }
    } else if (str[i] == '(') {
      push(op, &str[i]);
    } else if (str[i] == ')') {
      while (!is_stack_empty(op) && peek(op) != '(') {
        stringWork(&postfixExp, pop(op));
      }
      pop(op);
    } else if (operatorsWithOneNumberCheck(str[i])) {
      i = dealWithFunctions(str, op, postfixExp, i);
    } else if (operatorsWithTwoNumberCheck(str[i])) {
      if (str[i] == '-' && i > 1 && operatorsWithTwoNumberCheck(str[i - 1])) {
        str[i] = '~';
      }
      while (!is_stack_empty(op) &&
             operationPriority(peek(op)) >= operationPriority(str[i])) {
        stringWork(&postfixExp, pop(op));
      }
      push(op, &str[i]);
    }
  }
  while (!is_stack_empty(op)) {
    stringWork(&postfixExp, pop(op));
  }
  free(op);
  return postfixExp;
}

bool isValidOperator(char op) {
  return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' ||
         op == '%' || op == '~';
}

bool isValidFunction(const char* func) {
  return strcmp(func, "sin") == 0 || strcmp(func, "cos") == 0 ||
         strcmp(func, "tan") == 0 || strcmp(func, "asin") == 0 ||
         strcmp(func, "acos") == 0 || strcmp(func, "atan") == 0 ||
         strcmp(func, "sqrt") == 0 || strcmp(func, "ln") == 0 ||
         strcmp(func, "lg") == 0;
}

bool isValidExpression(const char* expression) {
  bool result = true;
  int parentheses_count = 0;
  bool expecting_operand = true;
  while (*expression && result) {
    if (isdigit(*expression) || *expression == '.' || *expression == 'x') {
      expression++;
      expecting_operand = false;
    } else if (*expression == '(') {
      parentheses_count++;
      expression++;
    } else if (*expression == ')') {
      parentheses_count--;
      expression++;
    } else if (isValidOperator(*expression)) {
      if (expecting_operand && *expression != '-') result = false;
      expression++;
      expecting_operand = true;
    } else {
      char buffer[10];
      int i = 0;
      while (isalpha(*expression) && i < 9) {
        buffer[i++] = *expression++;
      }
      buffer[i] = '\0';
      if (isValidFunction(buffer)) {
        if (*expression != '(') result = false;
        parentheses_count++;
        expression++;
      } else {
        result = false;
      }
    }
  }
  if (parentheses_count != 0) result = false;
  if (expecting_operand) {
    result = false;
  }
  return result;
}

int dealWithFunctions(char* str, operators* op, char* postFix, int i) {
  if (str[i] == 'l' && str[i + 1] == 'g') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "g");
    i++;
  } else if (str[i] == 'l' && str[i + 1] == 'n') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "l");
    i++;
  } else if (str[i] == 's' && str[i + 1] == 'q') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "q");
    i = i + 3;
  } else if (str[i] == 's' && str[i + 1] == 'i') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "s");
    i = i + 2;
  } else if (str[i] == 'c' && str[i + 1] == 'o') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "c");
    i = i + 2;
  } else if (str[i] == 't' && str[i + 1] == 'a') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "t");
    i = i + 2;
  } else if (str[i] == 'a' && str[i + 1] == 's') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "i");
    i = i + 3;
  } else if (str[i] == 'a' && str[i + 1] == 'c') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "o");
    i = i + 3;
  } else if (str[i] == 'a' && str[i + 1] == 't') {
    while (!is_stack_empty(op) &&
           operationPriority(peek(op)) >= operationPriority('f')) {
      stringWork(&postFix, pop(op));
    }
    push(op, "a");
    i = i + 3;
  }
  return i;
}

void stringWork(char** str, char c) {
  size_t len = strlen(*str);
  *str = (char*)realloc(*str, (len + 2) * sizeof(char));

  if (*str == NULL) {
    printf("Ошибка выделения памяти\n");
    exit(1);
  }
  (*str)[len] = c;
  (*str)[len + 1] = '\0';
}

int operationPriority(int operator_code) {
  int operator_precedence = 0;
  if (operator_code == '(') {
    operator_precedence = OPEN_BRACKET;
  } else if (operator_code == '+') {
    operator_precedence = PLUS;
  } else if (operator_code == '-') {
    operator_precedence = MINUS;
  } else if (operator_code == '*') {
    operator_precedence = MULT;
  } else if (operator_code == '/') {
    operator_precedence = DIV;
  } else if (operator_code == '%') {
    operator_precedence = MOD;
  } else if (operator_code == '^') {
    operator_precedence = POW;
  } else if (operator_code == '~') {
    operator_precedence = UNARY_MINUS;
  } else if (strchr("sctlgqioaf", operator_code)) {
    operator_precedence = FUN;
  }
  return operator_precedence;
}

operators* init_stack() {
  bool is_error = false;
  operators* newstack = (operators*)calloc(1, sizeof(operators));
  if (newstack == NULL) {
    is_error = true;
  } else {
    newstack->length = 0;
    if (newstack->tokens == NULL) {
      is_error = true;
    }
  }

  return is_error == 0 ? newstack : NULL;
}

bool is_stack_empty(operators* stack) {
  if (stack == NULL) {
    return false;
  }

  return (stack->length == 0);
}

bool is_stack_full(operators* stack) {
  if (stack == NULL) {
    return false;
  }

  return stack->length == MAX_SIZE;
}

void push(operators* stack, char* token) {
  if (stack != NULL && !is_stack_full(stack)) {
    stack->tokens[stack->length] = *token;
    stack->length++;
  }
}

char peek(operators* stack) {
  if (stack == NULL || is_stack_empty(stack)) {
    return 0;
  }

  return stack->tokens[stack->length - 1];
}

char pop(operators* stack) {
  if (stack == NULL || is_stack_empty(stack)) {
    return 0;
  }

  stack->length--;
  return stack->tokens[stack->length];
}

numbers* init_double_stack() {
  numbers* newstack = (numbers*)calloc(1, sizeof(numbers));
  if (newstack != NULL) {
    newstack->length = 0;
    newstack->values = (long double*)calloc(MAX_SIZE, sizeof(long double*));
  }

  return newstack->values != NULL ? newstack : NULL;
}

bool is_double_stack_empty(numbers* stack) {
  if (stack == NULL) {
    return false;
  }

  return stack->length == 0;
}

bool is_double_stack_full(numbers* stack) {
  if (stack == NULL) {
    return false;
  }

  return stack->length == MAX_SIZE;
}

void push_into_double(numbers* stack, long double value) {
  if (stack != NULL && !is_double_stack_full(stack)) {
    stack->values[stack->length] = value;
    stack->length++;
  }
}

long double pop_double_stack(numbers* stack) {
  if (stack == NULL || is_double_stack_empty(stack)) {
    return 0;
  }

  stack->length--;
  return stack->values[stack->length];
}

void remove_double_stack(numbers* stack) {
  if (stack != NULL && stack->values != NULL) {
    free(stack->values);
    stack->values = NULL;
    stack->length = 0;
  }
}
