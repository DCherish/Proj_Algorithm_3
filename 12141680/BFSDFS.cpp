#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std ;

void NodeBFS(vector <vector <int> > graph, vector <bool> visited) // BFS 방문 노드
{
	for( int i = 0 ; i < visited.size() ; i++ ) // 초기화
	{
		visited[i] = false ;
	}

	queue <int> store ; // queue 이용

	int index = 0 ;

	store.push(index) ; // 초기 값 queue에 삽입

	cout << "BFSNode : " ;

	while( !store.empty() )
	{
		int visit = store.front() ;

		store.pop() ; // 맨 앞 값 pop

		if( visited[visit] == false ) // 만약 방문한 적이 없다면
		{
			visited[visit] = true ; // 방문했다고 표시

			cout << visit+1 << " " ; // 방문 노드 출력
			
			for( int i = 0 ; i < graph[visit].size() ; i++ ) // BFS
			{
				if( visited[graph[visit][i]] == false ) // 만약 방문한 적이 없다면
				{
					store.push(graph[visit][i]) ; // queue에 삽입
				}
			}
		}
	}
	cout << endl << endl ;
}

void LineBFS(vector <vector <int> > graph, vector <bool> visited) // BFS 간선 출력
{
	for( int i = 0 ; i < visited.size() ; i++ ) // 초기화
	{
		visited[i] = false ;
	}

	queue <int> store ; // queue 이용

	int index = 0 ;

	store.push(index) ; // 초기 값 queue에 삽입

	cout << "-> BFSLine :" << endl ;

	while( !store.empty() )
	{
		int visit = store.front() ;

		store.pop() ; // 맨 앞 값 pop (Queue -> 앞 값 pop)

		visited[visit] = true ; // 맨 앞 값 방문했다고 표시

		for( int i = 0 ; i < graph[visit].size() ; i++ ) // BFS
		{
			if( visited[graph[visit][i]] == false ) // 만약 방문한 적이 없다면
			{
				visited[graph[visit][i]] = true ; // 방문했다고 표시
				store.push(graph[visit][i]) ; // queue에 삽입
				cout << "(" << visit+1 << ") - (" << graph[visit][i]+1 << ")" << endl ; // 간선을 출력
			}
		}
	}
	cout << endl ;
}

void NodeDFS(vector <vector <int> > graph, vector <bool> visited) // DFS 방문 노드
{
	for( int i = 0 ; i < visited.size() ; i++ ) // 초기화
	{
		visited[i] = false ;
	}

	stack <int> store ; // stack 이용

	int index = 0 ;

	store.push(index) ; // 초기 값 stack에 삽입

	cout << "DFSNode : " ;

	while( !store.empty() )
	{
		int visit = store.top() ;

		store.pop() ; // 맨 위 값 pop

		if( visited[visit] == false ) // 만약 방문한 적이 없다면
		{
			visited[visit] = true ; // 방문했다고 표시

			cout << visit+1 << " " ; // 방문 노드 출력

			for( int i = 1 ; i < graph[visit].size() ; i++ )
			{
				if( visited[graph[visit][i]] == false ) // 만약 방문한 적이 없다면
				{
					store.push(graph[visit][i]) ; // stack에 삽입
				}
			}
		}
	}
	cout << endl << endl ;
}

void LineDFS(vector <vector <int> > graph, vector <bool> visited) // DFS 간선 출력
{
	for( int i = 0 ; i < visited.size() ; i++ ) // 초기화
	{
		visited[i] = false ;
	}

	stack <int> store ; // stack 이용

	int index = 0 ;

	store.push(index) ;
	store.push(index) ; // 초기 값 stack 삽입

	cout << "-> DFSLine :" << endl ;

	while( !store.empty() )
	{
		int visit = store.top() ; // 실제 값

		store.pop() ; // 실제 값 pop
		store.pop() ; // 실제 값이랑 연결된 노드 pop

		if( visited[visit] == false ) // 만약 방문한 적이 없다면
		{
			visited[visit] = true ; // 방문했다고 표시

			for( int i = 0 ; i < graph[visit].size() ; i++ )
			{
				store.push(visit) ; // 실제 값이랑 연결된 노드 삽입
				store.push(graph[visit][i]) ; // 실제 값 삽입
			}

			if( !store.empty() ) // 만약 stack이 비어있지 않다면
			{
				while( visited[store.top()] == true ) // 만약 방문했던 적이 있다면
				{
					store.pop() ; // 실제 값 pop
					store.pop() ; // 실제 값이랑 연결된 노드 pop
					if( store.empty() ) break ; // pop 도중, stack이 empty하다면 종료
				}

				if( store.empty() ) break ; // stack이 비어있다면 종료
				
				int k2 = store.top() ; // 실제 값
				store.pop() ; // 실제 값 pop

				int k1 = store.top() ; // 실제 값이랑 연결된 노드
				
				cout << "(" << k1+1 << ") - (" << k2+1 << ")" << endl ; // 간선 출력
				store.push(k2) ; // 다시 실제 값은 삽입
			}
		}
	}
	cout << endl ;
}

int main()
{
	cout << "12141680 BFSDFS" << endl << endl ;

	int N, L ;
	cin >> N >> L ; // 노드 개수, 간선 개수 입력

	vector <vector <int> > graph(N) ; // graph ; 2d array
	vector <bool> visited(N) ; // visited ; array

	for( int i = 0 ; i < L ; i++ )
	{
		int h ;
		int t ;
		cin >> h >> t ; // 간선 시작 노드, 끝 노드 삽입
		graph[h-1].push_back(t-1) ; // ex) 1 - 3 이 연결되어 있다면
		graph[t-1].push_back(h-1) ; // ex) 3 - 1 또한 연결되어 있음
	}

	cout << endl ;

	NodeBFS(graph, visited) ; // BFS 방문 노드
	LineBFS(graph, visited) ; // BFS 간선 출력
	NodeDFS(graph, visited) ; // DFS 방문 노드
	LineDFS(graph, visited) ; // DFS 간선 출력

	return 0 ;
}