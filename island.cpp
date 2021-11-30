#include <bits/stdc++.h>
using namespace std;

int find(int i, vector<int> &parent)
{
    int p = i;
    while(parent[p] >= 0)
        p = parent[p];
    return p;
}

void Union(int i, int j, vector<int> &parent)
{
    int u = find(i, parent), v = find(j, parent);
    if(u == v)
        return;
    if(parent[u] <= parent[v])
    {
        parent[u] += parent[v];
        parent[v] = u;
    }
    else
    {
        parent[v] += parent[u];
        parent[u] = v;
    }
}

int countIslands(vector< vector<int> > mat, int n, int m)
{
    vector<int> parent(n*m, -1);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(mat[i][j] == 0)
                continue;
            int node = i * m + j;
            if(i-1 >= 0)
            {
                if(mat[i-1][j] == 1)
                    Union(node, (i-1)*m + j, parent);
                if(j-1 >= 0 && mat[i-1][j-1] == 1)
                    Union(node, (i-1)*m + j - 1 , parent);
                if(j+1 < m && mat[i-1][j+1] == 1)
                    Union(node, (i-1)*m + j + 1, parent);
            }
            if(i+1 < n)
            {
                if(mat[i+1][j] == 1)
                    Union(node, (i+1)*m + j, parent);
                if(j-1 >= 0 && mat[i+1][j-1] == 1)
                    Union(node, (i+1)*m + j - 1 , parent);
                if(j+1 < m && mat[i+1][j+1] == 1)
                    Union(node, (i+1)*m + j + 1, parent);
            }
            if(j-1 >= 0 && mat[i][j-1] == 1)
                Union(node, i*m + j - 1, parent);
            if(j+1 < n && mat[i][j+1] == 1)
                Union(node, i*m + j + 1, parent);
        }
    }
    int count = 0;
    vector<bool> flag(n*m);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(mat[i][j] == 1)
            {
                int par = find(i*m + j, parent);
                if(!flag[par])
                {
                    count++;
                    flag[par] = true;
                }
            }
        }
    }
    return count;
}

int main()
{
    int n = 5, m = 5;
    vector< vector<int> > mat = {{1, 1, 0, 0, 0},
                                 {0, 1, 1, 0, 1},
                                 {1, 0, 0, 1, 1},
                                 {0, 0, 0, 0, 0},
                                 {1, 1, 1, 1, 1}};
    cout << "Number of Islands = " << countIslands(mat, n, m);
    return 0;
}


