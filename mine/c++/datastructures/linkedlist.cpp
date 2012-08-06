#include <iostream>
#include <string>

using namespace std;

typedef struct LLNode {
  int val;
  LLNode* next;
} LLNode;

LLNode* create_linked_list(int range);

void printlist(LLNode* head, string str);
LLNode* insert_node_with_val(LLNode* head, int val);
LLNode* delete_node_with_val(LLNode* head, int val);
LLNode* reverse_list(LLNode* head);


int main ( int argc, char** argv)
{
  LLNode* head=NULL;
  head=create_linked_list(10); //sorted
  printlist(head,"initial creation");

  head=insert_node_with_val(head,8); printlist(head,"after inserting 8");
  head=insert_node_with_val(head,0); printlist(head,"after inserting 0");
  head=insert_node_with_val(head,11);printlist(head,"after inserting 11");
  head=insert_node_with_val(head,12);printlist(head,"after inserting 12");
  head=reverse_list(head);printlist(head,"after reversing");

  head=delete_node_with_val(head,7);printlist(head,"after deleting 7");
  head=delete_node_with_val(head,0);printlist(head,"after deleting 0");
  head=delete_node_with_val(head,12);printlist(head,"after deleting 12");  

  return 0;
}


void printlist(LLNode* head, string str)
{
  cout << str << endl;
  LLNode* ptr=head;
  while (ptr!= NULL ){
    cout << ptr->val << " ";
    ptr=ptr->next;
  }
  cout << "\n";
}


LLNode* insert_node_with_val(LLNode* head, int val)
{
  LLNode* newnode = new LLNode();
  
  newnode->val=val;
  newnode->next=NULL;

  if ( head == NULL )
    return newnode;

  if ( val < head->val) {
    newnode->next=head;
    return newnode;
  }

  LLNode* currptr=head;
  while ( currptr->next != NULL ){
    if ( currptr->next->val < val)
      currptr=currptr->next;
    else
      break;
  }
  if ( currptr->next==NULL)
    newnode->next= NULL;

  LLNode* tempptr=currptr->next;
  currptr->next=newnode;
  newnode->next=tempptr;;
  
  return head;
      
}

LLNode* delete_node_with_val(LLNode* head, int val)
{
  if ( head == NULL) {
    return NULL;
  }

  if ( head->val==val){
    LLNode* temp=head->next;
    delete head;
    head=NULL;
    return temp;
  }
  
  LLNode* prevptr=head;
  LLNode* currptr=head->next;
  
  while(currptr != NULL){
    if( currptr->val==val){
      prevptr->next=currptr->next;
      delete currptr;
      currptr=NULL;
      return head;
    }
    prevptr=currptr;
    currptr=currptr->next;
  }
  cout << "Val not found\n";
  return head;
}

LLNode* create_linked_list(int range)
{
  LLNode* head=NULL;
  if ( range <=0 ) 
    return NULL;
  
  LLNode* newnode=new LLNode();
  newnode->val=1;
  newnode->next=NULL;
  head=newnode;
  for ( int ii=2; ii<=range;++ii){
    LLNode* new2node=new LLNode();
    new2node->val=ii;
    new2node->next=NULL;

    newnode->next=new2node;
    newnode=new2node;
  }
  return head;
}

LLNode* reverse_list(LLNode* head)
{

  if ( head == NULL || head->next == NULL ) 
    return head;

  LLNode* currptr=head;
  LLNode* revlistptr=NULL;
  while ( currptr->next != NULL){

    LLNode* tempptr=currptr->next;
    currptr->next=revlistptr;

    revlistptr=currptr;
    currptr=tempptr;
  }
  currptr->next=revlistptr;
  return currptr;

}
