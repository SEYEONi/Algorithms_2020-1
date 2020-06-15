#include<cstdio>
#include<vector>
#include<queue>

/*coordinates of knights*/
typedef struct
{
	int x; //vertical
	int y; //horizontal
}Pos;

class InputData
{
public:
	int n=0; //size of board
	std::vector<std::vector<int>> chess; //allocate board

	Pos s = { 0,0 }; //starting point
	Pos d = { 0,0 }; //destination
	Pos mov[8] = { {-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1} }; //the direction of the knight can move
	
	void input(const char* _fileName)
	{
		FILE* input = fopen(_fileName, "r");
		fscanf(input, "%d", &n);
		
		//make n x n chess board*/
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

/*find the minimum number of steps taken by a Knight to reach, 'starting point'->'destination'*/
int BFS(InputData& _i)
{
	std::queue<std::pair<int, Pos>> q;
	int cnt = 0;
	q.push(std::make_pair(cnt, _i.s));
	_i.chess[_i.s.x][_i.s.y]++;

	while (!q.empty())
	{
		int x = q.front().second.x;
		int y = q.front().second.y;
		int step = q.front().first;;
		q.pop();

		/*when arrived at destination, return nummber of steps*/
		if (x == _i.d.x && y == _i.d.y)
		{
			return step;
		}
		/*Knights can move 8 directions*/
		for (int i = 0; i < 8; i++)
		{
			int nx = x + _i.mov[i].x;
			int ny = y + _i.mov[i].y;

			if (0 <= nx && nx < _i.n && 0 <= ny && ny < _i.n) //move in n x n
			{
				if (_i.chess[nx][ny] != 1)
				{
					q.push(std::make_pair(step + 1, Pos{ nx, ny }));
					_i.chess[nx][ny]++;
				}
			}
		}
	}
	return -1; //if the destination is unreachable return '-1'
}

/*Main Function*/
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
