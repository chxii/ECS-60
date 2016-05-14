
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"
#include "QuadraticProbing.h"
#include "QueueAr.h"
#include <cstring>


class store
{
public:
	char addr[16];
	store() {}

};

class MaxFinder
{
public:
	store s[5000];
	int numComp;
	int numTerm;
	MaxFinder( Computer *computers, int numComputers, int numTerminals);
	int min(int a, int b);
	int convertToNum(char string[]);
	bool bfs(AdjList ar[], int s, int t, int path[]);
	int calcMaxFlow(Edge *edges, int numEdges);


}; // class MaxFinder




#endif
