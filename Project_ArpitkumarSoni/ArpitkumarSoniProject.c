#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//NODE
struct node{
	char fname[100]; //firtName
	char lname[100]; //lastName
	char phone[15];  //phoneNumber
	char group[100]; //Group
	struct node * next;  //nextIndex
};
//DECLARATIONS
void printList();
void addContact();
void readFromFile();
void retrieveContact();
void deleteContact();
void writeToTheFile();
struct node *head=NULL;

struct node* getNode();

int main(){
	int back=1;  //for while loop
	int action = 0; //for action, use chose
	printf("WELCOME TO PHONEBOOK APP\n");
	printf("List: \n");
	readFromFile(); //will read contacts from the file and print it
	while(back){
	printf("\nActions:\n");
	printf("ADD:      Press 1\n");
	printf("Retrieve: Press 2\n");
	printf("Delete:   Press 3\n");
	printf("Load:     Press 4\n");
	printf("Save:     Press 5\n");
	printf("Enter the Action: ");
	scanf("%d",&action);getchar();  //taking action from user
		if(action == 1 ){
		 addContact();  //if 1, addContact
		}
		else if(action == 2 ){
		retrieveContact();  //if 2 retrieve Contact and so on....
		}
		else if(action == 3 ){
		deleteContact();
		}
		else if(action == 4 ){
		readFromFile();
		}
		else if(action == 5 ){
		writeToTheFile();
		}
		else{
		printf("Wrong Input!!!");  //wrong Input 
		}
	}
}

struct node* getNode() {  //kind of getter
    struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	return newNode;
}

void addContact(){  	
	//will take contact info from user
	char first[100];
	char last[100];
	char num[15];
	char grp[100];
	printf("\nEnter First Name: \n");
	gets(first);
	printf("\nEnter Last Name: \n");
	gets(last);
	printf("\nEnter Phone Number: \n");
	gets(num);
	printf("\nEnter Group: \n");
	gets(grp);
   //creating new node and sets the value as per user inputs
	struct node* newNode = getNode();
	strcpy(newNode->fname, first);
	strcpy(newNode->lname, last);
	strcpy(newNode->phone, num);
	strcpy(newNode->group, grp);
	if(head == NULL) {
        head = newNode;
	} else {
        struct node *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
		}
		temp->next = newNode;
	}
}

void readFromFile() {
	//will read the content from the file
    head = NULL;
    FILE *fp;
	fp = fopen("Contacts.txt","a+"); //file name and permissions
	char first[100];
    char last[100];
    char num[15];
    char grp[100];
	while(fscanf(fp, "%s", first) != EOF) { //reading and assigning the values
        fscanf(fp, "%s", last);
        fscanf(fp, "%s", num);
        fscanf(fp, "%s", grp);
        printf("\nName: %s, %s || Phone Number: %s || Group: %s ",first, last, num , grp);
        struct node* newNode = getNode();
		//will add this contact to the LinkedList....
        strcpy(newNode->fname, first);
        strcpy(newNode->lname, last);
        strcpy(newNode->phone, num);
        strcpy(newNode->group, grp);

        if(head == NULL) {
            head = newNode;
        } else {
            struct node *temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
        }
	}
	fclose(fp); //closing the file
}

void deleteContact(){
	//delete the contact with the first name
char first[100];
	printf("\nEnter First Name You Want To Delete: \n");
	gets(first);
	int match;  //for comparing the strings
    if(head == NULL){
        printf("\nThe List is Empty!\n");
	} else {
        struct node *temp = head, *prev = NULL;
        if(strcmp(head->fname, first) == 0) { //if it matches then...
            head = head->next;
            return;
        }
        while(temp != NULL){
			match = strcmp(temp->fname,first);
			if(match == 0) {
                prev->next = temp->next; //removing the current contact
                free(temp);
				printf("\nContact Deleted!!!");
			}
			prev = temp;
			temp = temp->next;
		}
			
	}
}

void retrieveContact(){
	//this method will display the contact withing the linkedlist
	//will ask for firstName
	char first[100];
	printf("\nEnter First Name You Want to See: \n");
	gets(first);
	int match;
	if(head==NULL){
        printf("\nThe List is Empty!\n");
	} else {
        struct node *temp=head;
        while(temp != NULL){
            match =	strcmp(temp->fname,first);
            if(match==0) {
printf("Name: %s, %s || Phone Number: %s || Group: %s \n",temp->fname, temp->lname, temp->phone, temp->group);
            }
                temp=temp->next;
            }
	}
}

void writeToTheFile(){
	//when user press the save button then this method will overWrite the file
	//and write all of the contacts from the linked list.
	FILE *fp;
	fp = fopen("Contacts.txt","w");
	struct node *temp=head;
	while(temp != NULL) {
        fprintf(fp,"%s\n%s\n%s\n%s\n",temp->fname,temp->lname,temp->phone,temp->group);
        temp=temp->next;
    }
	fclose(fp);
	printf("\nThe Information is Saved!!!");
}

void printList(){
	//this function will go through the list and print the data...
	if(head == NULL){
	printf("\nThe List is Empty!\n");
	}
	else{
	struct node *temp=head;
	while(temp != NULL) {
		printf("\nName: %s, %s || Phone Number: %s || Group: %s ",temp->fname, temp->lname, temp->phone, temp->group);
			temp=temp->next;
		}
	}
}
