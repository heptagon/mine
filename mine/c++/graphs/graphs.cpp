#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include <vector>
#include <time.h>

using namespace std;

const int MAX=25000;
int arr[MAX][MAX] = {0};;



void bfs(vector<int> ii);
int dfs(int ii);

int main(int argc, char** argv)
{

	for(int ii=0;ii<MAX;++ii)
	  for(int jj=0;jj<MAX;++jj)
		arr[ii][jj]=rand()%2;

/*	
	for(int ii=0;ii<MAX;++ii)
	{
	  for(int jj=0;jj<MAX;++jj)
		cout << arr[ii][jj] ;
	  cout << endl;
	}
	cout << endl;
*/
	
	time_t start=time(NULL);
	dfs(3);
	time_t end=time(NULL);
	cout << "time taken " << end-start << " seconds \n";

	vector<int> v;
	v.push_back(3);
	start=time(NULL);
	bfs(v);
	end=time(NULL);
	cout << "time taken " << end-start << " seconds \n";
	return 0;
}


int dfs(int ii)
{
	static set<int> s;
	s.insert(ii);
	cout <<  ii << endl;
	for(int jj=0;jj<MAX;++jj)
		if(arr[ii][jj] && s.find(jj) == s.end())
			dfs(jj);
	cout << "\n";
}

void bfs(vector<int> v)
{
	static set<int> s;
	s.get_allocator().allocate(MAX);
	vector<int>::iterator vi;
	vector<int> nbors;
	nbors.get_allocator().allocate(MAX);
	for(vi=v.begin();vi != v.end();++vi)
	{
		for(int jj=0;jj<MAX;++jj)
		{
			if ( arr[*vi][jj] && s.find(jj) == s.end())
			{	
				nbors.push_back(jj);
				s.insert(jj);
			//	cout << jj << " ";
			}
		}
	}
//	cout << "\n";
	if ( nbors.size())
		bfs(nbors);
	else
		return;
}	

