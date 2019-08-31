package binaryTree;

public class BTree {
	BNode root;
	public BTree() {
		root = null;
	}
	//查找在树中是否有key=x的节点.递归和非递归
	private BNode search(BNode node,int key) {
		if(node == null) {
			return null;
		}
		while(true) {
			if(node.key ==key ) { //找到了
				return node;
			}
			while(node.key < key) {
				if(node.right != null) {
					node = node.right;
				}else {
					return node; //没找到，返回最近的父节点。方便插入的时候直接插入
				}
			}
			while(node.key > key) {
				if(node.left != null) {
					node = node.left;
				}else {
					return node;
				}
			}
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
		BNode node = search(key);
		BNode newNode = new BNode(key);
		if(node.key < key) {
			node.right = newNode;
		}else if(node.key > key) {
			node.left = newNode;
		}
		newNode.parent = node;
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
//	BNode maxKeyNode(BNode node) {
//		while(node!=null && node.right != null) {
//			node = node.right;
//		}
//		return node;
//	}
	//移除以该节点为根节点的最大节点。将该节点返回。
	private BNode removeMax(BNode node) {
		while(node!= null && node.right != null) {
			node = node.right;
		}
		BNode parent = node.parent;
		if(parent.key > node.key) {
			parent.left = null;
		}else {
			parent.right = null;
		}
		return node;
		
	}
	//删除一个节点，
	private void remove(BNode tree, int key) {
		if (tree == null) {
			return;
		}
		BNode node = search(key);
		if (node.key != key) {
			System.out.println("树中不存在该值");
			return;
		}
		BNode parent = node.parent;
		if (node.left != null) { // 左边不为空
			BNode maxKeyNode = removeMax(node.left);
			node.key = maxKeyNode.key;
		} else if (node.right != null) { // 左边为空，右边不为空。直接指向右边就可以。
			if (parent == null) {
				root = node.right;
			} else {
				if (parent.key < node.key) {
					parent.right = node.right;
				} else {
					parent.left = node.right;
				}
			}
			if (node.right != null) {
				node.right.parent = parent;
			}
		}	
	} 
	public void remove(int key) {
		remove(root,key);
	}
}
