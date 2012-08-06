#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>


using namespace std;

void printarr(int* arrint,int size,string str);
void fill_array_randomly(int* arrint, int size);

void do_selection_sort(int* arrint, int size);
void do_insertion_sort(int* arrint, int size);
void do_bubble_sort   (int* arrint, int size);
void do_merge_sort    (int* arrint, int size);
void do_quick_sort    (int* arrint, int left,int right);

void do_heap_sort     (int* arrint, int size);
void buildheap(int* arrint,int size);          // private
void heapify(int* arrint, int heapsize,int root_index);     // private
int heap_parent(int child_index);              // private
int heap_left_child(int parent_index);         // private
int heap_right_child(int parent_index);        // private
void verify_heap(int* arrint, int size, int root);       // tester

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

  
  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_bubble_sort(arrint,gsize); printarr(arrint,gsize,"after bubble sort");
  
  fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  do_quick_sort(arrint,0,gsize-1); printarr(arrint,gsize,"after quick sort");

  
  //fill_array_randomly(arrint,gsize); printarr(arrint,gsize,"random fill");
  //do_merge_sort(arrint,gsize); printarr(arrint,gsize,"after merge sort");

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

void do_selection_sort(int* arrint, int size)
{
  // select the lowest element and swap it to the top
  for (int ii=0;ii<size;++ii){
    for ( int jj=ii+1;jj<size;++jj){
      if ( arrint[ii] > arrint[jj]){
	swap(arrint,ii,jj);
      }
    }
  }
  return;
}
void do_insertion_sort(int* arrint, int size)
{
  // keep the sublist sorted in itself : sorting happens by :
  // pick a key in outer loop at pos  n. Inner loop iterates in reverse for the n-1 elments in the sorted sublist.
  // if key still lesser than element then forward consecutive elements by 1 step

  for ( int ii=1;ii<size;++ii){
    int key=arrint[ii];
    int jj=ii-1;
    while(key < arrint[jj] && jj >=0){
      arrint[jj+1]=arrint[jj];
      --jj;
    }
    arrint[jj+1]=key;
  }

  return;
}
void do_bubble_sort   (int* arrint, int size)
{
  // swaps consecutive elements per pass ...and does n passes of it
  for ( int ii=0;ii<size;++ii)
    for ( int jj=0; jj<size-1;++jj)
      if (arrint[jj+1] < arrint[jj])
	  swap(arrint,jj+1,jj);

  return;
}


int* do_merge_sort    (int* arrint, int lo, int hi)
{

}



void do_quick_sort    (int* arrint, int lt, int rt)
{
  // build a partition with pivot as central element.
  // left pointer moves forward to pivot as long as its values are lesser than pivot
  // right pointer moves backward to pivot as long as its values are larger than pivot
  // if left and right pointers dont cross each other, swap their values
  // repeat above until left and right pointers cross each other
  // Now you have  2 sublists partitioned around pivot. The left sublist has elements all smaller to pivot and the right sublist has elements all larger to pivot
  // Hint hint: here pivot is the root to a BST
  // repeat quicksort again in left sublist and right sublist [ recursively ]

  int left=lt;
  int right=rt;
  int pivot=arrint[(lt+rt)/2];

  // partition
  while(left <= right){
    while ( arrint[left] < pivot)
      left++;
    while (arrint[right] >  pivot)
      right--;
    if ( left <=right){
      int temp=arrint[left];
      arrint[left]=arrint[right];
      arrint[right]=temp;
      left++;right--;
    }
  }
  
  if ( right > lt) 
    do_quick_sort(arrint,lt,right);
  if ( left < rt )
    do_quick_sort(arrint,left,rt);

  return;
}

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

void do_heap_sort  (int* arrint, int size)
{
  int heapsize=size;
  buildheap(arrint, heapsize);
  
  for(int ii=heapsize-1;ii>0;--ii){
    swap(arrint,0,heapsize-1);
    heapsize--;
    heapify(arrint,heapsize,0);
  }
}

void buildheap(int* arrint, int heapsize)
{
  int last_parent=(heapsize-1)/2;
  for(int ii=last_parent;ii>=0;--ii){
    heapify(arrint,heapsize,ii);
  }
  //verify_heap(arrint, heapsize,0);
}

void verify_heap(int* arrint, int heapsize, int root)
{

    int li=heap_left_child(root);
    int ri=heap_right_child(root);

    if ( li < heapsize-1)
      verify_heap(arrint,heapsize,li);
    if ( ri < heapsize-1)
      verify_heap(arrint,heapsize,ri);
    

    if ( arrint[root] > arrint[heap_parent(root)] ){
      cout << "Parent id : " << heap_parent(root)  << " not a heap root \n";
    }else {
      cout << "Parent id : " << heap_parent(root)  << " is indeed a heap root \n";
    }
}

void heapify(int* arrint, int heapsize, int index)
{
  int lastindex=heapsize-1;
  int li=heap_left_child(index);
  int ri=heap_right_child(index);
  
  if ( ri > lastindex && li  > lastindex)
    return;
  
  int maxchild=-1;

  if (ri > lastindex)
    maxchild=li;
  else if ( li > lastindex ) // should not be necessary as ri will also be > lastindex then
    maxchild=ri;
  else 
    maxchild= arrint[li] >  arrint[ri] ? li : ri ;
  
  if ( arrint[maxchild] > arrint[index]){
    swap(arrint,maxchild,index);
    heapify(arrint,heapsize,maxchild);
  }
}


int heap_parent(int i)
{
  if ( i==0 ) return 0;

  if ( i % 2 == 0)
    return (i/2)-1;
  else 
    return i/2;
}

int heap_left_child(int i)
{
  return i*2+1;
}

int heap_right_child(int i)
{
  return i*2+2;
}


// see http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/shell/shellen.htm
void do_shell_sort    (int* arrint, int size)
{
  int cols[]={21,13,8,5,3,1};
  int colsize=6;

  for ( int kk=0; kk<colsize;++kk){
    int step=cols[kk];
    for ( int ii=step;ii<size;++ii){
      int key=arrint[ii];

      int jj=ii;
      while(arrint[jj-step] > key && jj>=step ){
	arrint[jj]=arrint[jj-step];
	jj=jj-step;
      }
      arrint[jj]=key;
    }
  }
  return;
}

