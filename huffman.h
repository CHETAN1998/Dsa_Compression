#define MAX 256
typedef struct node {
    char data;
    unsigned freq;
    struct node *l, *r;
}node;
typedef struct heap {
    unsigned size;
    unsigned capacity;
    node **arr;
}heap;



