#include <iostream>
using namespace std;

int size=0;

struct Queue{
    Queue* head;
    Queue* tail;
    Queue* next;
    int number;

    void enqueue(int num){
        Queue* new_el = new Queue;
        new_el->next = new_el->tail;
        tail = new_el;

        new_el->number = num;
        ++size;
    }
    void dequeue(){
        free()
            
    }
};

int main(){

}