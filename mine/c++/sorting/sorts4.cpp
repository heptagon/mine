#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class sorter
{
	public:
		sorter()
		{
			s=100;
			a =new int[100];
			srand(time(0));
			int ii=0;
			while(ii < s)
				a[ii++]=rand()%s;
			output();
		};

		~sorter()
		{
			delete[] a;
			cout << "array memory deleted\n";
		};

		sorter*  insertion_sort();
		sorter*  selection_sort();
		sorter*  quick_sort();
		sorter*  heap_sort();
		sorter*  shell_sort();
	
		sorter* randomize();
		sorter* output();
		bool verify();
	private:	
		void swap(int pos1,int pos2);

		void qs(int l, int r);

		int parent(int i);
		int lc(int p);
		int rc(int p);
		void heapify(int n, int e);
		

		int* a;
		int s;
};


sorter* sorter::output()
{
	for(int ii=0;ii<s;ii++)
		cout << a[ii] << "," ;
	cout << endl;	
	return this;
}

sorter* sorter::insertion_sort()
{
	cout << "in insertion sort\n";
	for(int ii=1;ii<s;++ii)
	{
		int v=a[ii];
		int jj=ii-1;
		while(jj>=0 && a[jj] > v)
		{
			a[jj+1]=a[jj];	
			jj--;
		}
		a[jj+1]=v;	
	}	
	return this;
}

sorter* sorter::selection_sort()
{
	cout << "in selection sort\n";
	for(int ii=0;ii<s-1;++ii)
	{
		int minpos=ii;
		for(int jj=ii+1;jj<s;++jj)
			if ( a[jj] < a[minpos])
				minpos=jj;
		swap(ii,minpos);
	}
	return this;
}

sorter* sorter::quick_sort()
{
	cout << "in quick sort\n";
	qs(0,s-1);
	return this;
}

void sorter::qs(int _l, int _r)
{
	int l=_l;
	int r=_r;
	int pv=a[(l+r)/2];
	while(l<r)
	{
		while(a[l]<pv)
			l++;
		while(a[r]>pv)
			r--;
		if ( l <= r)
			swap(l++,r--);
	}

	if(l < _r)
		qs(l,_r);
	if(_l < r)
		qs(_l,r);	

}


sorter*  sorter::heap_sort()
{
	cout << "in heap sort\n";
	int hs=s;
	//build heap
	int lp=parent(s-1);
	while( lp>=0)
	{
		heapify(lp,hs);
		lp--;
	}

	// sort
	do {
		heapify(0,hs);
		swap(0,hs-1);
		hs--;
	}while(hs>0);
	
	return this;
}

void sorter::heapify(int n, int e)
{
	int l=lc(n);
	int r=rc(n);
	int max=n;
	if(l < e && a[l] > a[max] )
		max=l;
	if( r < e && a[r] > a[max] )
		max=r;

	if ( max != n )
	{
		swap(n,max);
		heapify(max,e);
	}
}


int sorter::parent(int n)
{
	if( n == 0 )	
		return 0;
	return n%2 ? (n-2)/2 : (n-1)/2;
}

int sorter::lc(int n)
{
	return 2*n+1;
}
int sorter::rc(int n)
{
	return 2*n+2;
}




sorter* sorter::shell_sort()
{
	cout << "in shell sort\n";
	int h_s[]={1391376,463792,198768,86961,33936,13776,4592,1968,861,336,112,48,21,7,3,1};
	for(int h=0;h<16;++h)
	{
		int step=h_s[h];
		for(int ii=step;ii<s;ii+=step)
		{
			int v=a[ii];
			int jj=ii-step;
			while( jj >= 0 && a[jj] > v)
			{
				a[jj+step]=a[jj];
				jj-=step;
			}
			a[jj+step]=v;
		}
	}
	return this;
}

sorter* sorter::randomize()
{
	srand(time(0));
	for(int ii=0;ii<s;++ii)
	{
		swap(ii,rand()%s);
	}
	cout << "after randomizing\n";
	return this;
}

bool sorter::verify()
{
	int ii=0; int jj=1;
	while(jj<s)
		if ((a[ii++]>a[jj++]))  // ii incremented twice in the same expression
			return false;
	return true;
}

void sorter::swap(int from, int to)
{
	int t=a[from];
	a[from]=a[to];
	a[to]=t;
}


int main(int argc, char** argv)
{
	sorter s;
	cout << s.verify() << endl;
	cout << ( s.randomize()->output()->selection_sort()->output()->verify()  ? "verified" : "incorrect" ) << endl;
	cout << ( s.randomize()->output()->insertion_sort()->output()->verify()  ? "verified" : "incorrect" ) << endl;
	cout << ( s.randomize()->output()->quick_sort()->output()->verify()  ? "verified" : "incorrect" ) << endl;
	cout << ( s.randomize()->output()->shell_sort()->output()->verify()  ? "verified" : "incorrect" ) << endl;
	cout << ( s.randomize()->output()->heap_sort()->output()->verify()  ? "verified" : "incorrect" ) << endl;
	return 0;
}

