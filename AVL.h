class AVLTree {
    struct Node {
        int id,reward_score,count;

        int height;
        Node* left;
        Node* right;

        Node(int score, int id ) : reward_score(score), id(id), count(1), height(1), left(nullptr), right(nullptr) {}
    };

public:
    Node* root;

    AVLTree() :root(nullptr) {}

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateLeft(Node* node) {
        Node* newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;
        updateHeight(node);
        updateHeight(newParent);
        return newParent;
    }

    Node* rotateRight(Node* node) {
        Node* newParent = node->left;
        node->left = newParent->right;
        newParent->right = node;
        updateHeight(node);
        updateHeight(newParent);
        return newParent;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        else if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }
    void insert(int id, int reward_score) {
        
        if (root == nullptr) {
            root = insert(root,100, reward_score);
            return;
        }
        root = insert(root, id, reward_score);
    }
    Node* insert(Node*& node, int id, int reward_score) {
       // cout << id << " ";
        if (node == nullptr) {
            return new Node(reward_score,id);
        }
        if (id < node->id) {
            node->left = insert(node->left, id, reward_score);
        }
        else if (id > node->id) {
            node->right = insert(node->right, id, reward_score);
        }
        else {
            node->count++;
            return node;
        }
        return balance(node);
    }
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    int calculateScore(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left_score = calculateScore(node->left);
        int right_score = calculateScore(node->right);
        int node_score = node->reward_score * node->count;
        return left_score + right_score + node_score;
    }
};