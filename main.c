#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

typedef struct node{
	int delay;
	float charge;
	struct node* next;
}Node;
#define MAX_RAND 21
float getR();
Node* pushNode(Node* head,int delivered,float charge);
void clearList(Node* head);
void processList(Node *head);

float getR(){
	return(rand() % MAX_RAND)/100.0;
}
Node* pushNode(Node* head,int delivered,float charge){
	Node* tmp;
	tmp=head;
	Node* newnode;
	newnode=(Node*)malloc(sizeof(Node));
	newnode->delay=delivered;
	newnode->charge=charge;
	newnode->next=NULL;
	if(tmp==NULL)
		return newnode;
	while(tmp->next!=NULL)
	{
		tmp=tmp->next;
	}
	tmp->next=newnode;
	return head;
}
void clearList(Node* head ){
	Node* tmp;
	tmp=head;
	while(head!=NULL)
	{
		head=head->next;
		free(tmp);
		tmp=head;
	}
}
void processList(Node *head){
	Node* tmp;
	tmp=head;
	float totalTip=0;
	int maxDelay=0;
	int orders=0;
	float tip=0;
	while(tmp!=NULL)
	{
		tip = tmp->charge * getR() /100;
		totalTip+=tip;
		maxDelay+=tmp->delay;
		orders++;
		printf("# %d | $%f (+ %f) Delay: %d\n",orders,tmp->charge,tip,tmp->delay);
		tmp=tmp->next;
	}
	printf("------------------------------\n");
	printf("Total orders:%d\n",orders);
	printf("Maximum Delay:%d\n",maxDelay);
	printf("Total Tips:%f\n",totalTip);
}
int main(){
	int delay;
	int tip;
	float charge;
	Node* head=NULL;
	while(1){
		printf("insert delivery delay(second)[-1 to exit]:");
		scanf("%d",&delay);
		printf("insert delivery charge:");
		scanf("%f",&charge);
		if(delay==-1 && charge==-1)
		{
			processList(head);
			clearList(head);
			system("PAUSE");
			exit(0);
		}
		head=pushNode(head,delay,charge);
	}
}