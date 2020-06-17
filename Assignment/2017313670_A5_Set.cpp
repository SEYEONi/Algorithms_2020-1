#include<cstdio>
#include<vector>
using namespace std;

//vector<int>root;

int find(int node, vector<int> &_root) {
    if(_root[node] == node)
        return node;
    else
        return _root[node] = find(_root[node], _root);
}

void uni(int a, int b, vector<int> &_root) {
    int _a = find(a, _root);
    int _b = find(b, _root);
    _root[_b] = _a;
}

int main(int argc, char** argv)
{
    if (argc != 3)
	{
		fprintf(stderr, "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
    }
    FILE* input = fopen(argv[1], "r");

    int n, m;
    fscanf(input, "%d %d", &n, &m);
    vector<int>root;

    for(int i = 0; i <= n; i++)
        root.push_back(i);

    int op, a, b;
    int count = 0;
    vector<char>answer;

    for(int i = 0; i<m; i++)
    {
        fscanf(input, "%d %d %d", &op, &a, &b);

        if(op == 0)
            uni(a, b, root);
        else
        {
            if(find(a, root) == find(b, root))
                answer.push_back('Y');
            else
                answer.push_back('N');
        }    
    }
    fclose(input);

    // output file
    FILE *output = fopen( argv[2] , "w" );
    for(int i = 0; i<answer.size(); i++)
        fprintf(output, "%c\n", answer.at(i));

    fclose(output);

    return 0;
}
