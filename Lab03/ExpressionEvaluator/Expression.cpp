#include <string>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;

void reverseString(string& str) {
    stack<int> stk;

    for (char ch : str) stk.push(ch);

    for (int i = 0; i < str.length(); i++) {
        str[i] = stk.top();
        stk.pop();
    }
}

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
#include <iostream>
#include <stack>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPrecedence(char op) {
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0; // '('
}

string Infix2Postfix(string& s) {
    stack<char> operatorStack;
    string result;

    for (int i = 0; i < s.length(); ++i) {
        char& c = s[i];

        if (isdigit(c)) {
            // (1) Operand: Output it
            string operand;
            while (i < s.length() && isdigit(s[i])) {
                operand += s[i];
                ++i;
            }
            result += ' ';
            result += operand;
            result += ' ';
            // Bir sonraki karakteri kontrol etmek için döngüde artırıyoruz
            --i;
        }
        else if (c == '(') {
            // (2) '(': Push it
            operatorStack.push(c);
        }
        else if (c == ')') {
            // (3) ')': Pop operators until '(' is encountered
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                result += ' ';
                result += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); // Pop '('
        }
        else if (isOperator(c)) {
            // (4) Operator: Pop operators with higher or equal precedence
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                result += ' ';
                result += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    // (5) Pop remaining operators from the stack
    while (!operatorStack.empty()) {
        result += ' ';
        result += operatorStack.top();
        operatorStack.pop();
    }

    return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	stringstream ss(s);
	stack<int> st,tempst;
	stack<char> op,tempop;
	string token;
	while (ss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			op.push(token[0]);
		}
		else {
			st.push(stoi(token));
		}
	}
    while (!st.empty()) {
        tempst.push(st.top());
        st.pop();
    }
    st=tempst;
    while (!op.empty()) {
        tempop.push(op.top());
        op.pop();
    }
    op=tempop;

	while (!op.empty()) {
		if (op.top()=='*'){
			int a = 0, b = 0;
			a = st.top();
            cout << a << endl;
			st.pop();
			b = st.top();
			cout << b << endl;
			st.pop();
			st.push(a * b);
			op.pop();
            cout << st.top()<<endl;
		}
		else if (op.top() == '/') {
			int a = 0, b = 0;
			a = st.top();
            cout << a << endl;
			st.pop();
			b = st.top();
            cout << b << endl;
			st.pop();
			st.push(b / a);
			op.pop();
            cout << st.top() << endl;
		}
		else if (op.top() == '+') {
			int a = 0, b = 0;
			a = st.top();
            cout << a << endl;
			st.pop();
			b = st.top();
            cout << b << endl;
			st.pop();
			st.push(a + b);
			op.pop();
            cout << st.top() << endl;
		}
		else if (op.top() == '-') {
			int a = 0, b = 0;
			a = st.top();
            cout << a << endl;
			st.pop();
			b = st.top();
            cout << b << endl;
			st.pop();
			st.push(b - a);
			op.pop();
            cout << st.top() << endl;
		}
	}
    cout << st.top() << endl;
	return st.top();
} // end-EvaluatePostfixExpression
