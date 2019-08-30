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
		if(node.key < key) {
			node.right = new BNode(key);
		}else if(node.key > key) {
			node.left = new BNode(key);
		}
		
		//递归实现，3w左右栈溢出。
//		if(tree.key > key) {
//			if(tree.left == null) {
//				tree.left = new BNode(key);
//			}else {
//				insert(tree.left,key);
//			}
//		}else {
//			if(tree.right == null) {
//				tree.right = new BNode(key);
//			}else {
//				insert(tree.right,key);
//			}
//		}
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
		while(node!=null && node.right != null) {
			node = node.right;
		}
		return node;
	}
	//移除以该节点为根节点的最大节点。
	private void removeMax(BNode node) {
		while(node!= null && node.right != null) {
			node = node.right;
		}
		node.parent = null;
	}
	//删除一个节点，
	private void remove(BNode tree,int key) {
		if(tree ==  null) {
			return;
		}
		while( key < tree.key ) { //如果不相等，一定是要删的。
			if(tree.left != null) {
				tree = tree.left;
			}else {
				System.out.println("该点不存在"); //比你小，你左边还没点了。
			}
		}
		while(key > tree.key ) {
			if(tree.right != null) {
				tree = tree.right;
			}else {
				System.out.println("该点不存在。"); //比你大，你右边还没点了
			}
		}
		if( key == tree.key) { //就是要删了你。
			BNode parent = tree.parent; 
			int maxKey =  maxKeyNode(tree).key;
			if(parent == null) { //删除根节点。
				if(tree.left != null) {
//					root = maxKeyNode(tree);
					removeMax(tree); //在原处移除。
					root.key = maxKey;
				}else {
					root = tree.right; //右边还有，左边没有，直接左边为根节点。
				}
				return;
			}
			//后面都是非根节点情况。
			if( tree.left != null) { //左边不为空
				removeMax(tree); //将树最左边的移除掉。
				if(key < parent.key) { 
					parent.left.key = maxKey;
				}else {
					parent.right.key = maxKey;
				}
			}else if(tree.right != null) { //左边为空，右边不为空。直接指向右边就可以。
				if(key < parent.key) {
					parent.left = tree.right;
				}else {
					parent.right = tree.right;
				}
			}else { 
				tree.parent = null;
			}
		}
	}
	public void remove(int key) {
		remove(root,key);
	}
}
