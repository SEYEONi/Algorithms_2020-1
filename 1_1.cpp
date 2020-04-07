#include<cstdio>
#include<vector>
#include<queue>

//knight�� ��ǥ
typedef struct
{
	int x, y;
}Pos;

class InputData
{
public:
	int n=0; //�������� ũ�� (n x n)
	std::vector<std::vector<int>> chess; //ü���� �Ҵ�

	Pos s = { 0,0 }; //���� ��ġ start
	Pos d = { 0,0 }; //���� ��ġ destination
	Pos mov[8] = { {-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1} };
	/*input.txt �о ��ǥ �����ϱ�*/
	void input(const char* _fileName)
	{
		FILE* input = fopen(_fileName, "r");
		fscanf(input, "%d", &n);
		/* n x n ü���� ����, ���� 0���� �ʱ�ȭ */
		for (int i = 0; i < n; i++)
		{
			std::vector<int>element(n);
			chess.push_back(element);
		}
		fscanf(input, "%d %d", &s.x, &s.y);
		fscanf(input, "%d %d", &d.x, &d.y);

		fclose(input);
	}

};

int BFS(InputData& _i)
{
	std::queue<std::pair<int, Pos>> q;
	int cnt = 0;
	q.push(std::make_pair(cnt, _i.s));
	_i.chess[_i.s.x][_i.s.y]++; //�������� �̹� �湮�� ���̹Ƿ� +1 ���ش�.

	/*ť�� ��������*/
	while (!q.empty())
	{
		int x = q.front().second.x;
		int y = q.front().second.y;
		int cnt = q.front().first;;
		q.pop();

		/*���������� ���������� �̵�Ƚ�� ���*/
		if (x == _i.d.x && y == _i.d.y)
		{
			printf("�ּ��̵�Ƚ��: %d\n", cnt);
			return cnt;
		}
		/*8�� �������� �̵� ����*/
		for (int i = 0; i < 8; i++)
		{
			int nx = x + _i.mov[i].x;
			int ny = y + _i.mov[i].y;

			if (0 <= nx && nx < _i.n && 0 <= ny && ny < _i.n) //ü���� �������� �̵��Ѵ�.
			{
				if (_i.chess[nx][ny] != 1) //�湮�� ���� ������
				{
					q.push(std::make_pair(cnt + 1, Pos{ nx, ny }));
					_i.chess[nx][ny]++;
				}
			}
		}
	}
	return -1;
}


int main(int argc, char** argv)
{
	InputData i;
	i.input(argv[1]);
	int result = BFS(i);

	FILE* output = fopen(argv[2], "w");
	if(output == NULL)
	{
		printf("Fail!");
		return -1;
	}
	fprintf(output, "%d", result);
	fclose(output);
	return 0;
}