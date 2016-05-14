

#include "NetDriver.h"
#include "maxfinder.h"




MaxFinder::MaxFinder(Computer *computers, int numComputers, int numTerminals)
{

    for (int i = 0; i < numComputers; i++)
        strcpy(s[i].addr, computers[i].address);

    numComp = numComputers;
    numTerm = numTerminals;
} // MaxFinder()

bool MaxFinder::bfs(AdjList ar[], int s, int t, int path[])
{
    bool visited[numComp + 1];
    memset(visited, 0, sizeof(visited));

    Queue <int> q(5000);
    q.enqueue(s);
    visited[ar[s].index] = true;
    path[ar[s].index] = -1;

    while (!q.isEmpty())
    {
        int u = q.dequeue();

        for (int i = 0; i < ar[u].size; i++)
        {
            int nextIndex = ar[u].adj[i].index ;

            if (visited[nextIndex] == false && ar[u].adj[i].capacity > 0)
            {
                q.enqueue(nextIndex);                
                path[nextIndex] = u;
                visited[nextIndex] = true;
            }
        }
    }

    return (visited[t] == true);
}


int MaxFinder::min(int a, int b)
{
    if (a < b)
        return a;
    else 
        return b;
}

int MaxFinder::convertToNum(char string[])
{
    char *pch;
    int temp[4];
    int count = 0;
    pch = strtok(string, ".");
    while (pch != NULL)
    {
        temp[count++] = atoi(pch);
        pch = strtok(NULL, ".");
    }
    return((temp[0]<<24) + (temp[1]<<16) + (temp[2]<<8) + temp[3]);
}



int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{
    int comp[5000];

    //convert char IP to unique integers
    for(int i = 0; i < numComp; i++)
        comp[i] = convertToNum(s[i].addr);

    //a hash table to store all computers 
    AdjList m(0, -1, 0);
    QuadraticHashTable hash(m, 5001); 

    //creating a fake start point
    AdjList newList(0);
    AdjListNode * ps= new AdjListNode[numTerm];
    newList.adj = ps ;
    newList.size = numTerm;

    for (int i = 0; i < numTerm; i++)
        newList.adj[i] = AdjListNode(comp[i], 99999999, i + 1);

    hash.insert(newList);

    //first insert all computers to AdjList
    for (int i = 0; i < numComp; i++)
    {
        AdjList newList(0, comp[i], i + 1);
        hash.insert(newList);
    }

    //add adjancency
    for (int i = 0; i < numEdges; i++)
    {
        int c1, c2;
        c1 = convertToNum(edges[i].src);
        c2 = convertToNum(edges[i].dest);

        AdjList to_find(c1);
        AdjList &found = hash.find(to_find);
        AdjList find_c2 = hash.find(AdjList(c2));
        found.adj[found.size] = AdjListNode(c2, edges[i].capacity, find_c2.index);
        found.size++;
    }


    //change hash to an array of AdjList (for speed)
    AdjList ar[5001];
    AdjList first(0);
    AdjList found_first = hash.find(first);
    ar[0] = found_first;
    for (int i = 0; i < 5000; i++)
    {
        AdjList to_find(comp[i]);
        AdjList found = hash.find(to_find);
        ar[i + 1] = found;
    }

    //find max flow (bfs to find path)
    int start = 0;
    int end = numComp;
    int path[10000]; 
    int max_flow = 0;

    while (bfs(ar, start, end, path))
    {

        int path_flow = 99999999;

        //find path flow
        for (int v = numComp; v != 0; v = path[v])
        {

            int u = path[v];
            int c = comp[v - 1];
            int temp_flow = ar[u].findSrc(c);
            path_flow = min(path_flow, temp_flow);

        }

        //update graph
        for (int v = numComp; v != 0; v = path[v])
        {
            int u = path[v];//going from u to v
            int b = comp[u - 1];// b is u
            int c = comp[v - 1];//c is v
            ar[u].minusSrc(c, path_flow);//find c in adj of u(b) 
            
            //check if already have back flow
            if (ar[v].findSrc(b) == -1)
            {
                AdjListNode ttt(b, path_flow, ar[u].index);
                ar[v].adj[ar[v].size] = ttt;
                ar[v].size++;
            }
            else 
                ar[v].plusSrc(b,path_flow);
            
        }

        max_flow += path_flow;
    }

    return max_flow;
} // calcMaxFlow()

