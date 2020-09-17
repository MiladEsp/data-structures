#include "BinaryTree.h"

int main()
{
    BinaryTree<int> five_tree({1,2,3,4,5});

    
    five_tree.traverseTree("preOrder");
    std::cout << std::endl << std::endl;

    five_tree.traverseTree("inOrder");
    std::cout << std::endl << std::endl;

    five_tree.traverseTree("postOrder");
    std::cout << std::endl << std::endl;
    
    return 0;
}