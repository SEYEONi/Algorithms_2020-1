#include<cstdio>
#include<vector>
#include<stack>
#include<cctype>

/*���Ͽ� �ִ� ���� �ҷ����̱�*/
class Calculator
{
public:
	std::vector<char> s1; //s1: �ؽ�Ʈ ���Ͽ� �ִ� ������, �ǿ����ڸ� vector�� ����

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

/*������ �켱����*/
int OpPriority(char op)
{
	switch (op)
	{
	case '(':
		return 1; //������ �켱���� ���� ����
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3; //������ �켱���� ���� ����
	}
	return -1;
}

/*����->����*/
std::vector<char> ChangeFix(Calculator&_c)
{
	std::stack<char> o;
	std::vector<char> p;
	char op;

	for (unsigned int i = 0; i < _c.s1.size(); i++)
	{
		op = _c.s1.at(i);
		if (isdigit(op)) //���°� �ǿ����� ��� ��ȯ���� �ڸ��� �̵�
		{
			p.push_back(op);
		}
		else //op�� �����ڶ��
		{
			if (op == '(')
			{
				o.push(op);
			}
			else if (op == ')')
			{
				//���ÿ��� �����ڸ� ������ (�� ���� �� ���� ��ȯ ���� �������� �ű��.
				while (true)
				{
					char ch = o.top(); o.pop();
					if (ch == '(')
						break;
					p.push_back(ch);
				}
			}
			else //+,-,*,/ �� ��
			{
				//������ ����ִٸ� �ϴ� �������� push
				//������ top�� op���� ���ų� ������ ����o���� pop�Ѵ��� p�� push
				//������ top�� op���� ������ �׳� o�� push
				while (!o.empty() && OpPriority(o.top()) >= OpPriority(op))
				{
					char ch = o.top(); o.pop();
					p.push_back(ch);
				}
				o.push(op);
			}
		}
	}
	//���ÿ� �����ִ� �͵��� �� ��ȯ���� �ڸ��� �ű��.
	while (!o.empty())
	{
		char ch = o.top(); o.pop();
		p.push_back(ch);
	}

	return p;
	////��ȯ�� ���� ����ϱ�
	//for (unsigned int i = 0; i < p.size(); i++)
	//{
	//	printf("%c", p[i]);
	//}
}

/*���� ǥ��� ���*/
double CalPostfix(std::vector<char> _p)
{
	std::stack<double> r; //����� �����ϴ� ����, ���������δ� ����� ����� ����
	//��ü ���� Ÿ���� char���� double �� ��ȯ�ϱ�

	for (unsigned int i = 0; i < _p.size(); i++)
	{
		if (isdigit(_p.at(i)))
		{
			double n = (double)_p.at(i)-'0';
			r.push(n); //�ǿ������̸� r�� �ִ´�.
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
/*�����Լ�*/
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