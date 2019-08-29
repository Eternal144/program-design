package AVLTree;

public class AVLNode {
	int key;
	int height;
//	AVLNode parent;
	AVLNode left;
	AVLNode right;
	public AVLNode(int key, AVLNode left,AVLNode right) {
		this.key = key;
		this.left = left;
		this.right = right;
		this.height = 0;
	}
}
