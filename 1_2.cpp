#include<cstdio>
#include<vector>
#include<stack>
#include<cctype>

/*파일에 있는 수식 불러들이기*/
class Calculator
{
public:
	std::vector<char> s1; //s1: 텍스트 파일에 있는 연산자, 피연산자를 vector에 저장

	void Init(const char* _fileName)
	{
		char temp;
		int ret;
		FILE* input = fopen(_fileName, "r");
		while ((ret = fscanf(input, "%c", &temp)) != EOF)
		{
			s1.push_back(temp);
		}
		fclose(input);
				
	}
};

/*연산자 우선순위*/
int OpPriority(char op)
{
	switch (op)
	{
	case '(':
		return 1; //연산자 우선순위 가장 낮음
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3; //연산자 우선순위 가장 높음
	}
	return -1;
}

/*중위->후위*/
std::vector<char> ChangeFix(Calculator&_c)
{
	std::stack<char> o;
	std::vector<char> p;
	char op;

	for (unsigned int i = 0; i < _c.s1.size(); i++)
	{
		op = _c.s1.at(i);
		if (isdigit(op)) //들어온게 피연산자 라면 변환수식 자리로 이동
		{
			p.push_back(op);
		}
		else //op가 연산자라면
		{
			if (op == '(')
			{
				o.push(op);
			}
			else if (op == ')')
			{
				//스택에서 연산자를 꺼내서 (를 만날 때 까지 변환 수식 공간으로 옮긴다.
				while (true)
				{
					char ch = o.top(); o.pop();
					if (ch == '(')
						break;
					p.push_back(ch);
				}
			}
			else //+,-,*,/ 일 때
			{
				//스택이 비어있다면 일단 스택으로 push
				//스택의 top이 op보다 높거나 같으면 스택o에서 pop한다음 p로 push
				//스택의 top이 op보다 낮으면 그냥 o로 push
				while (!o.empty() && OpPriority(o.top()) >= OpPriority(op))
				{
					char ch = o.top(); o.pop();
					p.push_back(ch);
				}
				o.push(op);
			}
		}
	}
	//스택에 남아있는 것들을 다 변환수식 자리로 옮긴다.
	while (!o.empty())
	{
		char ch = o.top(); o.pop();
		p.push_back(ch);
	}

	return p;
	////변환된 수식 출력하기
	//for (unsigned int i = 0; i < p.size(); i++)
	//{
	//	printf("%c", p[i]);
	//}
}

/*후위 표기법 계산*/
double CalPostfix(std::vector<char> _p)
{
	std::stack<double> r; //결과를 저장하는 과정, 마지막으로는 결과가 저장될 스택
	//전체 스택 타입을 char에서 double 로 변환하기

	for (unsigned int i = 0; i < _p.size(); i++)
	{
		if (isdigit(_p.at(i)))
		{
			double n = (double)_p.at(i)-'0';
			r.push(n); //피연산자이면 r에 넣는다.
		}
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
	return r.top();
}
/*메인함수*/
int main(int argc, char** argv)
{
	Calculator c;
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