tree *findBrother(tree *root, int key) {
    if (root == NULL) return 0; // Если дерево пустое, возвращаем 0

    tree *current = root;

    // Поиск узла с заданным ключом
    while (current != NULL) {
        if (current->key == key) {
            // Если найден узел, проверяем, есть ли у него родитель
            if (current->parent == NULL) {
                return 0; // Корень дерева не имеет брата
            }

            // Определяем, является ли текущий узел левым или правым потомком
            if (current->parent->left == current) {
                return current->parent->right; // Возвращаем правого брата
            } else {
                return current->parent->left; // Возвращаем левого брата
            }
        } else if (key < current->key) {
            // Идём в левое поддерево
            if (current->left == NULL) {
                return 0; // Ключ не найден
            }
            current = current->left;
        } else {
            // Идём в правое поддерево
            if (current->right == NULL) {
                return 0; // Ключ не найден
            }
            current = current->right;
        }
    }

    // Если ключ не найден, возвращаем 0
    return 0;
}