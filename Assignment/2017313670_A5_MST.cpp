#include<cstdio>
#include<algorithm>
//#include<cstring>
//#include<string>
#include<vector>
#include<queue>
using namespace std;

int findroot(int node, int *parent)
{
    if(node == parent[node])
        return node;
    return parent[node] = findroot(parent[node], parent);
}

void merge(int node1, int node2, int *parent, int *size)
{
    node1 = findroot(node1, parent);
    node2 = findroot(node2, parent);

    if(node1 != node2)
    {
        if(size[node1] < size[node2])
            swap(node1, node2);

        parent[node2] = node1;
        size[node1] += size[node2];
        size[node2] = 0;
    }
}

struct Edge {
    int v1, v2, cost;

    bool operator<(Edge const &e)
    {
        return cost < e.cost;
    }
};

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		fprintf(stderr, "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
    }
    FILE* input = fopen(argv[1], "r");

    int n, m; // n: Vertex m: Edge
    fscanf(input, "%d %d", &n, &m);

    vector<Edge> edge;
    for(int i = 0; i< m; i++)
    {
        int a, b, c; // the graph has an edge between vertices 'a' and 'b' with cost of 'c'
        fscanf(input, "%d %d %d", &a, &b, &c);

        edge.push_back({a, b, c});
    }
    fclose(input);

    //sort ascending order by cost of the edge
    sort(edge.begin(), edge.end());

    int parent[10001], size[10001];
    int ans = 0; // answer

    for(int i = 0; i<n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }

    for(int i = 0; i<edge.size(); i++)
    {
        Edge e = edge[i];

        if(findroot(e.v1, parent) != findroot(e.v2, parent))
        {
            ans += e.cost;
            merge(e.v1, e.v2, parent, size);
        }
    }

//    printf("%d\n", ans);

    // output file
	FILE *output = fopen( argv[2] , "w" );
    fprintf(output, "%d", ans);
    fclose(output);

    return 0;
}