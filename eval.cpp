#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
#include <sstream>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
// Evaluates an integer arithmetic expression
// Precondition: infix is an infix integer arithmetic
//   expression consisting of single lower case letter operands,
//   parentheses, and the operators +, -, *, /, with embedded blanks
//   allowed for readability.
// Postcondition: If infix is a syntactically valid infix integer
//   expression whose only operands are single lower case letters
//   (whether or not they appear in the values map), then postfix is
//   set to the postfix form of the expression; otherwise postfix may
//   or may not be changed, result is unchanged, and the function
//   returns 1.  If infix is syntactically valid but contains at
//   least one lower case letter operand that does not appear in the
//   values map, then result is unchanged and the function returns 2.
//   If infix is syntactically valid and all its lower case operand
//   letters appear in the values map, then if evaluating the
//   expression (using for each letter in the expression the value in
//   the map that corresponds to it) attempts to divide by zero, then
//   result is unchanged and the function returns 3; otherwise,
//   result is set to the value of the expression and the function
//   returns 0.

int pemdas(const char input);
//function to determine precedence

int main() {
    return 0;
}

int pemdas(const char input) { //function to determine precedence
    if(input == '(' || input == ')')
        return 0;
    if(input == '+' || input == '-')
        return 1;
    if(input == '*' || input == '/')
        return 2;
    return 3;
}

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    postfix = "";
    stack<char> o_stack;
    for(int i = 0; i < infix.size(); i++) {
        char test = infix[i];
        if(!islower(test) && test != '(' && test != ')' && test != '+' && test != '-' && test != '*' && test != '/' ) {
            return 1;
        }
        
        string mystring = string(1, test);
        if(!values.contains(mystring)) {
            return 2;
        }
        
        if(test == '/' && infix[i+1] == 0)
            return 3;
    }
    
    for(int i = 0; i < infix.size(); i++) {
        char t_char = infix[i];
        switch (t_char) {
                case '(':
                o_stack.push(t_char);
                break;
            case ')':
                // pop stack until matching '('
                while(o_stack.top() != '(') {
                    postfix = postfix + o_stack.top();
                    o_stack.pop();
                    o_stack.pop();
                    break;
                }
            case '+':
                while((!o_stack.empty()) && (o_stack.top() != '(') &&
                      (pemdas(t_char) <= pemdas(o_stack.top()))) {
                    postfix = postfix + o_stack.top();
                    o_stack.pop();
                }
                o_stack.push(t_char);
                break;
        }
    }
    
    while(!o_stack.empty()) {
        postfix = postfix + o_stack.top();
        o_stack.pop();
    }
    
    stack<char> operand_stack;
    int res = 0;
    for(int i = 0; i < postfix.size(); i++) {
        char t_char = postfix[i];
        if(t_char != '+' && t_char != '-' && t_char != '*' && t_char != '/') {
            operand_stack.push(t_char);
        }
        else {
            char operand2 = operand_stack.top();
            operand_stack.pop();
            char operand1 = operand_stack.top();
            KeyType k = string(1, operand2);
            ValueType v;
            values.get(k, v);
            KeyType l = string(1, operand1);
            ValueType w;
            values.get(l, w);
            ValueType x = v + w;
            res += x;
            switch(t_char) {
                case '+':
                    operand_stack.push(operand1 + operand2);
                    break;
                case '-':
                    operand_stack.push(operand1 - operand2);
                    break;
                case '*':
                    operand_stack.push(operand1 * operand2);
                    break;
                case '/':
                    operand_stack.push(operand1 / operand2);
                    break;
            }
        }
    }
    result = res; //I did this as a safety net since I have no idea what using an operator on a char does, and if it will actually show up in the operand stack. How do you go from char to int?
    return 1;
}
