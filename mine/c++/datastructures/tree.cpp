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

void printtree(treenode* root, string str);
void printlevels(treenode* root, int level,int shift); //private

treenode* balance_tree(treenode* root);

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

  root=balance_tree(root); printtree(root,"after balancing");

  cout << "Height of the tree is " << heightT(root) << " \n";
  cout << "nof leaf nodes of the tree is" << leaf_nodes(root) << " \n";
  cout << "depth of node 19 is " << depth(root,19) << endl;

  
  return 0;
}


treenode* balance_tree(treenode* root)
{
  return root;
}

treenode* create_tree(int range)
{
  
  treenode* root = new treenode();
  root->val=1;
  root->left=NULL;
  root->right=NULL;
  
  treenode* currnode=root;

  for(int ii=2; ii<=range; ++ii, currnode=root){
    insert_node(root,ii);
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
	return root;
      }else{
	currnode=currnode->left;
      }
    }else { // if ( val  > currnode->val){
      if ( currnode->right == NULL){
	currnode->right=newnode;
	return root;
      }else{
	currnode=currnode->right;
      }
    }
  }

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
      return root;
    }

    if ((currnode->left != NULL && currnode->right == NULL)) {
      if ( !parent){
	treenode* temp=root->left;
	root->val = root->left->val;
	root->left=root->left->left;
	root->right=root->left->right;
	delete temp;
	return root;
      }
	
      if ( parent->left == currnode )
	parent->left = currnode->left;
      if ( parent->right == currnode)
	parent->right = currnode->left;
      delete currnode;
      currnode=NULL;
      return root;
    }
    if (( currnode->left == NULL && currnode->right != NULL)) {
      if ( !parent){

	treenode* temp=currnode->right;
	currnode->val=currnode->right->val;
	currnode->right=currnode->right->right;
	currnode->left=currnode->right->left;

	delete temp;
	return root;
      }
      if ( parent->left == currnode)
	parent->left = currnode->right;
      if ( parent->right == currnode)
	parent->right = currnode->right;
      delete currnode;
      currnode=NULL;
      return root;
    }
    if ( currnode->left != NULL && currnode->right !=NULL){
      // find nearest node just smaller than it 
      // alt. I could have found nearest node just larger than it
      if (currnode->left->right == NULL ){
	currnode->val=currnode->left->val;
	currnode->left=currnode->left->left;
	delete currnode->left;
	return root;
      }else{
	treenode* just_lowests_parent=find_parent_rightmost_node(currnode->left);
	currnode->val=just_lowests_parent->right->val;
	delete just_lowests_parent->right;
	just_lowests_parent->right=NULL;
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

