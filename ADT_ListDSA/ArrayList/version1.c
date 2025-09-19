#include <stdio.h>
#include <stdbool.h>
#define MAX 10


typedef struct {
    int elem[MAX];
    int count; 
} List;

List L;

List initialize(List L){
    L.count = 0;
    return L;
}

// List insertPos(List L, int data, int position){
//     if (L.count != MAX){ //check if full
//         if(position >= 0 && position <= L.count){ //position is valid
//             if(position != L.count){ 
//                 for(int i = L.count; i > position; i--){
//                         L.elem[i] = L.elem[i - 1];
//                 }
//             }
//             L.elem[position] = data;
//             L.count++;
//         }else{
//             printf("Position is not valids.\n");
//         }
//     } else {
//         printf("List is full\n.");
//     }

//     return L;
// }

List insertPos(List L, int data, int position){
    int i;
    
    if(L.count != MAX && position <= L.count){
    for(i = L.count; i >= position; i--){
        L.elem[i] = L.elem[i-1];
    }
    }
    L.elem[position] = data;
    L.count++;
    return L;
}


List deletePos(List L, int position){
    if (L.count != 0){//CHECK IF ITS EMPTY
        if(position >= 0 && position <= L.count){
            if(position != L.count){ 
                for(int i = position; i < L.count-1; i++){
                        L.elem[i] = L.elem[i + 1];
                }
            }
            L.count--;
        }else{
            printf("Position is not valid.\n");
        }
    return L;
}
}

int locate(List L, int data){
    int i; 

    if (L.count != 0){
        for (i = 0; i < L.count && L.elem[i] != data; i++);
        return (i < L.count) ? i: -1;
    }
    printf("\n");

}

// List insertSorted(List L, int data){
//     List l;

//     if (L.count != MAX){
        
//     }
// }

List insertSorted(List L, int data){
    if(L.count == MAX){
        return L;
    }
    
    int i = L.count - 1;
    while (i >= 0 && data <= L.elem[i]){
        L.elem[i+1] = L.elem[i];
        i--;
    }
    L.elem[i+1] = data;
    L.count++;
    
    return L;
}

void printList(List L) {
    printf("List (count = %d): ", L.count);
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

int main(){
    List L = initialize(L);

    L = insertPos(L, 10, 0);
    printList(L);
    L = insertPos(L, 20, 1);
     printList(L);
    L = insertPos(L, 30, 2);
     printList(L);

    printf("Index of 20: %d\n", locate(L, 20)); // should print 1
    printf("Index of 40: %d\n", locate(L, 30)); // should print -1
    
    printList(L);
    L = deletePos(L, 1);
    printList(L);
    printf("After deleting pos 1, index of 30: %d\n", locate(L, 30)); // should print 1

    return 0;
}