package binaryTree;

import javax.xml.transform.Templates;

public class BTree {
	BNode root;
	public BNode getRoot;
	public BTree() {
		root = null;
	}
	//查找在树中是否有key=x的节点
	private BNode search(BNode node,int key) {
		if(node == null) {
			return null;
		}
		if(node.key == key) {
			return node;
		}else if(node.key > key) {
			return search( node.left,key);
		}else {
			return search(node.right,key);
		}
	}
	public BNode search(int key) {
		return search(root,key);
	}
	//插入一个值
	private void insert(BNode tree,int key) {
		if(tree.key == key ) {
			return;
		}
		//递归实现，3w左右栈溢出。
		if(tree.key > key) {
			if(tree.left == null) {
				tree.left = new BNode(key);
			}else {
				insert(tree.left,key);
			}
		}else {
			if(tree.right == null) {
				tree.right = new BNode(key);
			}else {
				insert(tree.right,key);
			}
		}
	}
	public void insert(int key) {
		if(root == null) {
			root = new BNode(key);
		}else {
			insert(root,key);
		}
	}
	//以前序遍历打印
	void print(BNode tree) {
		if(tree != null) {
			System.out.print(tree.key + " ");
			print(tree.left);
			print(tree.right);
		}
	}
	public void print() {
		if(root != null) {
			print(root);
		}
	}
	//寻找以该节点为父节点最大的值。
	BNode maxKeyNode(BNode node) {
		if(node.right != null) {
			return maxKeyNode(node.right);
		}else {
			return node;
		}
	}
	private BNode removeMax(BNode node) {
		if(node.right == null) {
			BNode rBNode = node.left;
			node.left = null;
			return rBNode;
		}else {
			node.right = removeMax(node.right);
			return node;
		}
	}
	//删除一个节点，
	private BNode remove(BNode tree,int key) {
		if(tree ==  null) {
			return null;
		}
		if(key < tree.key) {
			tree.left = remove(tree.left, key);
			return tree;
		}else if(key > tree.key) {
			tree.right = remove(tree.right, key);
			return tree;
		}else {
			if(tree.left == null) {
				BNode rBNode = tree.right;
				tree.right = null;
				return rBNode;
			}else if(tree.right == null) {
				BNode lBNode = tree.left;
				tree.left = null;
				return lBNode;
			}else {
				BNode maxNode = removeMax(tree.left);
				tree.key = maxNode.key;
				return tree;
			}
		}
	}
	public void remove(int key) {
		root = remove(root,key);
	}
}
