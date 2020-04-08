#include<cstdio>
#include<vector>
#include<stack>
#include<cctype>

/*Read formulas in file*/
class Formulas
{
public:
	std::vector<char> s1;

	void Init(const char* _fileName)
	{
		char temp;
		FILE* input = fopen(_fileName, "r");
		
		while(fscanf(input, " %c", &temp) != EOF)
		{
			s1.push_back(temp);
		}
		fclose(input);
	}
};

/*Priority of operators*/
int OpPriority(char op)
{
	switch (op)
	{
	case '(':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	}
	return -1;
}

/*infix -> postfix*/
std::vector<char> ChangeFix(Formulas&_c)
{
	std::stack<char> o;
	std::vector<char> p;
	char op;

	for (unsigned int i = 0; i < _c.s1.size(); i++)
	{
		op = _c.s1.at(i);
		if (isdigit(op)) //if 'op' is operand, move to 'p'
		{
			p.push_back(op);
		}
		else //if 'op' is operator
		{
			if (op == '(')
			{
				o.push(op);
			}
			else if (op == ')')
			{
				while (true)
				{
					char ch = o.top(); o.pop();
					if (ch == '(')
						break;
					p.push_back(ch);
				}
			}
			else
			{
				while (!o.empty() && OpPriority(o.top()) >= OpPriority(op))
				{
					char ch = o.top(); o.pop();
					p.push_back(ch);
				}
				o.push(op);
			}
		}
	}
	
	while (!o.empty())
	{
		char ch = o.top(); o.pop();
		p.push_back(ch);
	}
	return p; //return postfix formula
}

/*Calculate postfix*/
double CalPostfix(std::vector<char> _p)
{
	std::stack<double> r;
	for (unsigned int i = 0; i < _p.size(); i++)
	{
		//if '_p[i]' is operand, push 'r'
		if (isdigit(_p.at(i)))
		{
			double n = (double)_p.at(i)-'0';
			r.push(n);
		}
		//if '_p[i]' is operator, calculate 2 operands
		else
		{
			double n1, n2;
			n2 = r.top(); r.pop();
			n1 = r.top(); r.pop();

			switch (_p.at(i))
			{
			case '+':
				r.push(n1 + n2);
				break;
			case '-':
				r.push(n1 - n2);
				break;
			case '*':
				r.push(n1 * n2);
				break;
			case '/':
				r.push(n1 / n2);
				break;
			}
		}
	}
	return r.top(); //return result of calculation
}

/*Main Function*/
int main(int argc, char** argv)
{
	Formulas c;
	c.Init(argv[1]);
	std::vector<char> _p = ChangeFix(c);
	double result = CalPostfix(_p);
	
	FILE* output = fopen(argv[2], "w");
	if (output == NULL)
	{
		printf("Fail!");
		return -1;
	}
	fprintf(output, "%0.2lf", result);

	fclose(output);

	return 0;
}