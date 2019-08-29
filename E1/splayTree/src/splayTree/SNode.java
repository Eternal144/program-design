package splayTree;


public class SNode {
	int key;
	SNode left;
	SNode right;
	SNode parent;
	public SNode(int key, SNode left, SNode right) {
		this.key = key;
		this.left = left;
		this.right = right;
		this.parent = null;
	}
	public SNode(int key) {
		this.key = key;
		this.left = null;
		this.right = null;
		this.parent = null;
	}
}
