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
	
	//将search里面的递归改掉。
	private SNode search(SNode tree, int key) {
		if(tree == null) {
			return null;
		}
		while(true) {
			if(tree.key == key) {
				return tree;
			}
			while( tree.key < key) {
				if(tree.right != null) {
					tree = tree.right;
				}else { 
					return tree;
				}
			}
			while( tree.key > key) {
				if(tree.left != null) {
					tree = tree.left;
				}else {
					return tree;
				}
			}
		}
	}
	
	public SNode search(int key) {
		return search(root, key);
	}
	//普通插入。单独写吧。
	private void insert(SNode tree,int key) {
		if(tree == null ) {
			tree = new SNode(key);
			root = tree;
			return;
		}
		SNode node = search(tree,key);
		SNode temp;
		if(node.key != key) { //找到了，返回
			if(node.key > key) {
				temp = new SNode(key);
				temp.parent = node;
				node.left = temp;
			}else {
				temp = new SNode(key);
				temp.parent = node;
				node.right =  temp;
			}
		}else {
			System.out.println("重复插入");
		}
	}
	//进行右旋
	private SNode RRotation(SNode node) {
		SNode lSNode = node.left;
		node.left = lSNode.right;
		if(lSNode.right != null) {
			lSNode.right.parent = node;
		}
		lSNode.right = node;
		node.parent = lSNode;
		return lSNode;
	}
	//进行左旋，node为目标节点的父节点。返回新节点。
	private SNode LRotation(SNode node) {
		SNode rSNode = node.right;
		node.right = rSNode.left;
		if(rSNode.left != null) {
			rSNode.left.parent = node;
		}
		rSNode.left = node;
		node.parent = rSNode;
		return rSNode;
	}
	
	
	
	//使用自底向上进行伸展，tree为根节点，key为要移到根节点的key。重新赋值parent。
	private SNode splay(SNode tree, int key) {
		if(tree == null) {
			return tree;
		}
		SNode node = search(key); //找到它的位置。
		SNode parent = node.parent;
		SNode pparent;
		if(parent == null) { //本身已经是根节点。 
			return tree; //返回自己这个根节点。
		}
		while(true) { //伴随着转，更改parent。
			if(parent == null) {
				break;
			}
			parent = node.parent;
			pparent = parent.parent; //父节点的父节点。
			while(parent.key > node.key) { //在左子树
				if(pparent == null) {
					parent.left = node.right;
					if(node.right != null) {
						node.right.parent = parent;
					}
					node.right = node.parent;
					node.parent = null;
					node.right = parent;
					parent.parent = node;
					root = node;
					return root;
				}else {
					if(pparent.key > parent.key) {
						pparent.left = RRotation(parent);
						node.parent = pparent;
					}else {
						pparent.right = RRotation(parent);
						node.parent = pparent;
					}
				}
				parent = node.parent;
				pparent = parent.parent; //父节点的父节点。
			}
			
			while(parent.key < node.key) { //在右子树
				if(pparent == null) {
					parent.right = node.left;
					if(node.left != null) {
						node.left.parent = parent;
					}
					node.parent = null;
					node.left = parent;
					parent.parent = node;
					root = node;
					return root;
				}else { //父节点的父节点非空。
					if(pparent.key > parent.key) { //父父节点比父节点大。
						pparent.left = LRotation(parent);
						node.parent = pparent;
					}else {
						pparent.right = LRotation(parent);
						node.parent = pparent;
					}
				}
				parent = node.parent;
				pparent = parent.parent; //父节点的父节点。
			}
		}
		return tree;
	}
	public SNode insert(int key) {
		insert(root,key);
		splay(root, key);
		return root;
	}
	//
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
