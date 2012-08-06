#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

void printarr(int* arrint,int size,string str);
void fill_array_randomly(int* arrint, int size);

void do_selection_sort(int* arrint, int size);
void do_insertion_sort(int* arrint, int size);
//void do_bubble_sort   (int* arrint, int size);
//void do_merge_sort    (int* arrint, int size);
void do_quick_sort    (int* arrint, int left,int right);


void do_heap_sort     (int* arrint, int size);
//void buildheap(int* arrint,int size);          // private
void heapify(int* arrint,int parent, int heapsize);     // private
int heap_parent(int child_index);              // private
int heap_lt(int parent_index);         // private
int heap_rt(int parent_index);        // private
void verify_heap(int* arrint, int parent, int size);       // tester
void do_shell_sort    (int* arrint, int size);

void swap(int* arrint, int to, int from);      //private

int main(int argc, char** argv)
{
  const int gsize=100;
  int arrint[gsize] = { 0 } ;
  printarr(arrint,gsize,"After initializing");

  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_insertion_sort(arrint,gsize); printarr(arrint,gsize,"after Insertion sort");

  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_selection_sort(arrint,gsize); printarr(arrint,gsize,"after selection sort");

  
//  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
//  do_bubble_sort(arrint,gsize); printarr(arrint,gsize,"after bubble sort");
  
  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_quick_sort(arrint,0,gsize-1); printarr(arrint,gsize,"after quick sort");

/*
  
  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_merge_sort(arrint,gsize); printarr(arrint,gsize,"after merge sort");

  */

  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_heap_sort(arrint,gsize); printarr(arrint,gsize,"after heap sort");

  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_shell_sort(arrint,gsize); printarr(arrint,gsize,"after shell  sort");
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
    arrint[ii]=r;
  }
    
}

void swap(int* arrint, int to_index, int from_index){
  int temp=arrint[to_index];
  arrint[to_index]=arrint[from_index];
  arrint[from_index]=temp;
  return;
}

// 1. start from top
// 2. for each item search remaining sublist backwards
// 3. keep shifting items down in the sublist until the 'i'tem is in the right position
// 4. assign 'i'tem to that position
// Note: save arrint[ii] to item or else it will be overwritten while shifting down
void do_insertion_sort(int* arrint,int size)
{
	for ( int ii=1;ii<size;++ii)
	{
		int item=arrint[ii];
		int jj=ii-1;
		while(jj >=0 && arrint[jj] > item)
		{
			arrint[jj+1]=arrint[jj];
			jj--;
		}
		arrint[jj+1]=item;
	}
}

// 1. idea is to keep sorted sublist from top
// 2. going top-down, for each item : search bottom list to find index of minimum element
// 3. Swap 'i'tem's index with min index and move to next item

void do_selection_sort(int* a, int size)
{
	for(int ii=0;ii<size-1;++ii)
	{
		int mi=ii;
		for( int jj=ii+1;jj<size;++jj)
		{
			if(a[jj] < a[mi])
				mi=jj;
		}
		swap(a,ii,mi);
	}
}




// 1. create a pivot element [ typically midway of the list ]
// 2. Idea is to split the list at pivot so that left of pivot is a sublist less than pivot value and right of it is greater.
// 3. Recursively apply quick_sort to both sublists.
// 4. HINT HINT: pivot is the root of a BST
// 5. beware: there is only one time that "=" features in teh condition. This is when we need to swap.
// 5.1: also beware : reference pivot only by the vlaue and not index as the index's value can change due to swaps in recursion
// 6. The idea is keep advancing left sublist and stop when an element > pivot value is found.
// 7. do the same with right sublist but advance the other way.
// 8. swap the values where left and righ pointers stop. Remember to move left and right pointers once swapped.
// 9. Keep repeating until left pointer has moved ahead of right pointer.

void do_quick_sort(int* a, int _lt, int _rt)
{
	int left=_lt;
	int right=_rt;
	int pivot=a[(left+right)/2];
	while( left < right) {
		while(a[left] < pivot)
			left++;
		while(a[right] > pivot)
			right--;
		if (left <= right) {
			int t=a[left];
			a[left]=a[right];
			a[right]=t;
			left++;
			right--;
		}
	}
	if (_lt < right)
		do_quick_sort(a,_lt,right);
	if (left < _rt)
		do_quick_sort(a,left,_rt); 
}






// 1. split list in two and recursively apply merge_sort
// 2. bottom out when the list size is 1.
// 3. Start merging: take two lists and merge such that
// 	compare top elements in both list and move the smallest to the target list. 
// 	get the next top element from the list where the smallest was moved.
// 	repeat.
//	one of the lists might have ended. Merge the tail of the other list.

/*
int* do_merge_sort    (int* arrint, int lo, int hi)
{
	if ( lo < hi){
		do_merge_sort(arrint,lo,(lo+hi)/2);
		do_merge_sort(arrint,((lo+hi)/2)+1,hi);
	}
	merge(arrint,lo,((lo+hi)/2)+1),hi);
}

cant do inplace merge except for swapping and shifting the reamining sublist uptil the swapped [ from ] position. Bad performance.
void merge(int* a, int l1, int l2, int hi)
{
	int l1i=l2-1;
	int l2i=hi;
	while(l2i >= l2 && l1i >= l1)
	{
		if(a[l2i] < a[l1i])
		{
			int t=a[l2i];
			a[l2i]=a[li1];
			a[l1i]=t;
		}
		l2i--;
	}
}

*/

// The idea is build a heap and keep removing the root [ which is the largest ]
// assign a new root [ right most element of the tree at max depth] and reheap.
// repeat 
// 1. heapify [ note heapify takes parent as the argument. 
//	 When you build the heap: go backwards from last prent to root. But  When you reheap : start from first parent [ root ]
// 2. remove last element
// 3. reheap
// 4. repeat 2 and 3.




/*
// check Y:\doc_collection\work\per\33-heapsort
// 1.build heap from an array
// 2.swap first node with last node [act of removal]
// 3.reheap
// 4. repeat 2 and 3 n times with heapsize reducing every iteration so that last elements dont get picked up again

// heap:
// binary tree but NOT binary search tree
// root is largest than all children
// represented as a left justified balanced binary tree 
// balanced because depths to leaf nodes differ no more than 2 in left and right branches
// left justified because all leafs at depth n are as far as possible to the left
// left justified so that it can be represented in an array 

// how to build heap from array
// 1. start backwards from last parent i.e. (n-1)/2 th node
// 2. using parent->child relnship verify its children are lowest or else swap the largest w parent.
// 3.  If swapped : ensure that victim subtree is still satisfying heap properties or else repeat 2 for that victim and so on...
// 4. Note steps 2 and 3 also comprise reheap process after every removal action.


*/
void do_heap_sort(int* a, int size)
{
	int heapsize=size;
	int last_parent=heap_parent(heapsize-1);
	for (int ii=last_parent;ii>=0;--ii)
		heapify(a,ii,heapsize);

	while(heapsize > 1) {
		swap(a,0,heapsize-1);
		--heapsize;
		heapify(a,0,heapsize);
	}
}

int heap_parent(int c)
{
	if ( c==0)
		return 0;
	return (c%2 ? (c-1)/2 : (c-2)/2);
}

int heap_lt(int p)
{
	return p*2+1;
}

int heap_rt(int p)
{
	return p*2+2;
}

// takes array and index to consider for heapifying
void heapify(int* a, int p,int heapsize)
{
	int lt=heap_lt(p);
	int rt=heap_rt(p);
	if(lt >= heapsize)
		return;
	else if ( rt >= heapsize)
	{
		if(a[p] < a[lt])
		{
			swap(a,p,lt);
			heapify(a,lt,heapsize);
		}
	}else {
		int maxi=p;
		if (a[maxi] <  a[lt])
			maxi=lt;
		if ( a[maxi] < a[rt])
			maxi=rt;
		
		if ( maxi != p)
		{
			swap(a,p,maxi);
			heapify(a,maxi,heapsize);
		}
	}
}

void verify_heap(int* a,int p,int heapsize)
{
	int lt=heap_lt(p);
	int rt=heap_rt(p);
	
	if ( lt <  heapsize) {
		if ( a[p] < a[lt])
		{
			cout << "Heap error at " << p << ":" << lt << endl; 
			return;
		}
		verify_heap(a,lt,heapsize);
	}
	if ( rt < heapsize) {
		if ( a[p] < a[rt])
		{
			cout << "Heap error at " << p << ":" << rt << endl; 
			return;
		}
		verify_heap(a,rt,heapsize);
	}
}

// see http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/shell/shellen.htm
void do_shell_sort(int* a, int size)
{
	int h_seq[]={1391376,463792,198768,86961,33936,13776,4592,1968,861,336,112,48,21,7,3,1};
	for (int h_ind=0;h_ind < 16; ++h_ind)
	{
		int h_val=h_seq[h_ind];
		int h=h_val;
		for (int ii=h;ii<size;++ii)
		{
			int v=a[ii];
			int jj=ii-h;
			while( jj >=0 && a[jj] > v)
			{
				a[jj+h] = a[jj];
				jj=jj-h;
			}
			a[jj+h]=v;
		}
	}
}

