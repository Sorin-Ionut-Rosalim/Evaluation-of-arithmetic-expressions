#include <iostream>
#include <stack>
#include <initializer_list>
#include <windows.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h> 
using namespace std;


int priority(char op) {
	if (op == '^')
		return 3;
	if (op == '*' || op == '/')
		return 2;
	if (op == '+' || op == '-')
		return 1;
	return 0;

}

int cases(int a, int b, char op) {
	switch (op) {
	case '+': return a + b; break;
	case '-': return a - b; break;
	case '*': return a * b; break;
	case '/': return a / b; break;
	case '^': return pow(a, b); break;
	}
}

void menu() {
	puts("Operators allowed :");
	puts("  + -> Addition");
	puts("  - -> Substraction");
	puts("  / -> Division");
	puts("  * -> Multiplication");
	puts("  ^ -> Power");
	puts("");
	puts("Press 1 to compute an expression");
	puts("Press 0 to exit.");
	
}


int translate(string input) {
		
		int i, l;
		l = input.length();

		stack <int> values;
		stack <int> operators;

		for (i = 0; i < l; i++) {
				
			if (input[i] == ' ') {
				continue;

			}
			else if (input[i] == '(') {
					operators.push(input[i]);

			}
			else if (isdigit(input[i])) {
				int number = 0;

				while (i < l && isdigit(input[i]))
				{
					number = (number * 10) + (input[i] - '0');
					i++;

				}

				values.push(number);
				i--;

			}
			else if (input[i] == ')') {
				while (!operators.empty() && operators.top() != '(')
				{
					int b = values.top();
					values.pop();

					int a = values.top();
					values.pop();

					char op = operators.top();
					operators.pop();

					values.push(cases(a, b, op));

				}

				if (!operators.empty()) {
					operators.pop();

				}

			}
			else
			{
				while (!operators.empty() && priority(operators.top()) >= priority(input[i]))
				{
					int b = values.top();
					values.pop();

					int a = values.top();
					values.pop();

					char op = operators.top();
					operators.pop();

					values.push(cases(a, b, op));
				}

				operators.push(input[i]);

			}

		}

		while (!operators.empty())
		{
			int b = values.top();
			values.pop();

			int a = values.top();
			values.pop();

			char op = operators.top();
			operators.pop();

			values.push(cases(a, b, op));
		}

		return values.top();

}



int main() {
	char line[200];
	
	int  choice = 1;
	int ok;
	puts("Expression Evaluation");
	puts("");
	while (choice != 0 )
	{
		menu();
		cin >> choice;
		if (choice != 0) {
				cin.get();
			do {
				
				cout << "Give a VALID expression"<<endl;
				cin.getline(line, 200);
				int len = strlen(line);
				ok = 0;
				for (int i = 0; i < len; i++) {
					if (isalpha(line[i]) || line[i] == '!' || line[i] == '@' || line[i] == '#' || line[i] == '%' || line[i] == '$' || line[i] == '&') {

						ok = 1;
						memset(line, 0, 200);
					}

				}
			} while (ok == 1);

			cout << "The result of the expression is : " << translate(line) << endl;
		}
		
	}
	
	
	
}