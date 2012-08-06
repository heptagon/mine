#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

typedef struct treenode {
  int val;
  treenode* left;
  treenode* right;
} treenode;

treenode* create_tree(int range);
treenode* insert_node(treenode* root, int val);

treenode* delete_nodes_with_val(treenode* root, int val);
treenode* find_parent_rightmost_node(treenode* node);
treenode* find_parent_leftmost_node(treenode* node);



void postorder_traversal(treenode* root);
void preorder_traversal(treenode* root);
void inorder_traversal(treenode* root);
void morris_traversal(treenode* root);

void printtree(treenode* root, string str);
void printlevels(treenode* root, int level,int shift); //private

treenode* balance_tree(treenode* root);
treenode* rotR(treenode* node);
treenode* rotL(treenode* node);

int heightT(treenode* root);
int depth(treenode* root, treenode* node);
int depth(treenode* root, int val);
int leaf_nodes(treenode* root);

//global
vector<string> glines;
int gminshift=0;

int main( int argc, char** argv)
{
  glines.clear();
  treenode* root=NULL;


  root=create_tree(15);      printtree(root,"after creation");
  root=insert_node(root,19); printtree(root,"after inserting 19");
  root=insert_node(root,0);  printtree(root,"after inserting 0");
  root=insert_node(root,7);  printtree(root,"after inserting 7");

  root=delete_nodes_with_val(root,1); printtree(root,"after deleting root");  
  root=delete_nodes_with_val(root,0);  printtree(root,"after deleting 0");
  root=delete_nodes_with_val(root,19); printtree(root,"after deleting 19");
  root=delete_nodes_with_val(root,7); printtree(root,"after deleting 7");
  //root=delete_root(root); printtree(root,"after deleting root");


  postorder_traversal(root);  cout <<  "\nafter postorder traversal " << endl;
  preorder_traversal(root);  cout << "\n after preorder traversal " << endl;
  inorder_traversal(root);  cout <<  "\n after inorder traversal " << endl;
  morris_traversal(root);  cout <<  "\n after morris traversal " << endl;

  root=balance_tree(root); printtree(root,"after balancing");

  cout << "Height of the tree is " << heightT(root) << " \n";
  cout << "nof leaf nodes of the tree is" << leaf_nodes(root) << " \n";
  cout << "depth of node 19 is " << depth(root,19) << endl;

  
  return 0;
}


treenode* balance_tree(treenode* root)
{
  if ( root->left != NULL)
    root->left=balance_tree(root->left);
  if ( root->right != NULL)
    root->right=balance_tree(root->right);

  int balance_factor=heightT(root->right) - heightT(root->left);
  if ( balance_factor == 2) { // right heavy
    treenode* subtree_root=root->right;
    int subtree_balance_factor=heightT(subtree_root->right) - heightT(subtree_root->left);
    if ( subtree_balance_factor == -2 ){
      //doubleleft
      // 1. right rotation on right subtree
      subtree_root=rotR(subtree_root);
      root->right=subtree_root;
      // 2. left rotation on root
      root=rotL(root);
    }else{
      //singleleft
      // 1. left rotation on root
      root=rotL(root);
    }
  }else if ( balance_factor == -2) { //left heavy
    treenode* subtree_root=root->left;
    int subtree_balance_factor = heightT(subtree_root->right) - heightT(subtree_root->left);
    if ( subtree_balance_factor == 2 ){
      // doubleright
      //1.  left rotation on left subtree
      subtree_root=rotL(subtree_root);
      root->left=subtree_root;
      //2.  right rotation on root
      root=rotR(root);
    }else {
      //single right
      //1. right rotation on root
      root=rotR(root);
    }
  }else{
    //cout << " No need to balance tree right now subtree_root->val is " << root->val << "\n";
    return root;
  }
  return root;
}

treenode* rotL(treenode* node)
{
  treenode* newroot=node->right;
  node->right=newroot->left;
  newroot->left=node;
  return newroot;
}

treenode* rotR(treenode* node)
{
  treenode* newroot=node->left;
  node->left=newroot->right;
  newroot->right=node;
  return newroot;
}

treenode* create_tree(int range)
{
  
  treenode* root = new treenode();
  root->val=1;
  root->left=NULL;
  root->right=NULL;
  
  treenode* currnode=root;

  for(int ii=2; ii<=range; ++ii, currnode=root){
    root=insert_node(root,ii);
    printtree(root,"during creation");
  }
  return root;
}

treenode* insert_node(treenode* root, int val)
{
  treenode* newnode= new treenode();
  newnode->val=val;
  newnode->left=NULL;
  newnode->right=NULL;

  if ( root == NULL ) 
    return newnode;

  treenode* currnode=root;
  while ( 1 ) {
    if ( val <= currnode->val){
      if(currnode->left == NULL){
	currnode->left=newnode;
	root=balance_tree(root);
	return root;
      }else{
	currnode=currnode->left;
      }
    }else { // if ( val  > currnode->val){
      if ( currnode->right == NULL){
	currnode->right=newnode;
	root=balance_tree(root);
	return root;
      }else{
	currnode=currnode->right;
      }
    }
  }

  root=balance_tree(root);
  return root;
}

treenode* delete_nodes_with_val(treenode* root, int val)
{
  if ( !root || (root->val == val && root->left == NULL && root->right == NULL)) {
    delete root;
    root=NULL;
    return NULL;
  }


  treenode* currnode=root;
  treenode* parent=NULL;


  while(currnode->val != val){
    if ( currnode->val <  val){
      parent=currnode;
      currnode = currnode->right;
    } else {
      parent=currnode;
      currnode = currnode->left;
    }
  }

  if ( currnode == NULL )
    cout << "Value to be deleted not found\n";

  if ( currnode->val == val){
    if ( currnode->left == NULL  && currnode->right == NULL){
      if ( parent->left == currnode )
	parent->left = NULL;
      if ( parent->right == currnode)
	parent->right = NULL;
      delete currnode;
      currnode=NULL;
      root=balance_tree(root);
      return root;
    }

    if ((currnode->left != NULL && currnode->right == NULL)) {
      if ( !parent){
	treenode* temp=root->left;
	root->val = root->left->val;
	root->left=root->left->left;
	root->right=root->left->right;
	delete temp;
	root=balance_tree(root);
	return root;
      }
	
      if ( parent->left == currnode )
	parent->left = currnode->left;
      if ( parent->right == currnode)
	parent->right = currnode->left;
      delete currnode;
      currnode=NULL;
      root=balance_tree(root);
      return root;
    }
    if (( currnode->left == NULL && currnode->right != NULL)) {
      if ( !parent){

	treenode* temp=currnode->right;
	currnode->val=currnode->right->val;
	currnode->right=currnode->right->right;
	currnode->left=currnode->right->left;

	delete temp;
	root=balance_tree(root);
	return root;
      }
      if ( parent->left == currnode)
	parent->left = currnode->right;
      if ( parent->right == currnode)
	parent->right = currnode->right;
      delete currnode;
      currnode=NULL;
      root=balance_tree(root);
      return root;
    }
    if ( currnode->left != NULL && currnode->right !=NULL){
      // find nearest node just smaller than it 
      // alt. I could have found nearest node just larger than it
      if (currnode->left->right == NULL ){
	currnode->val=currnode->left->val;
	currnode->left=currnode->left->left;
	delete currnode->left;
	root=balance_tree(root);
	return root;
      }else{
	treenode* just_lowests_parent=find_parent_rightmost_node(currnode->left);
	currnode->val=just_lowests_parent->right->val;
	delete just_lowests_parent->right;
	just_lowests_parent->right=NULL;
	root=balance_tree(root);
	return root;
      }
    }
  }
  return root;
}

treenode* find_parent_rightmost_node(treenode* node)
{
  treenode* parent=node;
  while ( parent->right->right != NULL)
    parent=parent->right;

  return parent;
}

treenode* find_parent_leftmost_node(treenode* node)
{
  treenode* parent=node;
  if ( parent->left == NULL)
    return parent;
  while(parent->left->left != NULL)
    parent=parent->left;

  return parent;
}

void inorder_traversal(treenode* node)
{
  if ( node == NULL )
    return;

  inorder_traversal(node->left);
  cout << node->val << " " ;
  inorder_traversal(node->right);  
}


void preorder_traversal(treenode* node)
{
  if ( node == NULL)
    return;
  
  cout << node->val << " " ;
  preorder_traversal(node->left);
  preorder_traversal(node->right);

}

void postorder_traversal(treenode* node)
{
  if ( node == NULL)
    return;
  
  postorder_traversal(node->left);
  postorder_traversal(node->right);
  cout << node->val << " " ;
}

void printtree(treenode* root, string str)
{
  cout << str << endl;
  gminshift=0;

  glines.resize(2*heightT(root));
  for ( int ii=0; ii<glines.size(); ++ii)
    glines[ii] = "                                                                                                                                               ";


  int level=0;
  int shift=0;
  printlevels(root,level,shift);
  for ( int ii=0; ii < glines.size(); ++ii)
    cout << glines[ii] << "\n";

  cout << "\n";

}

// level: level of a root node
// shift: x-axis shift of the current node if the tree root is positioned at x=0 
// note shift can be -ve

void printlevels(treenode* root,int level,int shift)
{
  if ( root == NULL )
    return;

  int stepshift=4; // gap between two values
  printlevels(root->left,level+2,shift-stepshift);
  printlevels(root->right,level+2,shift+stepshift);

  stringstream ss;
  ss << root->val;

  gminshift=min(gminshift,shift);    
  glines[level].insert((shift-gminshift),ss.str());
  if ( root->left != NULL )
    glines[level+1].insert((shift-gminshift-2),"/");
  if ( root->right != NULL )
    glines[level+1].insert((shift-gminshift+2),"\\");
 
 
  for ( int ii=0; ii < glines.size(); ++ii)
    cout << glines[ii] << "\n";

  cout << "\n";
}


int heightT(treenode* node)
{
  if (node==NULL)
    return 0;

  int height= 1 + max(heightT(node->left),heightT(node->right));
  return height;
}

int depth(treenode* root, int val)
{
   // assumes node->val  exists in the tree
  if ( !root )
    return 0;

  if ( val == root->val )
    return 0;
  if ( val < root->val ) // what about duplicate nodes
    return (1 + depth(root->left,val)); 
  if ( val > root->val )
    return ( 1 + depth(root->right,val));	   
}

int depth(treenode* root, treenode* node)
{
  if ( !node)
    return 0;

  depth(root,node->val);
}

int leaf_nodes(treenode* root)
{
  if (root==NULL)
    return 0;

  if ( root->left == NULL && root->right == NULL ){
    cout << root->val << " " ;
    return 1;
  }

  return (leaf_nodes(root->left) + leaf_nodes(root->right));
 
}



// 1. essentially links the rightmost leaf node of the left subtree to the root so that no backtracking is needed.
// but this creates loops and that needs to be broken when encountered.

// steps are:
// 1. do this while current [ initialized to root ] is non null
// 2. If left subtree is null, simply print that node's value and move to the right subtree and repeat
// 3. If left subtree is there, go to the rightmost leaf of that left subtree and assign that leaf's right node to be the left subtree's root. [ cycle ]
// 4. repeat same for the left child of that left subtree, and keep doing that.
// 5. At one point it will turn out that by going to the right subtree you are simply cycling back to the subtree root [ inorder successor ]
// 6. at that point, break the cycle and print that node;s value and keep going right.
// 7. Best to hand execute on a small tree to get the hang of it.
 
void morris_traversal(treenode* root)
{
	cout << "begin morris traversal..\n";
	treenode* curr=root;
	treenode *pre=NULL;
	while( curr )
	{
		if(!curr->left)
		{
			cout << curr->val << " " ;
			curr = curr->right;
		}else{
			pre=curr->left;
			while(pre->right && pre->right  != curr )
				pre = pre->right;
			if( !pre->right)
			{
				pre->right = curr;
				curr=curr->left;
			}else{
				cout << curr->val << " ";
				pre->right=NULL;
				curr=curr->right;
			}
		}
	}
	cout << "end morris traversal\n";
}
