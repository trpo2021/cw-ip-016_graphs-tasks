#include <graph/graphalg.h>
#include <queue>
#include <stack>
#include <iostream>

response calcShortestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode) {
	const int INF = 1000000000;
	response res;

	std::vector <int> vertex (n, INF);
	vertex[fromNode] = 0;

	std::vector <bool> visited (n, false);

	for (int i = 0; i < n; i++) {
		int vert = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (vert == -1 || vertex[j] < vertex[vert])) {
				vert = j;
			}
		}
		if (vertex[vert] == INF) break;
		visited[vert] = true;

		for (int j=0; j<n; j++) {
			if (g[vert][j] != -1) {
				int tmp;
				tmp = vertex[vert]+g[vert][j];
				vertex[j] = (vertex[j]<tmp)? vertex[j]: tmp;
			}
		}
	}

	res.code = 0;
	res.answer = vertex[toNode];
	return res;
}

response calcLongestPath(std::vector<std::vector<int> > g, int n, int fromNode, int toNode) {
		const int INF = -1000000000;
	response res;

	std::vector <int> vertex (n, INF);
	vertex[fromNode] = 0;

	//std::vector <bool> visited (n, false);
	std::queue<int> q;
	std::stack<int> st;
	q.push(toNode);
	while(q.size()>0) {
		int v=q.front();
		st.push(v);
		q.pop();
		for(int i=0;i<n;++i) {
			if(g[i][v]>=0) {
				q.push(i);
			}
		}
	}
	while(st.size()>0) {
		int v=st.top();
		st.pop();
		for(int i=0;i<n;++i) {
			if(g[v][i]>=0) {
				vertex[i]=(vertex[i]>g[v][i]+vertex[v])?vertex[i]:g[v][i]+vertex[v];
			}
		}
	}

	/*for (int i = 0; i < n; i++) {
		int vert = -1;
		for (int j = 0; j < n; j++) {
			if (!visited[j] && (vert == -1 || vertex[j] < vertex[vert])) {
				vert = j;
			}
		}
		if (vertex[vert] == INF) break;
		visited[vert] = true;

		for (int j=0; j<n; j++) {
			if (g[vert][j] != -1) {
				int tmp;
				tmp = vertex[vert]+g[vert][j];
				vertex[j] = (vertex[j]>tmp)? vertex[j]: tmp;
			}
		}
	}*/

	res.code = 0;
	res.answer = vertex[toNode];
	return res;
}

response calcCountPaths(std::vector<std::vector<int> > g, int n, int fromNode, int toNode)
{
	response res;
	if(aCycleGraph(g, n, fromNode, toNode)){
		
	int MasIndex[n]={0};			//Массив количества путей из заданной вершины 
	int MCVP[n]={0};				//Массив колличества входящих рёбер для каждой вершины
	int MCVP2[n]={0};				//Массив колличества выходящих рёбер для каждой вершины
	int a=fromNode, b=toNode;
	
	
	
	for(int i=0; i<n; i++)			//Делаю из точки b сток
	{
		g[b][i]=-1;
	}
	
	for(int j=0; j<n; j++)			//Заполняю массив MCVP
	{
		for(int i=0; i<n; i++)
		{
			if(g[i][j]!=-1)
			{
				MCVP[j]+=1;
				MCVP2[i]+=1;
			}
		}
	}
	
	
	int k=1;
	
	while(k!=0)						//Убираю все истоки кроме изначальной точки тем самым делая из неё исток
	{
		k=0;
		for(int j=0; j<n; j++)
		{
			if(MCVP[j]==0 && j!=a && MCVP2[j]!=0)
			{
				for(int i=0; i<n; i++)
				{
					if(g[j][i]!=-1)
					{
						MCVP[i]-=1;
						MCVP2[j]-=1;
						g[j][i]=-1;
					}
				}
				k+=1;
			}
			
		}
				
	}
	
	
	MasIndex[a]=1;
	
	while(MCVP[b]!=0)									//Нахожу количество путей из точки a в точку b
	{
		for(int j=0; j<n; j++)
		{
			if(MCVP[j]==0 && MCVP2[j]!=0)
			{
				for(int i=0; i<n; i++)
				{
					if(g[j][i]!=-1)
					{
						MCVP[i]-=1;
						MCVP2[j]-=1;					
						g[j][i]=-1;				
						MasIndex[i]+=MasIndex[j];
					}
				}
			}
		}
	}
	res.code = 0;
	res.answer =MasIndex[b];
	
	
	}
	
	else
	{
		res.code = 1;
		res.answer =-1;
		res.message = "loop";
	}
	return res;
}

bool dfs(std::vector<std::vector<int> > &g, std::vector<char> &pColor, int v) {
	pColor[v]=1;
	for(unsigned int i=0;i<g[v].size();++i) {
		if(g[v][i]>=0) {
			if(pColor[i]==0) {
				if(dfs(g,pColor,i)) return true;
			}
			else if(pColor[i]==1) {
				return true;
			}
		}
	}
	pColor[v]=2;
	return false;
}

bool aCycleGraph(std::vector<std::vector<int> > g, int n, int fromNode, int toNode) {
	std::vector<char> pColor(n,0);
	clearNonPath(g,n,fromNode,toNode);
	
	return !dfs(g,pColor,fromNode);
}

void clearNonPath(std::vector<std::vector<int> > &g, int n, int fromNode, int toNode) {
	std::vector<int> mark(n,0);
	std::queue<int> q;
	q.push(fromNode);
	int x;
	mark[fromNode]=1;
	while(q.size()>0) {
		x=q.front();
		q.pop();
		for(int i=0;i<n;++i) {
			if(g[x][i]>=0) {
				if(!(mark[i]&1)) {
					mark[i]=1;
					q.push(i);
				}
			}
		}
	}
	q.push(toNode);
	mark[toNode]|=2;
	while(q.size()>0) {
		x=q.front();
		q.pop();
		for(int i=0;i<n;++i) {
			if(g[i][x]>=0) {
				if(!(mark[i]&2)) {
					mark[i]=mark[i]|2;
					q.push(i);
				}
			}
		}
	}

	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			if(g[i][j]>=0 && (mark[i]!=3 || mark[j]!=3))
				g[i][j]=-1;
		}
	}
}
