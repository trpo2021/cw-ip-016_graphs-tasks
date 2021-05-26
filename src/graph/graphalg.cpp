#include <graph/graphalg.h>

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



response calcCountPaths(std::vector<std::vector<int> > g, int n, int fromNode, int toNode)
{
	int MasIndex[n]={0};			//Массив количества путей из заданной точки 
	int MCVP[n]={0};				//Массив колличества входящих рёбер для каждой точки
	int a=fromNode, b=toNode;
	
	for(int i=0; i<n; i++)			//Делаю из точки b сток
	{
		g[b][i]=0;
	}
	
	for(int j=0; j<n; j++)			//Заполняю массив MCVP
	{
		for(int i=0; i<n; i++)
		{
			if(g[i][j]!=0)
			{
				MCVP[j]+=1;
			}
		}
	}
	
	
	int k=1;
	
	while(k!=0)						//Убираю все истоки кроме изначальной точки тем самым делая из неё исток
	{
		k=0;
		for(int j=0; j<n; j++)
		{
			if(MCVP[j]=0 and j!=a)
			{
				for(int i=0; i<n; i++)
				{
					if(g[j][i]!=0)
					{
						MCVP[i]-=1;
						g[j][i]=0;
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
			if(MCVP[j]==0)
			{
				for(int i=0; i<n, i++)
				{
					if(g[j][i]!=0)
					{
						MCVP[i]-=1;					
						g[j][i]=0;					
						MasIndex[i]+=MasIndex[j];
					}
				}
			}
		}
	}
	
}
