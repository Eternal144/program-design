package binaryTree;

public class BNode {
	int key;
	BNode parent;
	BNode left;
	BNode right;
	BNode(int key) {
		this.key = key;
		this.parent = null;
		this.right = null;
		this.left = null;
	}
}
