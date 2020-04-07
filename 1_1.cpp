#include<cstdio>
#include<vector>
#include<queue>

//knight의 좌표
typedef struct
{
	int x, y;
}Pos;

class InputData
{
public:
	int n=0; //보드판의 크기 (n x n)
	std::vector<std::vector<int>> chess; //체스판 할당

	Pos s = { 0,0 }; //시작 위치 start
	Pos d = { 0,0 }; //도착 위치 destination
	Pos mov[8] = { {-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1} };
	/*input.txt 읽어서 좌표 저장하기*/
	void input(const char* _fileName)
	{
		FILE* input = fopen(_fileName, "r");
		fscanf(input, "%d", &n);
		/* n x n 체스판 생성, 현재 0으로 초기화 */
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
	_i.chess[_i.s.x][_i.s.y]++; //시작점은 이미 방문한 것이므로 +1 해준다.

	/*큐가 빌때까지*/
	while (!q.empty())
	{
		int x = q.front().second.x;
		int y = q.front().second.y;
		int cnt = q.front().first;;
		q.pop();

		/*도착지점에 도달했으면 이동횟수 출력*/
		if (x == _i.d.x && y == _i.d.y)
		{
			printf("최소이동횟수: %d\n", cnt);
			return cnt;
		}
		/*8개 방향으로 이동 진행*/
		for (int i = 0; i < 8; i++)
		{
			int nx = x + _i.mov[i].x;
			int ny = y + _i.mov[i].y;

			if (0 <= nx && nx < _i.n && 0 <= ny && ny < _i.n) //체스판 내에서만 이동한다.
			{
				if (_i.chess[nx][ny] != 1) //방문한 적이 없으면
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