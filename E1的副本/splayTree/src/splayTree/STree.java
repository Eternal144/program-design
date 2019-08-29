package splayTree;

public class STree {
	SNode root;
	public STree() {
		this.root = null;
	}
	private SNode getMaxNode(SNode tree) {
		if(tree == null) {
			return null;
		}
		while(tree.right != null) {
			tree = tree.right;
		}
		return tree;
	}
	
	private SNode search(SNode tree, int key) {
		if(tree == null) {
			return null;
		}
		if(tree.key < key ) {
			return search(tree.right, key);
		}else  if(tree.key > key){
			return search(tree.left, key);
		}else { //找到了，则进行伸展，将正在查询的这个节点作为根节点
			root = splay(root, key);
			return tree;
		}
	}
	
	public SNode search(int key) {
		return search(root, key);
	}
	
	private SNode insert(SNode tree,int key) {
		if(tree == null ) {
			return new SNode(key, null, null);
		}
		//如果在左边
		if(key < tree.key) {
			tree.left = insert(tree.left, key);
		}else if(key > tree.key) { //如果在右边
			tree.right = insert(tree.right,key);
		}
		return tree;
	}
	//进行右旋
	private SNode RRotation(SNode node) {
		SNode lSNode = node.left;
		node.left = lSNode.right;
		lSNode.right = node;
		return lSNode;
	}
	//进行左旋
	private SNode LRotation(SNode node) {
		SNode rSNode = node.right;
		node.right = rSNode.left;
		rSNode.left = node;
		return rSNode;
	}
	//使用自底向上进行伸展
	private SNode splay(SNode tree, int key) {
		if(tree == null) {
			return null;
		}
		if(key < tree.key) { //在左子树，向右转
			tree.left = splay(tree.left, key);
			tree = RRotation(tree);
		}else if( key > tree.key) {
			tree.right = splay(tree.right, key);
			tree = LRotation(tree);
		}else {
			return tree;
		}
		return tree;
	}
	public SNode insert(int key) {
		root = insert(root, key);
		root = splay(root, key);
		return root;
	}
	public SNode remove(int key) {
		if(root == null) {
			return null;
		}
		SNode removeNode,newRoot;
		//查找将要删除的节点。
		removeNode = search(root,key);
		if(removeNode == null) {
			return null;
		}
		//将将要删除的节点旋转要根节点
		root = splay(root, key);
		if( root.left != null) {
			newRoot = splay(root.left, getMaxNode(root.left).key);
			newRoot.right = root.right;
		}else {
			newRoot = root.right;
		}
		root = newRoot;
		return removeNode;
	}
	
	public void print() {
		print(root);
	}
	private void print(SNode tree) {
		if(tree != null) {
			System.out.print(tree.key + " ");
			print(tree.left);
			print(tree.right);
		}
	}	
}
