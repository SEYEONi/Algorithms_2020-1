
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		fprintf(stderr, "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
    }
    FILE* input = fopen(argv[1], "r");

    int n, m, s; // n: vertex, m: edge, s: first infected computer
    int x, y, t; // y->x edge, t: time to transfer data

    vector<pair<int, int>> graph[10001];
    int visit[10001], dist[10001];
    int cnt = 0, time = 0;
    priority_queue < pair<int, int> > pq;

    // first line
    fscanf(input, "%d %d %d", &n, &m, &s);

    // initializing graph
    for(int i = 0; i<m; i++)
    {
        fscanf(input, "%d %d %d", &x, &y, &t);
        graph[y].push_back(make_pair(x, t));
    }

    fclose(input);

    for(int i = 1; i<=n; i++)
    {
        dist[i] = 1e9;
        visit[i] = 0;
    }

    pq.push({0, s}); // enter the first infected computer in priority queue
    dist[s] = 0;
    visit[s] = 1;
    cnt++;

    while(!pq.empty())
    {
        int pos_dist = pq.top().first;
        int pos = pq.top().second;
        pq.pop();
        
        for(int i = 0; i<graph[pos].size(); i++)
        {
            int next_comp = graph[pos][i].first;
            int next_time = pos_dist + graph[pos][i].second;

            if(dist[graph[pos][i].first] > next_comp)
            {
                if(visit[graph[pos][i].first] == 0)
                    cnt++;
                visit[next_comp] = 1;
                dist[graph[pos][i].first] = next_time;
                pq.push({next_time, next_comp});
            }
        }
    }

    for(int i = 1; i<= n; i++)
    {
        if (dist[i] > time && dist[i] != 1e9)
            time = dist[i];
    }

    // output file
	FILE *output = fopen( argv[2] , "w" );
	fprintf( output , "%d %d\n", cnt, time);
	fclose(output);

//    printf("%d %d\n", cnt, time);

    return 0;
}
