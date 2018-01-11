/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. 
Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/
    int minValue( Node* node ) {
        if ( !node->left && !node->right )
            return node->data;
        int l = minValue( node->left );
        int r = minValue( node->right );
        return l < r ? l : r;
        }

    int maxValue( Node* node ) {
        if ( !node->left && !node->right )
            return node->data;
        int l = maxValue( node->left );
        int r = maxValue( node->right );
        return l > r ? l : r;
        }

    bool checkBST( Node* root ) {
        if ( !root || !root->left || !root->right )
            return true;
        return 
            root->data > maxValue( root->left ) &&
            root->data < minValue( root->right ) &&
            checkBST( root->left ) &&
            checkBST( root->right );
        }
