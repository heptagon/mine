#include <iostream>
using namespace std;

typedef struct Node
{
	int val;
	struct Node* next;
} Node;

class LList
{
	public:
		LList()
		{
			head=NULL;
			curr=NULL;
		}

		~LList()
		{
			while(head) 
				remove(head->val);
		}

		LList* add(int val)
		{
			Node* n=new Node();
			n->val=val;
			n->next=NULL;
			if (!head)
				head=n;
			else
				curr->next=n;
			curr=n;
			return this;
		}

		LList* remove(int val)
		{
			Node* p=head;
			if ( !p)
				return this;

			if ( p->val == val)
			{
				head=p->next;
				delete p;
				return this;
			}

			for(p=head; p && p->next && p->next->val != val;p=get_next(p));
			if ( p && p->next && p->next->val == val)
			{
				Node* tmp=p->next;
				p->next=p->next->next;
				if( !p->next) 
					curr=p;

				delete tmp;
			}
			return this;
		}


		LList* p()
		{
			for(Node*p = head; p ; p=get_next(p))
				cout << p->val << "," ;

			cout << endl;
			return this;
		}
		LList* reverse()
		{
			Node* reversed=head;
			Node* n=head->next;
			
			while(n)
			{
				Node* nxt2=n->next;
				n->next=reversed;
				reversed=n;
				n=nxt2;
			}	

			head->next=NULL;
			curr=head;
			head=reversed;
			return this;
		}
	protected:
		
		Node*  get_next(Node* n)
		{
			return n ? n->next : n;
		}
		
		Node* head;
		Node* curr;

};

class StackL : public LList{
	public:
		StackL()
		{
		}

		~StackL()
		{
		}


		StackL* add_before_head(int val)
		{
			Node* n = new Node();
			n->val=val;
			n->next=head;
			head=n;
			return this;
		}

		StackL* push(int val)
		{
			return add_before_head(val);	
		}

		int pop()
		{
			if ( head)
			{		
				int ret=head->val;
				remove(head->val);
				return ret;
			}
			return 0;
		}

		StackL* p()
		{
			LList::p();
			return this;
		}

};

class QueueL : public LList
{
	public:
	QueueL() {};
	~QueueL(){};
	
	QueueL* enq(int val)
	{
		add(val);
		return this;
	}

	QueueL*  dq()
	{
		if(head)
			remove(head->val);
		return this;
	}

	QueueL* p()
	{
		LList::p();
		return this;
	}

};

int main(int argc,char** argv)
{
	LList* l = new LList();
	l->add(1)->p()->add(2)->p()->add(4)->p()->add(10)->p()->add(80)->p();
	l->reverse()->p();
	l->remove(44)->p()->remove(2)->p()->remove(10)->p()->remove(80)->p()->remove(1)->p()->remove(4)->p()->remove(99)->p();


	StackL* s = new StackL();
	s->push(1)->p()->push(2)->p()->push(5)->p()->push(3)->p();
	s->pop();
	s->p();
	s->pop();
	s->p();
	s->pop();
	s->p();
	s->pop();
	s->p();

	QueueL* q = new QueueL();
	q->enq(1)->p()->enq(2)->p()->enq(5)->p();
	q->dq()->p()->dq()->p()->dq()->p();

	return 0;
}


