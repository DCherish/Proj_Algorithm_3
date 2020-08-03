#include <iostream>
#include <stack>
#include <vec>
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

bool isCycle(vector <vector <int>> connect, int N) // Cycle 검사
{
	stack <int> store ; // stack 이용

	for( int i = 0 ; i < N ; i++ )
	{
		vector <bool> visited(N, false) ; // false 초기화

		if( connect[i].size() != 0 )
		{
			store.push(i) ; // stack에 삽입

			while( !store.empty() )
			{
				int visit = store.top() ;

				store.pop() ; // 맨 위 값 pop

				if( visited[visit] == false ) // 방문한 적이 없다면
				{
					visited[visit] = true ; // 방문했다고 표시

					for( int j = 0 ; j < connect[visit].size() ; j++ )
					{
						if( visited[connect[visit][j]] == false ) // 만약 방문한 적이 없다면
						{
							store.push(connect[visit][j]) ; // stack에 삽입
						}
					}
				}else // 방문한 적이 있다면
				{
					return true ; // 사이클이 있음
				}
			}
		}
	}

	return false ; // 사이클이 없음
}

void kruskal(priority_queue <Path> &pathk, int N)
{
	vector <vector <int>> connect(N) ; // connect ; 2d array

	vector <Path> result ; // result ; array

	while( !pathk.empty() )
	{
		Path temp ; // struct
		temp = pathk.top() ; // PQ 맨 위 값
		pathk.pop() ; // PQ 맨 위 값 pop

		connect[temp.node1].push_back(temp.node2) ; // node1 - node2 연결되어 있다면
		connect[temp.node2].push_back(temp.node1) ; // node2 - node1 또한 연결되어 있음

		if( !isCycle(connect, N) ) // cycle 방지 검사, kruskal 핵심
		{
			result.push_back(temp) ; // 사이클이 없다면 result에 삽입
		}else // 사이클이 있다면
		{
			connect[temp.node1].pop_back() ;
			connect[temp.node2].pop_back() ; // 그 노드는 제외
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
	cout << "12141680 Kruskal" << endl << endl ;

	int N, L ;
	cin >> N >> L ; // 노드 개수, 간선 개수 입력

	priority_queue <Path> pathk ; // path ; struct PQ

	vector <vector <int> > graph(N) ; // graph ; 2d array 
	vector <bool> visited(N) ; // visited ; array

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
		pathk.push(temp) ;
	}
	
	cout << endl ;

	kruskal(pathk, N) ; // Kruskal

	return 0 ;
}