#include "queue.h"


int main(){
    Queue q;
    init(&q, 5);
    int i;
    char* words [10]= {"1" ,"2" , "3", "4", "5", "6", "7", "8", "9", "10"};
    for (i = 0; i < 7; i++){
        printf("inserting \'%s\' ....", words[i]);
        if(push(&q, words[i])){
            printf("OK!\n");
        }
    }
    printf("size = %d\n", q.size);
    print_element_queue(&q);
    printf("\n\n");
    //printf("%s", q.list[q.index_get]);
    while(!is_empty(&q)){
        char* element;
        asprintf(&element, "%s", q.list[q.index_get]);
        pop(&q);
        printf("element = %s\n", element);
        free(element);
    }
    
    de_init(&q);
    
    return 0;
}