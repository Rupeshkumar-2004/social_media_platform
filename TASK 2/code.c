#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//definition of tree node
typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

//queue for level order construction
typedef struct {
    Node *arr[10000];
    int front, rear;
} Queue;

//queue operations
void push(Queue *q, Node *n){ 
    q->arr[q->rear++] = n;
}

Node *pop(Queue *q){ 
    return q->arr[q->front++]; 
}

bool empty(Queue *q){ 
    return q->front == q->rear; 
}

//create new tree node
Node *newNode(int val) {
    if(val==0) return NULL;
    Node *node =(Node *)malloc(sizeof(Node));
    node->val =val;
    node->left =node->right=NULL;
    return node;
}

//build tree from level order array
Node *buildTree(int *level,int n) {
    if(n==0||level[0]==0) return NULL;

    Node *root =newNode(1);
    Queue q = {0};
    push(&q,root);

    int i=1;
    while(!empty(&q) && i<n) {
        Node *curr =pop(&q);
        if(curr){
            if(i<n){
                curr->left = newNode(level[i]);
                push(&q,curr->left);
                i++;
            }
            if(i<n){
                curr->right =newNode(level[i]);
                push(&q,curr->right);
                i++;
            }
        }
    }
    return root;
}

//global variable to count phones
int phones = 0;

//dfs to determine minimum phones needed
int dfs(Node *root) {
    if(!root) return 2;
    int Left=dfs(root->left);
    int Right=dfs(root->right);

    if(Left==0||Right==0) {
        phones++;
        return 1;
    }
    if(Left==1||Right==1) return 2;
    return 0;
}

//function to get minimum phones
int minPhones(Node *root) {
    phones=0;
    if(dfs(root)==0) phones++;
    return phones;
}

//function to generate first m primes using Sieve of Eratosthenes
void generatePrimes(int m,int *primes) {
    int limit=2000000;
    char *isPrime=(char *)malloc(limit + 1);
    for(int i=2;i<=limit;i++){
        isPrime[i]=1;
    }

    for (int i=2;i*i<=limit;i++){
        if (isPrime[i]) {
            for (int j=i*i;j<=limit;j+=i){
                isPrime[j]=0;
            }
        }
    }

    int count=0;
    for (int i=2;i<=limit && count<m;i++) {
        if (isPrime[i]) primes[count++]=i;
    }
}

//function to count pairs with XOR outside [l, r]
long long countOutsideRange(int *primes, int m, int l, int r) {
    long long total = 0;
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            int val=primes[i]^primes[j];
            if(val<l||val>r)
                total++;
        }
    }
    return total;
}

int main() {
    //task 1..
    int n;
    scanf("%d", &n);
    int *level=(int *)malloc(n * sizeof(int));
    for (int i=0;i<n;i++){
        scanf("%d", &level[i]);
    }
    Node *root=buildTree(level, n);
    int m=minPhones(root);
    printf("%d\n", m);

    //task 2..
    int l, r;
    scanf("%d %d", &l, &r);
    int *primes = (int *)malloc(m * sizeof(int));
    generatePrimes(m, primes);
    long long outside = countOutsideRange(primes, m, l, r);
    printf("%lld\n", outside);
    return 0;
}