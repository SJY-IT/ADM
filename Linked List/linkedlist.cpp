#include <iostream>
using namespace std;

struct list {
    int item;
    list *next;
};

list* searchList(list *l, int x) {
    if(l == NULL) return NULL;

    if(l->item == x) 
        return l;  
    else 
        return searchList(l->next, x);
}
void insertList(list **l, int x) {
    list *temp = new list;
    temp->item = x;
    temp->next = *l;
    *l = temp;
}
list *predecessorList(list *l, int x) {
    if((l == NULL) || (l->next == NULL))
        //No predecessor
        return NULL;

    if(l->next->item == x) 
        return l;
    else
        return predecessorList(l->next, x);    
}
void deleteList(list **l, int x) {
    list *temp;
    list *pred;
    
    temp = searchList(*l, x);
    if (temp != NULL) {
        pred = predecessorList(*l, x);
        if(pred = NULL)
            *l = temp->next;
        else
            pred->next = temp->next;
        
        delete (temp);
    }
}
int main() {
    

return 0;
}