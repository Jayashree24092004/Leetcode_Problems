struct Info {
    int sum;
    int count;
};

int ans = 0;

struct Info dfs(struct TreeNode* root) {
    if (root == NULL) {
        return (struct Info){0, 0};
    }

    struct Info left = dfs(root->left);
    struct Info right = dfs(root->right);

    int sum = root->val + left.sum + right.sum;
    int count = 1 + left.count + right.count;

    if (root->val == sum / count) {
        ans++;
    }

    return (struct Info){sum, count};
}

int averageOfSubtree(struct TreeNode* root) {
    ans = 0;
    dfs(root);
    return ans;
}