/*Author:Bukkala Praneeth*/

#include<stdio.h>
class Node{			//creating a node with number, parent node and children array node
public:
	int number;
	class Node* parent;
	class Node* child[100]; //Creating class node pointer with children array and Taking 100 as maximum number of children
};

class FamilyTree{
	class Node* root;	//Intialising node as root 
public:
	FamilyTree(int value);	//Constructor	
	void insertChild(int par,int child);//funtion to insert child
	class Node *search(int par);		//search for a number with only one input as integer
	class Node* search_node(Node*,int par); //searching for a number and it takes two inputs one is integer and other is node 
	void relationship(int x,int y);		//to find relationship between two integers
};

FamilyTree::FamilyTree(int value){		//Constructor which takes input as integer and it is the root node value or number  
	root = new Node;			//creating a new node and taking it as root node
	root->parent = NULL;			//pointing the parent node of root node to NULL
	root->number = value;			//assigning input value to root nodes number
	for(int i=0;i<100;i++){			//Intialising all its children nodes to NULL
		root->child[i] = NULL;
	}
}

void FamilyTree::insertChild(int par,int child){	//this function inserts the child node and takes input as its parent value and child value which we have to insert
	class Node* new_node = new Node;		//creating a new node and assigning to a temparory class node 
	if(root->number == par){			//checks the given input parent value and if it matches with the value of root node in tree 	
		int i=0;
		while(root->child[i]!=NULL){		//checks the first null pointer in children array and incrementing i value
			i+=1;	
		}
		root->child[i] = new_node;		//assigning the new node to ith position of children array which is first null node in children array
		root->child[i]->parent = root;		//and pointing the parent of this children array to root node
		for(int i=0;i<100;i++){
			new_node->child[i] = NULL;	//intialising children array of new node to null
		}
		new_node->number = child;		//pointing the number of new node to the given integer child
		return; 
	};
	class Node* head = search(par);			//search for a parent node with the given input integer		
	int j=0;
	while(head->child[j]!=NULL){			//checks the first null pointer in children array and incrementing i value		
		j+=1;	
	}
	head->child[j] = new_node;			//assigning the new node to jth position of children array which is first null node in children array
	head->child[j]->parent = head;			//pointing the number of new node to the given integer child
	for(int j=0;j<100;j++){
		new_node->child[j] = NULL;		//intialising children array of new node to null
	}
	new_node->number = child; 			//pointing the number of new node to the given integer child
}

class Node* FamilyTree::search(int par){		//this function is used to search an integer
	return search_node(root,par);
}

class Node* FamilyTree::search_node(Node* start,int k){//this function is used to search an integer which takes node and integer as input
    	class Node* temp;
    	if(start->number==k) return start;
    	if(start->child[0]==NULL) return NULL;		//base case or leaf node
    	for(int i=0;start->child[i]!=NULL;i++){
        	temp=search_node(start->child[i],k);	//recursive step
        	if(temp!=NULL) return temp;
    	}
    	return NULL;
}

void FamilyTree::relationship(int x,int y){		//this function takes two numbers as input and prints the relation between them
	if(search(x)==NULL||search(y)==NULL){printf("%d is Unrelated to %d\n",x,y);}//if both integers are not from same tree then prints unrelated
	else {
	class Node* head1 =search(x);			//search for an integer in tree and points to the head1 node
	class Node* head2 =search(y);			//search for an integer in tree and points to the head2 node
	class Node* temp1 =search(x);			//search for an integer in tree and points to the temp1 node
	class Node* temp2 =search(y);			//search for an integer in tree and points to the temp2 node
	int gen1=0;					
	int gen2=0;
	while(head1->number!=root->number){		//finds the generation number of integer x
		gen1+=1;				//incrementing the value till we get root node
		head1=head1->parent;			//incrementing head1 to its parent 
	}
	while(head2->number!=root->number){		//finds the generation number of integer y
		gen2+=1;				//incrementing the value till we get root node
		head2=head2->parent;			//incrementing head2 to its parent
	}
	int gen=0;
	gen = gen2 - gen1;				//subtacting both generation values we get vertical distance in tree between the given two integers
	int i=0;
	int j=0;
	if(gen >= 0){
	while(j!=gen){
		j++;					
		temp2=temp2->parent;			//here temp2 will come to the same level of temp1	
		}
	while(temp2->number!=temp1->number){		//this while loop is used to find horizontal distance between the given nodes
		i++;					//here i value is used to find horizontal distance
		temp2=temp2->parent;
		temp1=temp1->parent;		
		}
	//since we know i(vertical distance) and gen(horizontal distance) we can now say directly relationship
	if(gen == 0){		
		if(i==1)	printf("%d is sibling of %d\n",x,y);	//if horizontal and vertical distaces are 0 implies sibling
		else if(i==2)	printf("%d is %dst cousin of %d \n",x,i-1,y);	//if horizontal distance is 1 and vertical distace is 0  implies cousin
		//similarly for other if else statements also
		else if(i==3)	printf("%d is %dnd cousin of %d \n",x,i-1,y);
		else if(i==4)	printf("%d is %drd cousin of %d \n",x,i-1,y);
		else 	printf("%d is %dth cousin of %d \n",x,i-1,y);	
		}
	else if(gen == 1){
		if(i==0) printf("%d is parent of %d\n",x,y); //if horizontal distance is 0 and vertical distace is 1  implies parent
		//similarly for remaining all
		else if(i==1)	printf("%d is Uncle or aunt of %d\n",x,y);
		else if(i==2)	printf("%d is %dst cousin once removed of %d\n",x,i-1,y);
		else if(i==3)	printf("%d is %dnd cousin once removed of %d\n",x,i-1,y);
		else if(i==4)	printf("%d is %drd cousin once removed of %d\n",x,i-1,y);
		else 	printf("%d is %dth cousin once removed of %d\n",x,i-1,y);	
		}
	else if(gen == 2){
		if(i==0) printf("%d is Grand parent of %d\n",x,y); //if horizontal distance is 0 and vertical distace is 2  implies parent
		//similarly for remaining all
		else if(i==1)	printf("%d is Great Uncle or aunt of %d\n",x,y);
		else if(i==2)	printf("%d is %dst cousin twice removed of %d\n",x,i-1,y);
		else if(i==3)	printf("%d is %dnd cousin twice removed of %d\n",x,i-1,y);
		else if(i==4)	printf("%d is %drd cousin twice removed of %d\n",x,i-1,y);
		else 	printf("%d is %dth cousin twice removed of %d\n",x,i-1,y);	
		}
	else if(gen == 3){
		if(i==0) printf("%d is Great Grand parent of %d\n",x,y); //if horizontal distance is 0 and vertical distace is 3  implies parent
		//similarly for remaining all
		else if(i==1)	printf("%d is Great Grand Uncle or aunt of %d \n",x,y);
		else if(i==2)	printf("%d is %dst cousin thrice removed of %d\n",x,i-1,y);
		else if(i==3)	printf("%d is %dnd cousin thrice removed of %d\n",x,i-1,y);
		else if(i==4)	printf("%d is %drd cousin thrice removed of %d\n",x,i-1,y);
		else 	printf("%d is %dth cousin thirce removed of %d\n",x,i-1,y);	
		}
	else if(gen == 4){
		if(i==0) printf("%d is Great Great Grand parent of %d\n",x,y);
		else if(i==1)	printf("%d is Great Great Grand Uncle or aunt of %d \n",x,y);
		else if(i==2)	printf("%d is %dst cousin 4 times removed of %d\n",x,i-1,y);
		else if(i==3)	printf("%d is %dnd cousin 4 times removed of %d\n",x,i-1,y);
		else if(i==4)	printf("%d is %drd cousin 4 times removed of %d\n",x,i-1,y);
		else 	printf("%d is %dth cousin 4 times removed of %d\n",x,i-1,y);	
		}
	
	else if(gen==5){
		if(i==0) printf("%d is 3rd Great Grand parent of %d\n",x,y); //if horizontal distance is 0 and vertical distace is 4  implies parent
		//similarly for remaining all
		else if(i==1)	printf("%d is 3rd Great Grand Uncle or aunt of %d \n",x,y);
		else if(i==2)	printf("%d is %dst cousin %d times removed of %d\n",x,i-1,gen,y);
		else if(i==3)	printf("%d is %dnd cousin %d times removed of %d\n",x,i-1,gen,y);
		else if(i==4)	printf("%d is %drd cousin %d times removed of %d\n",x,i-1,gen,y);
		else 	printf("%d is %dth cousin %d times removed of %d\n",x,i-1,gen,y);	
		}
	else	{
		//from here directly we can use generation value
		if(i==0) printf("%d is %dth Great Grand parent of %d\n",x,gen-2,y);
		else if(i==1)	printf("%d is %dth Great Grand Uncle or aunt of %d \n",x,gen-2,y);
		else if(i==2)	printf("%d is %dst cousin %d times removed of %d\n",x,i-1,gen,y);
		else if(i==3)	printf("%d is %dnd cousin %d times removed of %d\n",x,i-1,gen,y);
		else if(i==4)	printf("%d is %drd cousin %d times removed of %d\n",x,i-1,gen,y);
		else 	printf("%d is %dth cousin %d times removed of %d\n",x,i-1,gen,y);	
		}
	}
	else {
		while(j!=-gen){
			j++;
			temp1=temp1->parent;	     //here temp1 will come to the same level of temp2	
			}
		while(temp2->number!=temp1->number){ //this while loop is used to find horizontal distance between the given nodes
			i++;
			temp2=temp2->parent;
			temp1=temp1->parent;		
			}
		//everything is similar like above if statement
		if(gen == -1){
			if(i==0) printf("%d is childof %d\n",x,y);
			else if(i==1)	printf("%d is Niece or Nephew of %d \n",x,y);
			else if(i==2)	printf("%d is %dst cousin once removed of %d\n",x,i-1,y);
			else if(i==3)	printf("%d is %dnd cousin once removed of %d\n",x,i-1,y);
			else if(i==4)	printf("%d is %drd cousin once removed of %d\n",x,i-1,y);
			else 	printf("%d is %dth cousin once removed of %d\n",x,i-1,y);	
		}
		else if(gen == -2){
			if(i==0) printf("%d is Grand child of %d\n",x,y);
			else if(i==1)	printf("%d is Grand Niece or Nephew of %d \n",x,y);
			else if(i==2)	printf("%d is %dst cousin twice removed of %d\n",x,i-1,y);
			else if(i==3)	printf("%d is %dnd cousin twice removed of %d\n",x,i-1,y);
			else if(i==4)	printf("%d is %drd cousin twice removed of %d\n",x,i-1,y);
			else 	printf("%d is %dth cousin twice removed of %d\n",x,i-1,y);	
		}
		else if(gen == -3){
			if(i==0) printf("%d is Great Grand child of %d\n",x,y);
			else if(i==1)	printf("%d is Great Grand Nephew  of %d\n",x,y);
			else if(i==2)	printf("%d is %dst cousin thrice removed of %d\n",x,i-1,y);
			else if(i==3)	printf("%d is %dnd cousin thrice removed of %d\n",x,i-1,y);
			else if(i==4)	printf("%d is %drd cousin thrice removed of %d\n",x,i-1,y);
			else 	printf("%d is %dth cousin thirce removed of %d\n",x,i-1,y);	
		}
		else if(gen == -4){
			if(i==0) printf("%d is Great Great Grand child of %d\n",x,y);
			else if(i==1)	printf("%d is Great Great Grand Niece of %d \n",x,y);
			else if(i==2)	printf("%d is %dst cousin 4 times removed of %d\n",x,i-1,y);
			else if(i==3)	printf("%d is %dnd cousin 4 times removed of %d\n",x,i-1,y);
			else if(i==4)	printf("%d is %drd cousin 4 times removed of %d\n",x,i-1,y);
			else 	printf("%d is %dth cousin 4 times removed of %d\n",x,i-1,y);	
			}
	
		else if(gen==-5){
			if(i==0) printf("%d is 3rd Great Grand child of %d\n",x,y);
			else if(i==1)	printf("%d is 3rd Great Grand Nephew  of %d\n",x,y);
			else if(i==2)	printf("%d is %dst cousin %d times removed of %d\n",x,i-1,-gen,y);
			else if(i==3)	printf("%d is %dnd cousin %d times removed of %d\n",x,i-1,-gen,y);
			else if(i==4)	printf("%d is %drd cousin %d times removed of %d\n",x,i-1,-gen,y);
			else 	printf("%d is %dth cousin %d times removed of %d\n",x,i-1,-gen,y);	
			}
		else	{
			if(i==0) printf("%d is %dth Great Grand child of %d\n",x,-gen-2,y);
			else if(i==1)	printf("%d is %dth Great Grand Nephew  of %d\n",x,-gen-2,y);
			else if(i==2)	printf("%d is %dst cousin %d times removed of %d\n",x,i-1,-gen,y);
			else if(i==3)	printf("%d is %dnd cousin %d times removed of %d\n",x,i-1,-gen,y);
			else if(i==4)	printf("%d is %drd cousin %d times removed of %d\n",x,i-1,-gen,y);
			else 	printf("%d is %dth cousin %d times removed of %d\n",x,i-1,-gen,y);	
			}
		
		}
	}
}

int main(){
	class FamilyTree ft(100);
	ft.insertChild(100,4);
	ft.relationship(100,4);;
}










