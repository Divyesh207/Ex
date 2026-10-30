#include <iostream>
#include <string>
using namespace std;

int main() {
    char stack[100];
    string exp;

    while (true) {
        int top = -1;

        cout << "\nEnter a mathematical expression (type 'exit' to quit): ";
        getline(cin, exp);

        if (exp == "exit" || exp == "EXIT" || exp == "Exit") {
            cout << "Program terminated.";
            break;
        }

        bool balanced = true;

        for (int i = 0; i < exp.length(); i++) {
            char ch = exp[i];

            if (ch == '(' || ch == '{' || ch == '[') {
                if (top == 99) {
                    balanced = false;
                    break;
                }
                stack[++top] = ch;
            }
            else if (ch == ')' || ch == '}' || ch == ']') {

                if (top == -1) {
                    balanced = false;
                    break;
                }

                char open = stack[top--];

                if ((open == '(' && ch != ')') ||
                    (open == '{' && ch != '}') ||
                    (open == '[' && ch != ']')) {
                    balanced = false;
                    break;
                }
            }
        }

        if (top != -1)
            balanced = false;

        if (balanced)
            cout << "Expression is Balanced.\n";
        else
            cout << "Expression is Unbalanced.\n";
    }

    return 0;
}