#include <graphalg.h>

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
