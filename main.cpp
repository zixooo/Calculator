#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
using namespace std;

const double Pi = acos(-1);

double Sin(double x) {
    return (round(sin(x) * 1) / 1);
}

double Cos(double x) {
    return (round(cos(x) * 1) / 1);
}

double ctg(double x) {
    double a = Cos(x);
    double b = Sin(x);
    return (a/b);
}

struct Types {
    char type;
    double value;
};

bool flag = 1;

bool Maths(stack <Types> & stack_n, stack <Types> & stack_o, Types& item) { // производит расчеты
    double a, b, c;
    a = stack_n.top().value;// берется верхнее число их стека
    stack_n.pop(); // удаление числа из стека
    switch (stack_o.top().type) { // проверка типа верхней операции
        case '+':
            b = stack_n.top().value;
            stack_n.pop();
            c = a + b;
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case '-':
            b = stack_n.top().value;
            stack_n.pop();
            c = b - a;
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case '*':
            b = stack_n.top().value;
            stack_n.pop();
            c = a * b;
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case '/':
            b = stack_n.top().value;
            if (a == 0) {
                cerr << "\nError!\n";
                return false;
            } else {
                stack_n.pop();
                c = b / a;
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;
            }

        case '^':
            b = stack_n.top().value;
            stack_n.pop();
            c = pow(b, a);
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case 's':
            c = Sin(a);
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case 'c':
            c = Cos(a);
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        case 't':
            if (Cos(a) == 0){
                cerr << "\ntan doesn't exist!\n";
                return false;
            }
            else {
                c = tan(a);
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;
            }

        case 'g':
            if (Sin(a) == 0) {
                cerr << "\nctg doesn't exist\n";
                return false;
            }
            else {
                c = ctg(a);
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;
            }

        case 'e':
            c = exp(a);
            item.type = '0';
            item.value = c;
            stack_n.push(item);
            stack_o.pop();
            break;

        default: // Если операция не + , - , * , /
        cerr << "\nError!\n";
        return false;
    }
    return true;
}


int Priority (char Ch) { // приоритет операций
    if (Ch == '+' || Ch == '-') return 1;
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '^') return 3;
    if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') return 4;
    else return 0;
}

int main() {
    cout << "Enter the expression: ";
    char Ch;
    double value;
    stack<Types> stack_n;
    stack<Types> stack_o;
    Types item{};
    while (true) {
        Ch = cin.peek();
        if (Ch == '\n') break;
        if (Ch == ' ') {
            cin.ignore();
            continue;
        }
        if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'g' || Ch == 'e') {
            char foo[3];
            for (int i = 0; i < 3; i++) {
                Ch = cin.peek();
                foo[i] = Ch;
                cin.ignore();
            }

            if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') {
                item.type = 's';
                item.value = '0';
                stack_o.push(item);
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') {
                item.type = 'c';
                item.value = '0';
                stack_o.push(item);
                continue;
            }
            if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') {
                item.type = 't';
                item.value = '0';
                stack_o.push(item);
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') {
                item.type = 'g';
                item.value = '0';
                stack_o.push(item);
                continue;
            }
            if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
                item.type = 'e';
                item.value = '0';
                stack_o.push(item);
                continue;
            }

        }
        if (Ch == 'p') { // если прочитано число
            item.type = '0';
            item.value = Pi;
            stack_n.push(item);
            flag = 0;
            cin.ignore();
            continue;
        }
        if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1 ){
                cin >> value;
                item.type = '0';
                item.value = value;
                stack_n.push(item);
                flag = 0;
                continue;
            }

        if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/' || Ch == '^') { // если прочитана операция
            if (stack_o.size() == 0) { // если стек с операциями пуст
                item.type = Ch;
                item.value = '0';
                stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (stack_o.size() != 0 && Priority(Ch) > Priority(stack_o.top().type)) {
                item.type = Ch;
                item.value = '0';
                stack_o.push(item);
                cin.ignore();
                continue;
            }
            if (stack_o.size() != 0 && Priority(Ch) <= Priority(stack_o.top().type)) {
                if (!Maths(stack_n, stack_o, item)) {
                    system("pause");
                    return 0;
                }
                continue;
        }
        }
        if (Ch == '(') {
            item.type = Ch;
            item.value = '0';
            stack_o.push(item);
            cin.ignore();
            continue;
        }
        if (Ch == ')') {
            while(stack_o.top().type != '(') {
                if (!Maths(stack_n, stack_o, item)) { // прекращние работы если false
                    system("pause");
                    return 0;
                }
                else continue;
            }
            stack_o.pop();
            cin.ignore();
            continue;
        }
        else {
            cout << "\nIncorrect expression!\n";
            system("pause");
            return 0;
        }
    }
        while (stack_o.size() != 0) {
            if (!Maths(stack_n, stack_o, item)) { // прекращние работы если false
                system("pause");
                return 0;
            } else continue;
        }
        cout << "Result: " << stack_n.top().value << endl;
        return 0;
}

#pragma clang diagnostic pop