#include<cstdio>
#include<vector>
#include<stack>
#include<cctype>

/*���Ͽ� �ִ� ���� �ҷ����̱�*/
class Calculator
{
public:
	std::vector<int> s1; //s1: �ؽ�Ʈ ���Ͽ� �ִ� ������, �ǿ����ڸ� vector�� ����

	void Init(const char* _fileName)
	{
		char temp;
		FILE* input = fopen(_fileName, "r");
		while (fscanf(input, "%c", &temp) != EOF)
		{
			s1.push_back(temp);
		}
		fclose(input);
				
	}
};

class ChangeFix
{
public:
	std::stack<int> o; //postfix(����ǥ���)���� ������ �� �ʿ��� ���
	std::vector<int> p; //postfix(����ǥ���)���� ����� ������ ���� ����

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

	/*����ǥ��� -> ����ǥ��� ��ȯ*/
	void Change(Calculator& _c)
	{
		//std::stack<char> o; //postfix(����ǥ���)���� ������ �� �ʿ��� ���
		//std::vector<char> p; //postfix(����ǥ���)���� ����� ������ ���� ����
		char op;

		for (unsigned int i = 0; i < _c.s1.size(); i++)
		{
			op = _c.s1[i];
			//printf("%c", op);
			if (isdigit(op)) //���°� �ǿ����� ��� ��ȯ���� �ڸ��� �̵�
			{
				p.push_back(op);
				//for (unsigned int i = 0; i < p.size(); i++)
				//{
				//	printf("%c", p[i]);
				//}

			}
			else //op�� �����ڶ��
			{
				if (op == '(')
				{
					o.push(op);
					//printf("%c", o.top());
				}
				else if (op == ')')
				{
					//printf("%c", o.top());
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
						int ch = o.top(); o.pop();
						p.push_back(ch);
					}
					o.push(op);
				}
			}
		}
		//���ÿ� �����ִ� �͵��� �� ��ȯ���� �ڸ��� �ű��.
		while (!o.empty())
		{
			int ch = o.top(); o.pop();
			p.push_back(ch);
		}

		////��ȯ�� ���� ����ϱ�
		//for (unsigned int i = 0; i < p.size(); i++)
		//{
		//	printf("%c", p[i]);
		//}
	}
};

/*���� ǥ��� ���*/
double CalPostfix(Calculator& _c)
{
	ChangeFix ch;
	ch.Change(_c);

	//��ȯ�� ���� ����ϱ�
	//for (unsigned int i = 0; i < ch.p.size(); i++)
	//{
	//	printf("%c", ch.p[i]);
	//}
	//printf("\n");

	std::stack<double> r; //����� �����ϴ� ����, ���������δ� ����� ����� ����

	for (unsigned int i = 0; i < ch.p.size(); i++)
	{
		if (isdigit(ch.p[i]))
		{
			int n = ch.p[i]-'0';
			r.push(n); //�ǿ������̸� r�� �ִ´�.
		}
		else
		{
			double n1, n2;
			n2 = r.top(); r.pop();
			n1 = r.top(); r.pop();

			switch (ch.p[i])
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
	double result = CalPostfix(c);
	
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