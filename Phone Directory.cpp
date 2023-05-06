#include<string.h>
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include <unistd.h>
using namespace std;
int is_valid_contactNo(string contact_no)
{
	int i,count,flag;
 	for(i=1;contact_no[i]!='\0';i++){
 		count++;
 		if(contact_no[i]-48>=0 && contact_no[i]-48<=9)
    	{
	      	flag=1;
	      	continue;
    	}
    	else
    	{
	      	flag=0;
	      	break;
    	}			
	}
	if(flag==1 && count==11)
	{
		return 1;
	}
	else if(flag==0 || count!=11)
	{
		cout<<"\nInvalid Number!!!\nContact Number must be of 11 digits."<<endl<<endl;
		return 0;
	}
}
void printer(char x[],char y[],char z[]){
    cout<<(char)186<<setw(20)<<x
		<<(char)186<<setw(20)<<y
		<<(char)186<<setw(30)<<z<<(char)186<<endl;
}
void endd(){
    int i;
    cout<<(char)200;
    for( i=0;i<20;i++)
    	cout<<(char)205;
    cout<<(char)202;
    
    for(int i=0;i<20;i++)	
    	cout<<(char)205;
    cout<<(char)202;
    
    for( i=0;i<30;i++)
    	cout<<(char)205;
    cout<<(char)188;
}

class node
{
	public:
	char name[128], contact_no[256], email[128];;
	class node *left;
	class node *right;
	int hgt;// height
};

class tree{
public:
	node* root;
	node* insert(char* , char* , char* , node*);
	void in_traversal(node*, bool);
	bool search(node* , char*);
	node* ddelete(node* , char*);
	int update(node* , char*);
	tree()
	{
		root=NULL;
	}
private:
	node * min(node *);
	int height(node *);
	int BF(node*);
	node * LR(node*);
	node * LL(node*);
	node * RL(node*);
	node * RR(node*);
	node * rotateleft(node*);
	node* rotateright(node*);
};

int tree :: height(node* root)
{
	int lh , rh;
	if(root->left==NULL)
		lh=0;
	else
		lh=1+root->left->hgt;
	if(root->right==NULL)
		rh=0;
	else
		rh=1+root->right->hgt;
	if(lh>rh)
		return lh;
	return rh;
}

int tree :: BF(node* root)
{
	int lh, rh;				//lh=left height    ,	rh=right height
	if(root==NULL)
		return 0;
	if(root->left==NULL)
		lh=0;
	else
		lh=1+root->left->hgt;
	if(root->right==NULL)
		rh=0;
	else
		rh=1+root->right->hgt;
	return (lh-rh);
}

node * tree :: RR(node *root)
{
	root=rotateleft(root);
	return root;
}
node * tree :: LL(node *root)
{
	root=rotateright(root);
	return root;
}

node * tree :: LR(node* root)
{
	root->left=rotateleft(root->left);
	root=rotateright(root);
	return root;
}

node * tree :: RL(node* root)
{
	root->right=rotateright(root->right);
	root=rotateleft(root);
	return root;
}

node * tree :: rotateright(node* x)
{
	node *y ;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->hgt=height(x);
	y->hgt=height(y);
	return y;
}

node * tree :: rotateleft(node* x)
{
	node *y ;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->hgt=height(x);
	y->hgt=height(y);
	return y;
}

node * tree :: min(node *q)
{
	while(q->left != NULL)
	{
		q = q->left;
	}
	return q;
}
node* tree :: insert(char* name , char* contact_no , char* Email, node* root)
{
	int cmp;
	if(root==NULL){
		root=new node;
		root->left=NULL;
		root->right=NULL;
		strcpy(root->name , name);
		strcpy(root->contact_no , contact_no);
		strcpy(root->email , Email);
	}
	else
	{
		cmp=strcasecmp( name , root->name);         //like aisha < inmbsat
		if(cmp<0)
		{
			root->left=insert( name , contact_no ,Email, root->left);
			if(BF(root)==2)
			{
				if( strcasecmp( name , root->left->name) < 0 )
					root=LL(root);
				else
					root=LR(root);
			}
		}
		else if(cmp>0)
		{
			root->right =insert( name ,contact_no ,Email, root->right);
			if(BF(root)==-2)
				{
					if(strcasecmp( name , root->right->name)>0)
						root=RR(root);
					else
						root=RL(root);
				}
		}
		else
		{
			cout<<"ALREADY EXIST!!!"<<endl;
			sleep(1);
		}
	}
	
	root->hgt=height(root);
	return root;
}

void tree ::in_traversal(node* head, bool print=true)//LVR
{
	fstream i;
	if(head!=NULL) 
	{	
		if(print){
			in_traversal(head->left);
		}
		else{
			in_traversal(head->left, false);
		}
		i.open("file.txt", ios::in | ios::out | ios::app);
//		cout<<head->name<<" "<<head->contact_no<<" "<<head->email<<"\n";
		i<<head->name<<" "<<head->contact_no<<" "<<head->email<<"\n";
		i.close();
		if(print){
			printer(head->name,head->contact_no,head->email);
			in_traversal(head->right);
		}
		else{
			in_traversal(head->right, false);
		}
	}
}
bool tree :: search(node* head , char *name)
{

	while(head!=NULL)
	{
		int cmp=strcasecmp( name , head->name);
		if(cmp==0)
		{
			cout<<endl<<endl<<"Name: "<<head->name<<endl<<"Contact:\t"<<head->contact_no<<endl<<"Email:"<<head->email<<endl;
			return true;

		}
		else if(cmp<0)
		{
			head=head->left;
		}
		else if(cmp>0)
		{
			head=head->right;
		}
	}
	return false;
}

node* tree :: ddelete(node* root , char* name )
{
	node *temp;
	int cmp;
	cmp=strcasecmp(name , root->name);
	if(root==NULL)
	{
		cout<<"Phone Directory not created"<<endl;
		return root;
	}
	else if(cmp<0)
	{
		root->left=ddelete(root->left , name);
		if(BF(root)==-2)
		{
			if(BF(root->right)<=0)
				root=RR(root);
			else
				root=RL(root);
		}
	}

	else if(cmp>0)
	{
		root->right=ddelete(root->right , name);
		if(BF(root)==2)
		{
			if(BF(root->left)>=0)
				root=LL(root);
			else
				root=LR(root);
		}
	}
	else
	{
		if(root->right!=NULL)
		{
			temp=root->right;
			while(temp->left!=NULL)
				temp=temp->left;
			strcpy(root->name , temp->name);
			strcpy(root->contact_no , temp->contact_no);
			root->right=ddelete(root->right , temp->name);
			if(BF(root)==2)
			{
				if(BF(root->left)>=0)
					root=LL(root);
				else
					root=LR(root);
			}
		}
		else
		{
			return root->left;
			cout<<"\nSorry!! Entered contact not found\n"<<endl;
		}

	}
	root->hgt=height(root);
	return root;
}

int tree :: update(node* head , char* name)
{
	char New[256];
	while(head!=NULL)
	{
		int cmp;
		cmp=strcasecmp( name , head->name );
		if(cmp==0)
		{	
			do{
				cout<<"Enter new Contact number: ";
	  			cin>>New;
    		}while(is_valid_contactNo(New) == 0);
			strcpy(head->contact_no , New);
			cout<<"Contact updated =)"<<endl;
			return 1;
		}
		if(cmp<0)
			head=head->left;
		if(cmp>0)
			head=head->right;
	}
	return 0;
}

int is_valid_email(char email[]){
	int i;
	
 	for(i=0;email[i]!='\0';i++){
	 	if(email[i]=='@'){
	 		sleep(2);
			return 1;
		}
	}
	cout<<"Invalid email!!!!"<<endl<<endl;
	return 0;
}
int main()
{	int temp0, ch , rtrn;
	char name[128], contact_no[256], email[128];
	node * head;
	head=NULL;
	tree t;
	fstream  fp;
	fp.open("file.txt", ios::in);

	char data[256];
	if(!fp)
	{
		cout<<"Error in opening file!"<<endl;
	}
	else{
		while(fp>>data){
			strcpy(name,data);
	        fp>>contact_no;
			fp>>email;
//	        cout<<name<<contact_no<<email<<endl;
	        if(strcmp(data,"")!=0){
	            head = t.insert( name , contact_no, email , head);
	        }
	    }
	}
	fp.close();

	do{
		
		cout<<"\n  PERSONAL PHONE DIRECTORY"<<endl;
		cout<<"-------------------------------"<<endl;
		cout<<"\n1. INSERT new NUMBER\n2. DISPLAY ALL NUMBERS\n3. SEARCH CONTACT NUMEBR BY NAME\n4. DELETE CONTACT NUMBER\n5. UPDATE NUMBER BY NAME\n6. EXIT"<<endl;
		cout<<"\n\nENTER OPERATION NUMBER : "<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:	
				cout<<"\nEnter Name: ";
				cin>>name;
				do{
					cout<<"Enter Contact number: ";
		  			cin>>contact_no;
    			}while(is_valid_contactNo(contact_no) == 0);
				
				do{
					cout<<"Enter email: ";
					cin>>email;
    			}while(is_valid_email(email) == 0);
				head = t.insert( name , contact_no, email, head);
				cout<<"Wait Please =)";
				sleep(2);
				break;
			case 2: 
				if(head!=NULL){
					system("cls");
					cout<<"\nContacts Present in the Directory are:"<<endl;
					remove("file.txt");
					t.in_traversal(head);
			 		endd();
			 		sleep(2);
			 		cout<<endl<<"Type any NUMBER and press enter to continue...";
					cin>>temp0;
				}
			 	else{
			 		cout<<"\nOOPS!!! DIRECTORY IS EMPTY .... =("<<endl;
			 		sleep(1);
				}
			 	break;

			case 3: 
				cout<<"Enter Name:"<<endl;
				cin>>name;
				rtrn =t.search(head , name);
				if(rtrn==1){
					cout<<"\nCONTACT FOUND !!!"<<endl;
					cout<<"Enter any number to continue....";
					cin>>temp0;
				}
				else
				{
					cout<<"OOPS!! CONTACT NOT FOUND =("<<endl;
					sleep(2);
				}
				break;

			case 4: 
				cout<<"Enter Name: "<<endl;
			 	cin>>name;
			 	rtrn =t.search(head , name);
			 	if(head==NULL)
			 	{
				 	cout<<"\nOOPS!!! DIRECTORY IS EMPTY ...."<<endl;
				 	sleep(2);
			 	}
			 	else if(head!=NULL && rtrn ==1){
			 			head= t.ddelete(head , name);
					 	cout<<"Enter any number to continue....";
						cin>>temp0;
				}
			 	else
					cout<<"\nOOPS!! Contact Number doesn't exist =("<<endl;
					sleep(2);
			 	break;

			case 5: 
				cout<<"Enter Name to Update its Contact Number Number"<<endl;
			    cin>>name;
			 	rtrn =t.update(head , name);
			 	if(rtrn==1){
				 	cout<<"\nContact "<<name<<" is updated"<<endl;
				 	sleep(2);
				 }
			 	else{
				 	cout<<"\nOOPS!! CONTACT NUMBER DOES NOT EXISTS"<<endl;
				 	sleep(2);
				 }
			 	break;

			case 6: 
				if(head!=NULL){
					remove("file.txt");
					system("cls");
			 		t.in_traversal(head, false);
				}
				cout<<"THANK YOU =)";
				sleep(3);
			 	break;

			default: 
				cout<<"\nOOPS!! YOU HAVE ENTERED INVALID CHOICE"<<endl;
				sleep(2);
				break;
		}
		system("cls");
	}while(ch!=6);
	return 0;
}

