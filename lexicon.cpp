#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

struct BSTnode {
    char word[128];
    char meaning[256];
    char antonym[256];
    char synonym[256];
    struct BSTnode *left, *right;
};

struct BSTnode *root = NULL;

struct BSTnode * createNode(char *word, char *meaning, char *synonym, char *antonym) 
{
    struct BSTnode *newnode;
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);
    strcpy(newnode->meaning, meaning);
    strcpy(newnode->synonym, synonym);
    strcpy(newnode->antonym, antonym);
    newnode->left = newnode->right = NULL;
    return newnode;
}
void insert(char *word, char *meaning, char *synonym, char *antonym) 
{
    struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
    int res = 0;
    if (root==NULL) {
        root = createNode(word, meaning , synonym , antonym);
        return;
    }
    current=root;
    while(current!=NULL){
        res = strcasecmp(word, current->word);
        if (res == 0) {
          //------------------------------------------------------------------
            //The Dictionary contains a word, its meaning, its synonyms, antonyms…It cannot contain any duplicate words"
            cout<<"You have entered the same word again! It’s a  duplicate entry.";
            cout<<"\nPlease enter the new word for the dictionary"<<endl;
            return;
        }
        parent = current;
        if(res > 0){
            current= current->right;
        }

        else{
        current=current->left;
        }

    } //while loop ends here
    newnode = createNode(word, meaning, synonym, antonym);
    res > 0 ? (parent->right = newnode) : (parent->left = newnode);
    return;
} //function ends here

void inorderTraversal(struct BSTnode *myNode) 
{
    if (myNode!=NULL) 
    {
        inorderTraversal(myNode->left);

        cout<<"Word is "<<myNode->word<<endl;
        cout<<"Meaning: "<<myNode->meaning<<endl;
        cout<<"Synonym: "<<myNode->synonym<<endl;
        cout<<"Antonym: "<<myNode->antonym<<endl;
            
        inorderTraversal(myNode->right);
    }
    return;
}

struct node* search( char *str)
{
    struct BSTnode *temp =NULL;
    int flag =0, res=0;
    if(root ==NULL){
        cout<<"Lexicon is empty";
    }
    temp = root;
    while(temp){
        if((res = strcasecmp(temp->word,str))==0){
            cout<<"word:"<<str<<endl;
            cout<<"Meaning:"<<temp->meaning<<endl;
            cout<<"Synonym:"<<temp->synonym<<endl;
            cout<<"Antonym:"<<temp->antonym<<endl;
            flag = 1;
            break;
        }
        temp = (res>0) ? temp ->left : temp ->right;
    }
    if(flag == 0){
        cout<<"word not found"<<endl;
    }
    return 0;
}

unsigned int TotalWords(struct BSTnode *root)
{
    //no word node present
    if(root==NULL){
        return 0;
    }
    unsigned int count = 1; //one for root node 
    if(root->left != NULL){
        count += TotalWords(root->left);
    }
    if(root->right != NULL){
    count += TotalWords(root->right);
    }
    return count;
}


void deleteNode(char *str) {
        struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
        int flag = 0, res = 0;
        if (!root) {
                cout<<"Dictionary is empty!!"<<endl;
                return;
        }
        current = root;
        while (1) {
                res = strcasecmp(current->word, str);
                if (res == 0)
                        break;
                flag = res;
                parent = current;
                current = (res > 0) ? current->left : current->right;
                if (current == NULL){
                    cout<<"Word not found."<<endl;
                    return;
                }
        }
        /* deleting leaf node */
        if (current->right == NULL) {
                if (current == root && current->left == NULL) {
                        free(current);
                        root = NULL;
                        return;
                } else if (current == root) {
                        root = current->left;
                        free (current);
                        return;
                }

                flag > 0 ? (parent->left = current->left) :
                                (parent->right = current->left);
        } else {
                /* delete node with single child */
                temp = current->right;
                if (!temp->left) {
                        temp->left = current->left;
                        if (current == root) {
                                root = temp;
                                free(current);
                                return;
                        }
                        flag > 0 ? (parent->left = temp) :
                                        (parent->right = temp);
                } else {
                        /* delete node with two children */
                        struct BSTnode *successor = NULL;
                        while (1) {
                                successor = temp->left;
                                if (!successor->left)
                                        break;
                                temp = successor;
                        }
                        temp->left = successor->right;
                        successor->left = current->left;
                        successor->right = current->right;
                        if (current == root) {
                                root = successor;
                                free(current);
                                return;
                        }
                        (flag > 0) ? (parent->left = successor) :
                                        (parent->right = successor);
                }
        }
        free (current);
        return;
  }

void editWord(char * str)
{
    struct BSTnode *temp =NULL;
    int flag =0, res=0;
    if(root ==NULL){
        cout<<"Lexicon is empty";
        return;
    }
    temp = root;
    while(temp)
    {
        if((res = strcasecmp(temp->word,str))==0)
        {
            char nMeaning[256];
            char nAntonym[256];
            char nSynonym[256];
            cout<<"what do you want to edit"<<endl;
            cout<<"1. Meaning"<<endl;
            cout<<"2. Synonym"<<endl;
            cout<<"3. Antonym"<<endl;
            cout<<"4. Exit"<<endl;

            int ch;
            cin>>ch;

            switch(ch)
            {
                char b[10];
                char c[10];
                char a[10];
                case 1:
                    cout<<"Enter new meaning: ";
                    cin.getline(a,10);
                    cin.getline(nMeaning,256);
                    strcpy(temp->meaning,nMeaning);
                    break;

                case 2:
                    cout<<"Enter new synonym: ";
                    cin.getline(b,10);
                    cin.getline(nSynonym,256);
                   strcpy(temp->synonym,nSynonym);
                    break;

                case 3:
                    cout<<"Enter new antonym: ";
                    cin.getline(a,10);
                    cin.getline(nAntonym,256);
                    strcpy(temp->antonym,nAntonym);
                    break;

                case 4:
                
                break;

            }
            cout<<"Edited word is ->"<<endl;
            cout<<" Word: "<<str<<endl;
            cout<<" Meaning: "<<temp->meaning<<endl;
            cout<<" Synonym: "<<temp->synonym<<endl;
            cout<<" Antonym: "<<temp->antonym<<endl;
            flag=1;
            break;
        }
        temp = (res>0) ? temp ->left : temp ->right;
    }
    if(flag == 0){
        cout<<" word not found"<<endl;
    }
    return;
}

    
int main () 
{
    char word[256];
    char meaning[256];
    char antonym[256];
    char synonym[256]; 
    char a[128];
    char b[10];

    bool cond=true;

    cout<<"\n\n\n\n";
    cout<<"\t            WELCOME TO THE ENGLISH LEXICON "<<endl;
    cout<<"\n";
    cout<<"\t   It will read list of words and their definitions."<<endl;
    cout<<"\t  User can look for their meaning and their synonyms."<<endl;
    cout<<"\t Insertion of new words, searching, finding total number"<<endl;
    cout<<"\t     of words, deletion etc. can also be performed ."<<endl;
    cout<<"\n\n\n\n\n\n\n";

    while (cond)
    {
        cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
        cout<<"                 : MAIN MENU :"<<endl<<endl;
        cout<<"Enter the number of operation to be performed : "<<endl;
        cout<<"1.Insertion"<<endl;
        cout<<"2.Traversal"<<endl;
        cout<<"3.Search"<<endl;
        cout<<"4.Total words"<<endl;
        cout<<"5.Deletion"<<endl;
        cout<<"6.Updation"<<endl;
        cout<<"7.Exit"<<endl<<endl;
        cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
        
        int ch;
        cin>>ch;
        switch (ch)
        {
            case 1:
                cout<<" Word to insert: ";
                cin.getline(b,10);
                cin.getline(word,256);
                cout<<" Meaning: ";
                cin.getline(meaning,256);
                cout<<" Synonym: ";
                cin.getline(synonym,256);
                cout<<" Antonym: ";
                cin.getline(antonym,256);
                insert(word,meaning,synonym,antonym);
                cout<<"\n\n\n";
                break;
                                        
            case 2:
                if(root==NULL){
                    cout<<"No words present in the dictionary."<<endl;
                    cout<<"If you'd like to insert some words, press 1."<<endl;
                    break;
                }
                inorderTraversal(root);
                cout<<"\n\n\n";
                break;

            case 3:
                if(root==NULL){
                    cout<<"No words present to search from."<<endl;
                    break;
                }
                cout<<"Word to Search : "<<endl;
                cin.getline(b,10);
                cin.getline(a,128);
                cout<<search(a);
                cout<<"\n\n\n";
                break;
                
            case 4:
                cout<<"Number of words present at the moment are : "<<TotalWords(root)<<endl;
                cout<<"\n\n\n";
                break;

            case 5:
                cout<<"Enter the word to be deleted from the dictionary : ";
                cin.getline(b,10);
                cin.getline(a,256);
                deleteNode(word);
                //cout<<"Requested word has been deleted."<<endl;
                cout<<"\n\n\n";
                break;

            case 6:
                cout<<"enter the word you need to edit: ";
                cin.getline(b,10);
                cin.getline(word,128);
                editWord(word);
                cout<<"\n\n\n";
                break;

            case 7:
                cond=false;
                break;

            default : //re-running the loop
                cout<<"Invalid option chosen."<<endl;
                cout<<"Enter again."<<endl;
        }
    }
    return 0;
}