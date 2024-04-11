#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void applyOp(stack<double>& numbers, char op) {
    double b = numbers.top(); numbers.pop();
    double a = numbers.top(); numbers.pop();
    double result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        case '^': result = pow(a, b); break;
    }
    numbers.push(result);
}

double evaluateExpression(const string& expression) {
    stack<double> numbers;
    stack<char> ops;

    istringstream iss(expression);
    char token;
    while (iss >> token) {
        if (isdigit(token) || token == '.') {
            iss.putback(token);
            double num;
            iss >> num;
            numbers.push(num);
        } else if (isOperator(token)) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                applyOp(numbers, ops.top());
                ops.pop();
            }
            ops.push(token);
        } else if (token == '(') {
            ops.push(token);
        } else if (token == ')') {
            while (ops.top() != '(') {
                applyOp(numbers, ops.top());
                ops.pop();
            }
            ops.pop(); // Pop '('
        }
    }

    while (!ops.empty()) {
        applyOp(numbers, ops.top());
        ops.pop();
    }

    return numbers.top();
}

int main() {
    cout << "Simple Console Calculator\n";
    cout << "Enter 'q' to quit.\n";

    while (true) {
        string expression;
        cout << "Enter an expression: ";
        getline(cin, expression);

        if (expression == "q")
            break;

        try {
            double result = evaluateExpression(expression);
            cout << "Result: " << result << endl;
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
