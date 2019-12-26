#include <stdlib.h>
#include <stdio.h>

//data elements
typedef struct _LinkedList{
	struct _LinkedList* next;
	int element;
}Node;

typedef struct _HeadPtr{
	struct _LinkedList* first;
	
	//method pointers
	void (*add) (struct _HeadPtr*,int);
	int (*delete) (struct _HeadPtr*,int);
	int (*get) (struct _HeadPtr*,int);
	void (*addAfter) (struct _HeadPtr*,int,int);
}List;

//methods
void regularAdd(List* this,int newElement){
	Node* current=this->first;
	while (current->next!=0){
		current=current->next;
	}
	current->next=(Node*) malloc(sizeof(Node));
	current->next->element=newElement;
}

int regularGet(List* this,int index){
	Node* current=this->first;
	for (;index>0;index--){
		current=current->next;
	}
	return current->element;
}

int regularDelete(List* this,int index){
	Node* current=this->first;
	Node* prev;
	if (index==0){
		int returnInt=current->element;
		Node* next=current->next;
		free(current);
		this->first=next;
		return returnInt;
	}
	for (;index>0;index--){
		if (index==1) {prev=current;}
		current=current->next;
	}
	int returnInt=current->element;
	Node* next=current->next;
	free(current);
	prev->next=next;
	return returnInt;
}

void regularAddAfter(List* this,int index,int newElement){
	Node* current=this->first;
	for (;index>0;index--){
		current=current->next;
	}
	Node* previousNext=current->next;
	current->next=(Node*) malloc(sizeof(Node));
	current->next->element=newElement;
	current->next->next=previousNext;
}

//RegularList constructor
List* new_RegularList(int firstElement){
	List* newList=(List*) malloc(sizeof (List));
	newList->first=(Node*) malloc(sizeof (Node));
	newList->first->element=firstElement;
	newList->add=regularAdd;
	newList->get=regularGet;
	newList->delete=regularDelete;
	newList->addAfter=regularAddAfter;
	
	return newList;
}

int main(){
	List* testList=new_RegularList(4);
	(*testList).add(testList,5);
	(*testList).add(testList,6);
	(*testList).add(testList,7);
	printf("%d\n",(*testList).delete(testList,1));
	(*testList).addAfter(testList,0,8);
	printf("%d\n",(*testList).delete(testList,0));
	printf("%d  %d  %d\n",(*testList).get(testList,0),(*testList).get(testList,1),(*testList).get(testList,2));
	return 0;
}





















