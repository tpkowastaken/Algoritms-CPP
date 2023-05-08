#ifndef LINKED_LIST_H
#define LINKED_LIST_H
class Node {
    public:
        int value;
        Node *next;
};
class linked_list {//Singly linked list
    private:
        Node *head = NULL;
        Node *last = NULL;
        int l = 0; //length of the list
    public:
        ~linked_list(){
            Node *pointer = head;
            Node *tmp;
            while(pointer != NULL){
                tmp = pointer->next;
                delete pointer;
                pointer = tmp;
            }

        }
        void remove(int i){
            if(!i && head != NULL){
                if(last == head)last = head->next;
                Node *nextNode = head->next;
                delete head;
                head = nextNode;
            }
            else remove(accessNode(i-1));
        }
        bool isEmpty(){
            if(head==NULL)return true;
            else return false;
        }
        void remove(Node *previousNode){
            if(previousNode->next != NULL){
                if(last == previousNode->next)previousNode->next->next = NULL;
                Node *nextNode = previousNode->next->next;
                delete previousNode->next;
                previousNode->next = nextNode;
            }
        }
        void insert(Node *previousNode, int value){//pointer to the node after which we want to insert
            Node *newNode;
            newNode = new Node;
            newNode->value = value;
            newNode->next = previousNode->next;
            previousNode->next = newNode;
            if(previousNode == last)last = newNode;
        }
        void insert(int i, int value){//after which index do you want to insert
            insert(accessNode(i), value);
        }
        Node *accessNode(int i){//returns a pointer to a specific node
            Node *pointer = head;
            while(i--){
                pointer = pointer->next;
            }
            return pointer;
        }
        void append(int value){//adding one to the linked list at the end
            Node *newitem;
            newitem = new Node();
            newitem->value = value;
            newitem->next = NULL;
            if(last == NULL){
                last = newitem;
                head = newitem;
            }
            else{
                last->next = newitem;
                last = newitem;
            }
        }
        void print(){
            Node *pointer = head;
            while(pointer != NULL){
                std::cout << pointer->value << " ";
                pointer = pointer->next;
            }
        }
        int searchfor(int value){
            int i = 0;
            Node *pointer = head;
            while(pointer != NULL){
                if(pointer->value == value)return i;
                pointer = pointer->next;
                i++;
            }
            return -1;
        }

};
#endif //LINKED_LIST_H