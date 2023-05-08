#ifndef LINKED_LIST_H
#define LINKED_LIST_H
class Node {
    public:
        std::string value;
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
            remove(accessNode(i-1));
        }
        void remove(Node *previousNode){
            if(previousNode->next != NULL){
            Node *nextNode = previousNode->next->next;
            delete previousNode->next;
            previousNode->next = nextNode;
            }
        }
        void insert(Node *previousNode, std::string value){//pointer to the node after which we want to insert
            Node *newNode;
            newNode = new Node;
            newNode->value = value;
            newNode->next = previousNode->next;
            previousNode->next = newNode;
            if(previousNode == last)last = newNode;
        }
        void insert(int i, std::string value){//after which index do you want to insert
            insert(accessNode(i), value);
        }
        Node *accessNode(int i){//returns a pointer to a specific node
            Node *pointer = head;
            while(i--){
                pointer = pointer->next;
            }
            return pointer;
        }
        void append(std::string value){//adding one to the linked list at the end
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

};
#endif //LINKED_LIST_H