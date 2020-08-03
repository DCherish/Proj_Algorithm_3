#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std ;

typedef struct Path
{
	int node1 ;
	int node2 ;
	int cost ;

	bool operator<(const Path &o) const  // operation overloading
	{
		return cost > o.cost ;
	}
} Path ;

void prim(vector <vector <Path> > pathp, int N)
{
	vector <Path> result ;
	vector <bool> visited(N, false) ; // false 초기화
	priority_queue <Path> PQ ;

	int i = 0 ;

	visited[i] = true ; // 맨 앞 값 방문했다고 표시

	for( int j = 0 ; j < pathp[i].size() ; j++ )
	{
		if( visited[pathp[i][j].node2] == false ) // 방문한 적이 없다면
		{
			PQ.push(pathp[i][j]) ; // PQ에 삽입
		}
	}

	while( !PQ.empty() )
	{
		Path temp = PQ.top() ; // PQ 맨 위 값
		PQ.pop() ; // PQ 맨 위 값 pop

		i = temp.node2 ;

		if( visited[i] == false ) // 방문한 적이 없다면
		{
			result.push_back(temp) ; // result에 삽입

			visited[temp.node2] = true ; // 방문했다고 표시

			for( int j = 0 ; j < pathp[i].size() ; j++ )
			{
				if( visited[pathp[i][j].node2] == false ) // 방문한 적이 없다면
				{
					PQ.push(pathp[i][j]) ; // PQ에 삽입
				}
			}
		}
	}

	for( int i = 0 ; i < result.size() ; i++ ) // operation overloading
	{
		cout << result[i].node1+1 << " " << result[i].node2+1 << " " << result[i].cost << endl ;
	} // 사이클이 없는 최소 비용 간선 출력

	cout << endl ;
}

int main()
{
	cout << "12141680 Prim" << endl << endl ;

	int N, L ;
	cin >> N >> L ; // 노드 개수, 간선 개수 입력

	vector < vector <Path> > pathp(N) ; // pathp ; 2d struct array 

	for( int i = 0 ; i < L ; i++ )
	{
		int h ;
		int t ;
		int cost ;
		Path temp ;
		cin >> h >> t >> cost ; // 간선 시작 노드, 끝 노드, 간선 간의 cost 삽입
		temp.node1 = h - 1 ; // 시작 노드 tempnode1
		temp.node2 = t - 1 ; // 끝 노드 tempnode2
		temp.cost = cost ; // 간선 간의 cost
		pathp[h-1].push_back(temp) ;// node1 - node2 연결되어 있다면
		temp.node1 = t - 1 ;
		temp.node2 = h - 1 ;
		pathp[t-1].push_back(temp) ;// node2 - node1 또한 연결되어 있음
	}

	cout << endl ;

	prim(pathp, N) ; // Prim

	return 0 ;
}
