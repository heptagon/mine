#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

void printarr(int* arrint,int size,string str);
void fill_array_randomly(int* arrint, int size);
void do_kadane(int* ar, int size);

int main(int argc, char** argv)
{
  const int gsize=100;
  int arrint[gsize] = { 0 } ;
  printarr(arrint,gsize,"After initializing");

  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_kadane(arrint,gsize);
  void do_lca(arrint, gsize);

  return 0;
}

void printarr(int* arrint,int size,string str)
{
  cout << str << "\n";
  int ii=0;
  while(ii<size)
    cout <<arrint[ii++] << " " ;
  cout << endl;

}

void fill_array_randomly(int* arrint, int size)
{
  srand(time(0));
  for ( int ii=0; ii<size;++ii){
    int r=rand()% size;
    int sign=rand()%2;
    arrint[ii]= sign == 0 ? r : r*-1;
  }
    
}



void do_kadane(int* a, int s)
{
	int e_=0;
	int s_=0;
	int ms=0;
	int me=0;
	int ii=0;
	int sum_curr=0;
	int max_sum=0;

	while( ii < s )
	{
		int tmp_sum=sum_curr+a[ii];
		if ( tmp_sum > sum_curr){
			e_=ii;
		}

		sum_curr=tmp_sum;
		if (sum_curr < 0)
		{
			s_=ii+1;
			e_=ii+1;
			sum_curr=0;
		
		}else{
			if ( max_sum < sum_curr)
			{
				max_sum=sum_curr;
				ms=s_;
				me=e_;
			}
		}
		
		cout << "ii:"<<ii<<"\ts:"<<s_<<"\te:"<<e_<<"\tconsidered:" << a[ii]<<"\tcurr_sum:"<<sum_curr<<"\tmax_sum:"<<max_sum<<"\n";	
		ii++;
	}

	cout << "Max sum is " <<  max_sum << endl;
	cout << "start and end are " << ms << ":" << me << endl;
	cout << "subarray itself is " << endl;
	for (int ii=ms;ii<=me;++ii)
	{
		cout << a[ii] << ":";
	}
	cout << endl;

}

void do_lca(int* a, int s)
{
	 



}
