#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    explicit Node(T val, Node<T> *nextptr = nullptr) : data(val), next(nextptr) {}
};
template <typename T>
class Stack
{
private:
    Node<T> *top;

public:
    Stack() : top(nullptr){};

    void push(T val)
    {
        auto *temp = new Node<T>(val);
        temp->next = top;
        top = temp;
    }

    T pop()
    {
        if (top == nullptr)
            return '1';
        else
        {
            Node<T> *temp = top;
            top = top->next;
            temp->next = nullptr;
            T x = temp->data;
            delete temp;
            return x;
        }
    }

    bool isEmpty()
    {
        return top == nullptr ? true : false;
    }

    T getTop()
    {
        return top->data;
    }
};
int precedence(char c)
{

    if (c == '/' || c == '*')
        return 3;
    else if (c == '^')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
int associativity(char c)
{
    if (c == '/' || c == '*')
    {
        if (c == '*')
            return 2;
        else
            return 1;
    }
    else if (c == '+' || c == '-')
    {
        if (c == '+')
            return 2;
        else
            return 1;
    }
}
float calculate(float a, float b, char x)
{
    if (x == '*')
        return a * b;
    else if (x == '/')
        return a / b;
    else if (x == '+')
        return a + b;
    else if (x == '-')
        return a - b;
    else if (x == '^')
        return pow(b, a);
    return 0;
}
int main()
{
    Stack<char> operator_stk;
    Stack<float> operand_stk;

    string exp;
    cout << "Enter a expression: ";
    getline(cin, exp);
    for (auto i : exp)
    {
        if (i >= '0' && i <= '9')
        {
            cout << i;
            operand_stk.push(i);
        }
        else
        {
            while (!operator_stk.isEmpty() && precedence(i) <= precedence(operator_stk.getTop()))
            {
                if (precedence(i) == precedence(operator_stk.getTop()))
                {
                    if (associativity(i) <= associativity(operator_stk.getTop()))
                    {
                        while (!operator_stk.isEmpty() && associativity(i) <= associativity(operator_stk.getTop()))
                        {
                            float a, b;
                            a = operand_stk.pop() - 48;
                            b = operand_stk.pop() - 48;
                            float result1 = calculate(a, b, operator_stk.getTop());
                            operand_stk.push(result1 + 48);
                            cout << operator_stk.pop();
                        }
                    }
                    else
                        break;
                }
                else
                {
                    float a, b;
                    a = operand_stk.pop() - 48;
                    b = operand_stk.pop() - 48;
                    float result1 = calculate(a, b, operator_stk.getTop());
                    operand_stk.push(result1 + 48);
                    cout << operator_stk.pop();
                }
            }
            operator_stk.push(i);
        }
    }
    while (!operator_stk.isEmpty())
    {
        float a, b;
        b = operand_stk.pop() - 48;
        a = operand_stk.pop() - 48;
        float result1 = calculate(a, b, operator_stk.getTop());
        operand_stk.push(result1 + 48);
        cout << operator_stk.pop();
    }

    cout << "\nEvaluation of expression is: " << operand_stk.pop() - 48;
    return 0;
}