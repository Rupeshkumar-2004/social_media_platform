#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    long long dp[3];
    struct Node *left;
    struct Node *right;
};

struct Queue {
    struct Node **data;
    int front, rear, size, capacity;
};

// Queue helper functions
struct Queue* createQueue(int capacity) {
    struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
    q->capacity =capacity;
    q->front=q->size=0;
    q->rear=capacity-1;
    q->data=(struct Node**)malloc(capacity*sizeof(struct Node*));
    return q;
}

int isEmpty(struct Queue* q) {
    return q->size==0;
}

void enqueue(struct Queue* q,struct Node* data) {
    q->rear=(q->rear + 1)%q->capacity;
    q->data[q->rear]=data;
    q->size++;
}

struct Node* dequeue(struct Queue* q) {
    if (isEmpty(q)) return NULL;
    struct Node* item = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

// Create a new Node
struct Node* createNode() {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->left=node->right=NULL;
    node->dp[0]=0;
    node->dp[1]=0;
    node->dp[2]=0;
    return node;
}

// Tree construction from level order
struct Node* buildTree(int* level_order,int n) {
    if(n==0||level_order[0]==0)
        return NULL;

    struct Node* root=createNode();
    struct Queue* q=createQueue(n);
    enqueue(q,root);

    int i=1;
    while(i<n && !isEmpty(q)) {
        struct Node* current=dequeue(q);

        if (i<n && level_order[i]==1) {
            current->left =createNode();
            enqueue(q,current->left);
        }
        i++;

        if (i<n && level_order[i]==1) {
            current->right =createNode();
            enqueue(q,current->right);
        }
        i++;
    }
    return root;
}

// DFS for Minimum Dominating Set
void PhoneDistance(struct Node* u) {
    if (!u) return;
    PhoneDistance(u->left);
    PhoneDistance(u->right);

    //here i used long long as itoverflowed for larger test cases
    long long MAX_COST = (1LL<<60);

    // values for left child
    long long Left0 = u->left ? u->left->dp[0] : 0;
    long long Left1 = u->left ? u->left->dp[1] : MAX_COST;
    long long Left2 = u->left ? u->left->dp[2] : 0;

    // similarly for right child
    long long Right0 = u->right ? u->right->dp[0] : 0;
    long long Right1 = u->right ? u->right->dp[1] : MAX_COST;
    long long Right2 = u->right ? u->right->dp[2] : 0;

    long long min_Left = Left0;
    // find minimum among Left0, Left1, Left2
    if (Left1 < min_Left) min_Left = Left1;
    if (Left2 < min_Left) min_Left = Left2;

    long long min_Right = Right0;
    // find minimum among Right0, Right1, Right2
    if (Right1 < min_Right) min_Right = Right1;
    if (Right2 < min_Right) min_Right = Right2;

    // Minimum cost across all states for children subtrees
    u->dp[1] = 1 + min_Left + min_Right;

    // find cost when u is covered by left or right child
    long long cost_L_cover = Left1 + min_Right;
    long long cost_R_cover = Right1 + min_Left;

    if (u->left || u->right) {
        u->dp[2] = cost_L_cover < cost_R_cover ? cost_L_cover : cost_R_cover;
    } else {
        u->dp[2] = MAX_COST;
    }

    long long minL = Left1 < Left2 ? Left1 : Left2;
    long long minR = Right1 < Right2 ? Right1 : Right2;
    u->dp[0] = minL + minR;
}

int calculate_min_phones(struct Node* root) {
    if (!root) return 0;
    PhoneDistance(root);
    long long res = root->dp[1] < root->dp[2] ? root->dp[1] : root->dp[2];
    if (res > (long long)INT_MAX) return INT_MAX; // cap to int range
    return (int)res;
}

//FOR TASK 2...
// Sieve of Eratosthenes
void sieve(int* primes, int* prime_count, int m) {
    if (m <= 0) {
        *prime_count = 0;
        return;
    }

    int is_prime[1001];
    for(int i=0;i<=1000;i++) is_prime[i]=1;
    is_prime[0]=is_prime[1]=0;

    for(int p=2;p*p<=1000;p++){
        if(is_prime[p]){
            for(int i=p*p;i<=1000;i+=p)
                is_prime[i]=0;
        }
    }

    *prime_count=0;
    for(int p=2;p<=1000 &&*prime_count<m;p++){
        if(is_prime[p]){
            primes[*prime_count]=p;
            (*prime_count)++;
        }
    }
}

// Count XOR pairs in range
int pairsInRange(int* arr,int sz,int l,int r) {
    if(sz<2) return 0;
    int cnt=0;
    for(int i=0; i<sz;++i){
        for(int j=i+1;j<sz;++j){
            int x=arr[i]^arr[j];
            if (x>=l && x<=r) ++cnt;
        }
    }
    return cnt;
}

int main() {
    int n;
    if(scanf("%d", &n)!=1) return 0;

    int* level_order=(int*)malloc(n * sizeof(int));
    for(int i=0;i<n;++i) {
        if(scanf("%d",&level_order[i])!=1) return 0;
    }

    int l, r;
    if(scanf("%d %d", &l, &r)!=2) return 0;

    struct Node* root=buildTree(level_order,n);
    int m =calculate_min_phones(root);
    printf("%d\n",m);
    if (m==0) {
        printf("0\n");
        return 0;
    }

    // for task 2...
    int primes[1000];
    int prime_count=0;
    sieve(primes,&prime_count,m);
    int total_pairs =prime_count * (prime_count - 1) / 2;
    int count_in_range =pairsInRange(primes,prime_count,l,r);
    int count_outside_range=total_pairs - count_in_range;

    printf("%d\n",count_outside_range);
    return 0;
}
