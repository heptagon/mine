#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;


typedef struct TN {
	int val;
	struct TN* l;
	struct TN* r;
} TN;


class BTree 
{

	public:
	BTree()
	{
		root=NULL;
	}

	~BTree()
	{
		
	}


	
	friend ostream& operator << (ostream& os, BTree* tr)
	{
		os<< "Hello\n";
		tr->initialize_output();
		tr->format(tr->root);
		tr->print(os);
		return os;
	}
		
/*
		
		unsigned int max_nodes=(2 << (h-1)) -1;
		os << max_nodes << "\n";
		unsigned int max_leaf_nodes=(max_nodes+1)/2;
		int space_w=1;
		int block_w=2;
		vector<string> sv ;
		sv.get_allocator().allocate(h);
		int max_str_len=max_leaf_nodes*block_w+(max_leaf_nodes-1)*space_w;
		for(int ii=0;ii<h;++ii)
		{
			string tmp=string(max_str_len*2,' ');
			sv.push_back(tmp);	
		}
		int level=0;
		TN* t=tr->root;
		TN* tmp=NULL;
		stack<TN*> s;
		int pos=0;
		const char SPACE=' ';
		os << "printing tree:\n";


		while(true)
		{
			while(t)
			{
				s.push(t);
				level++;
				t=t->l;
			}
			
			if ( !s.empty())
			{
				t=s.top();
				os << s.size() << ":" << pos << ":" << t->val << ":" << level << ":\n" ;	
				//os << t->val << " ";
				s.pop();
				t=t->r;
				if (!t)
					level--;
			}
			else{
				break;
			}
		}
*/

/*	

			while(t)
			{
				stn.push(t);
				level++;
				t=t->l;
			}
			t=stn.top();
			stringstream ss;
			ss << t->val;
			string fstr(block_w,' ');
			fstr.replace(0,ss.str().size(),ss.str());

			os << stn.size() << ":" << pos << ":" << t->val << ":" << level << ":\t" ;	
			sv[level-1].replace(pos,block_w,fstr);pos+=block_w;
			sv[level-1].replace(pos++,space_w,&SPACE);
			os << sv[level-1] << endl;	
			stn.pop();
			level--;
			int prev_val=t->val;

			while(!stn.empty() &&  !t->r)
			{
				t=stn.top();
				if ( prev_val > t->val)
				{
					stn.pop();
					level--;
					continue;
				}
				stringstream ss;
				ss << t->val;
				string fstr(block_w,' ');
				fstr.replace(0,ss.str().size(),ss.str());
				os << stn.size() << ":" << pos << ":" << t->val << ":" << level << ":\t";	
				sv[level-1].replace(pos,block_w,fstr);pos += block_w;
				sv[level-1].replace(pos++,space_w,&SPACE);
				os <<  sv[level-1] << endl;	
				stn.pop();
				level--;
			}
			if (t) {
				t=t->r;
				stn.push(t);
				level++;
			}
		} while(t);
		for(int ii=0;ii<h;++ii)
			os << sv[ii] << "\n";
		os << "end printing\n";
		return os;
	}
*/

	BTree* insert(int val)
	{
		TN* n= new TN();
		n->val=val;
		n->l=NULL;
		n->r=NULL;
		
		if (!root)
		{
			root=n;
			return this;
		}

		TN* t=root;
		TN* tmp=t;
		while(t)
		{
			tmp=t;
			if ( val <= t->val)
				t=t->l;
			else 
				t=t->r;			
		}
		if ( val <= tmp->val)
			tmp->l=n;
		if ( val > tmp->val)
			tmp->r=n;
		return this;
	}		

	BTree* dtree(int val)
	{
		TN* t=root;
		TN* parent=t;
		for(;t && t->val != val;parent=t)
			t = val <  t->val ? t->l : t->r;

		if (!t)
			cout << "cant delete : Element not found\n";
	
		if ( parent->l== t)
		{
			if ( !t->l && !t->r)
			{
				delete t;
				parent->l=NULL;
			}else 
			{
				TN* lrp=left_most_node_parent(t->r);
				if ( lrp )
				{
					if ( lrp->l)
					{
						TN* tmp=lrp->l;
						parent->l->val=lrp->l->val; // dont delete t now
						lrp->l=lrp->l->r;
						delete tmp;
					}else
					{
						parent->l=t->r;
						delete t;
					}
				}else{
						
					TN* rlp=right_most_node_parent(t->l);
					if ( rlp)
					{
						if(rlp->r)
						{
							TN* tmp=rlp->r;
							parent->l->val=rlp->r->val; //dont delete t now
							rlp->r=rlp->r->l;
							delete tmp;
						}else
						{
							parent->l=t->l;
							delete t;
						}
					}
				}
			}
		}else  // parent->r ==t  
		{
			if ( !t->l && !t->r)
			{
				delete t;
				parent->r=NULL;
			}else 
			{
				TN* lrp=left_most_node_parent(t->r);
				if ( lrp )
				{
					if ( lrp->l)
					{
						TN* tmp=lrp->l;
						parent->r->val=lrp->l->val; // dont delete t now
						lrp->l=lrp->l->r;
						delete tmp;
					}else
					{
						parent->r=t->r;
						delete t;
					}
				}else{
						
					TN* rlp=right_most_node_parent(t->l);
					if ( rlp)
					{
						if(rlp->r)
						{
							TN* tmp=rlp->r;
							parent->r->val=rlp->r->val; //dont delete t now
							rlp->r=rlp->r->l;
							delete tmp;
						}else
						{
							parent->r=t->l;
							delete t;
						}
					}
				}
			}
		}
		return this;
	}

	void inorder()
	{
		ino(root);
		cout << "\n";
	}

	void preorder()
	{
		preo(root);
		cout << "\n";
	}

	void postorder()
	{
		posto(root);
		cout << "\n";
	}

	int height()
	{
		return ht(root);
	}
	protected:
	void ino(TN* n)
	{
		if (!n) return;
		ino(n->l);
		cout << n->val << ",";
		ino(n->r);
	}	

	void preo(TN* n)
	{
		if(!n) return;
		cout << n->val << ",";
		preo(n->l);
		preo(n->r);
	}

	void posto(TN* n)
	{
		if(!n) return;
		posto(n->l);
		posto(n->r);
		cout << n->val << ",";
	}

	int ht(TN* n)
	{
		if(!n) return 0;
		return max(ht(n->l),ht(n->r)) + 1;
			
	}	
	
	TN* left_most_node_parent(TN* n)
	{
		if ( !n || !n->l) return n;
		for(;n->l->l;n=n->l); 
		return n;
	}

	TN* right_most_node_parent(TN* n)
	{
		if ( !n || !n->r) return n;
		for(;n->r->r;n=n->r); 
		return n;
	}

	ostream& print(ostream& os)
	{
		for(int i=0;i<vs.size();++i)
		{
			os << vs[i]  << endl;
		}
		os << endl;
		return os;

	}
	void format(TN* n)
	{
		if ( !n)
			return;

		curr_level++;format(n->l);curr_level--;
		write_node(n);
		curr_level++;format(n->r);curr_level--;		
	}

	void write_node(TN* n)
	{
		center_text(n->val);
		curr_pos+=block_w;
	}

	void initialize_output()
	{
		int h= height();
		int max_leaf_nodes=2<<(h-2);
		cout << "max_leaf_nodes " << max_leaf_nodes << endl;
		block_w=3;
		pad_w=1;
		curr_pos=0;
		curr_level=0;
		//int max_width=max_leaf_nodes*(block_w+pad_w);
		int max_width=400;
		
		for(int i=0;i<h;i++)
		{
			string s;
			s.assign(max_width,' ');	
			vs.push_back(s);
		}
	}

	void center_text(int v)
	{
		stringstream ss;
		ss << v;
		vs[curr_level].insert(curr_pos,ss.str());
	}

	TN* root;

	int block_w;
	int pad_w;
	int curr_pos;
	int curr_level;
	vector<string> vs;

};

void randomly_fill_btree(BTree* b)
{
	for(int ii=0;ii<40;++ii)
	{
		int i=rand()%100;
		cout << "inserting " << i << endl;
		b->insert(i);
	}
}

int main(int argc, char** argv)
{
/*
	BTree* b= new BTree();
	b->insert(1)->insert(4)->insert(6)->insert(9)->insert(3)->insert(2)->insert(5);
	b->inorder(); 
	b->preorder();
	b->postorder();
	cout << "HT is " << b->height() <<  endl;
	cout << b;
*/
	BTree* b2= new BTree();
	randomly_fill_btree(b2);
	b2->inorder();
	cout << "HT is " << b2->height() <<  endl;
	cout << b2;

	
	return 0;
}
