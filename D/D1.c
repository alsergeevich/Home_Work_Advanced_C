void btUpView(tree *root) {
    if (root == NULL) return;

    
    int topView[2000] = {0}; 
    int visited[2000] = {0};

    
    typedef struct QueueItem {
        tree *node;
        int hd; 
    } QueueItem;

    QueueItem queue[1000]; 
    int front = 0, rear = 0;

    
    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;

    
    while (front < rear) {
        
        tree *current = queue[front].node;
        int hd = queue[front].hd;
        front++;

        
        if (!visited[hd + 1000]) {
            topView[hd + 1000] = current->key;
            visited[hd + 1000] = 1;
        }

        
        if (current->left != NULL) {
            queue[rear].node = current->left;
            queue[rear].hd = hd - 1;
            rear++;
        }

        
        if (current->right != NULL) {
            queue[rear].node = current->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }

    
    int printed = 0; 
    for (int i = 0; i < 2000; i++) {
        if (visited[i]) {
            if (printed) printf(" ");
            printf("%d", topView[i]);
            printed = 1;
        }
    }
    printf("\n");
}