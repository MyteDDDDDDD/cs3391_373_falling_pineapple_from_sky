#include <iostream>
#include<queue>
using namespace std;

queue<int> c;
queue<int> unused;
queue<int> countUnuser;

int n, m;

struct Edge {
	int u, v, cost;
}nEdge[25000];

int CMP(const void *a, const void *b) {
	Edge *A = (Edge*)a;
	Edge *B = (Edge*)b;
	return A->cost - B->cost;
}

int Find(int element, int A[]) {
	if (A[element] < 0)
		return element;
	else
		return Find(A[element], A);
}

void UnionSet(int set1, int set2, int A[]) {
	A[set1] += A[set2]; // A[ root of set is negative, and its
	A[set2] = set1;     // magnitude is the num of members
}

void Union(int element1, int element2, int A[]) {
	int root1 = Find(element1, A);
	int root2 = Find(element2, A);
	if (A[root1] < A[root2]) //root1 has more member		
		UnionSet(root1, root2, A);
	else
		UnionSet(root2, root1, A);
}

int prim() {
	int sum = 0;
	int sumUn = 0;
	if (m == 0) {
		countUnuser.push(sumUn);
		return -1;
	}

	qsort(nEdge, m, sizeof(Edge), CMP);
	int *city = new int[n];
	for (int i = 0; i < n; i++) {
		city[i] = -1;
	}
	for (int i = 0; i < m; i++) {
		int fu = Find(nEdge[i].u, city);
		int fv = Find(nEdge[i].v, city);
		
		if (fu == -1 || fv == -1) {
			Union(fu, fv, city);
			sum += nEdge[i].cost;
		}
		else if (fu == fv) {
			unused.push(nEdge[i].cost);
			sumUn++;
		}
		else {
			Union(fu, fv, city);
			sum += nEdge[i].cost;
		}

	}
	countUnuser.push(sumUn);
	int counter = city[0];

	for (int i = 0; i < n; i++) {
		if (counter != Find(i, city))
			return -1;
	}

	return sum;
}

void printUnused() {
	int count = countUnuser.front();
	countUnuser.pop();
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			cout << unused.front();
			if (i <count - 1)
				cout << " ";
			unused.pop();
		}
	}
	cout << endl;
	
}

int main() {
	cin >> n;
	cin >> m;
	while (!(n == 0 && m == 0)){
		int u, v, cost;
		for (int i = 0; i < m; i++) {
			cin >> nEdge[i].u >> nEdge[i].v >> nEdge[i].cost;
		}
		c.push(prim());
		cin >> n>>m;

	}

	while (!c.empty()) {
		if (c.front() != -1) {
			cout << "Min cost: " << c.front() << endl;
			c.pop();
			printUnused();
		}
		else if (c.front() == -1) {
			cout << "\\(^o^)/ pray to god" << endl;
			c.pop();
		}
			
	}

	return 0;
}
