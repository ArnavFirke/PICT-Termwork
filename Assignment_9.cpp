#include <iostream>
#include <string>
using namespace std;
#define size 10
class Stack
{
private:
    int top;
    char stk[size];

public:
    Stack()
    {
        top = -1;
    }

    void push(char);
    char pop();
    char getTop();
    bool isfull();
    bool isempty();
    void check(string, int);
};

char Stack::getTop()
{
    if (isempty())
    {
        cout << "Stack is Empty" << endl;
    }
    else
    {
        return stk[top];
    }
}

void Stack::push(char x)
{
    if (isfull())
    {
        cout << "Stack is Full" << endl;
        return;
    }
    else
    {
        top = top + 1;
        stk[top] = x;
    }
}

char Stack::pop()
{
    if (isempty())
    {
        cout << "Stack is Empty" << endl;
    }
    else
    {
        char s;
        s = stk[top];
        top = top - 1;
        return s;
    }
}

bool Stack::isfull()
{
    if (top == size)
        return true;
    else
        return false;
}

bool Stack::isempty()
{
    if (top == -1)
        return true;
    else
        return false;
}

void Stack::check(string arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == '[' || arr[i] == '{' || arr[i] == '(')
        {
            push(arr[i]);
            cout << "PUSHING " << arr[i] << endl;
        }

        else
        {
            if (arr[i] == ')')
            {
                if (!isempty())
                {
                    if (getTop() == '(')
                    {
                        cout << "POPING " << getTop() << endl;
                        pop();
                    }
                    else
                    {
                        cout << "Matching opening brace '(' is not found" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "Stack is Empty" << endl;
                    return;
                }
            }
            if (arr[i] == ']')
            {
                if (!isempty())
                {
                    if (getTop() == '[')
                    {
                        cout << "POPING " << getTop() << endl;
                        pop();
                    }
                    else
                    {
                        cout << "Matching opening brace '[' is not found" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "Stack is Empty" << endl;
                    return;
                }
            }
            if (arr[i] == '}')
            {
                if (!isempty())
                {
                    if (getTop() == '{')
                    {
                        cout << "POPING " << getTop() << endl;
                        pop();
                    }
                    else
                    {
                        cout << "Matching opening brace '{' is not found" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "Stack is Empty" << endl;
                    return;
                }
            }
        }
    }
    if (isempty())
    {
        cout << "Expression is well parenthesized " << endl;
    }
}

int main()
{
    string exp;
    cout << "Enter the Expression: ";
    getline(cin, exp);
    Stack s;
    s.check(exp, exp.length());

    return 0;
}