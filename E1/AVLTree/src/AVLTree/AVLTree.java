package AVLTree;

public class AVLTree {
	private AVLNode root;
	public AVLTree() {
		root = null;
	}
	public AVLNode getRoot() {
		return root;
	}
	//查找，如果找的到，则返回本节点，如果找不到，则返回最接近的节点
	private AVLNode search(AVLNode node,int key) {
		if(node.key > key) {
			if(node.left != null) {
				return search(node.left, key);
			}else {
				return node;
			}	
		}else if(node.key < key) {
			if(node.right != null) {
				return search(node.right, key);
			}else {
				return node;
			}
		}else {
			return node;
		}
	}
	//返回以node为根的值最大的节点
	AVLNode maxKeyNode(AVLNode node) {
		if(node.right != null) {
			return maxKeyNode(node.right);
		}else {
			return node;
		}
	}
	//返回以node为根的最小的节点
	AVLNode minKeyNode(AVLNode node) {
		if(node.left != null) {
			return minKeyNode(node.left);
		}else {
			return node;
		}
	}
	//选出最大的值
	private int max(int a, int b) {
		return a > b ? a : b;
	}
	//获取高度
	int getHeight(AVLNode tree) {
		if(tree != null) {
			return tree.height;
		}
		return 0;
	}
	//以前序遍历方式打印
	void print(AVLNode tree) {
		if(tree != null) {
			System.out.print(tree.key + " ");
			print(tree.left);
			print(tree.right);
		}
	}
	void midPrint(AVLNode tree) {
		if(tree != null) {
			print(tree.left);
			System.out.println(tree.key + " ");
			print(tree.right);
		}
	}
	//LL旋转
	private AVLNode LLRotation(AVLNode node1) {
		AVLNode node2;
		node2 = node1.left;
		node1.left = node2.right;
		node2.right = node1;
		node1.height = max(getHeight(node1.left),getHeight(node1.right))+1;
		node2.height = max(getHeight(node2.left), getHeight(node2.right))+1;
		return node2;
	}
    private AVLNode RRRotation(AVLNode node1) {
		AVLNode node2;
		node2 = node1.right;
		node1.right = node2.left;
		node2.left = node1;
		node1.height = max(getHeight(node1.left), getHeight(node1.right))+1;
		node2.height = max(getHeight(node2.left),getHeight(node2.left))+1;
		return node2;
	}
	private AVLNode LRRotation(AVLNode node1) {
		node1.left = RRRotation(node1.left);
		return LLRotation(node1);
	}
	private AVLNode RLRotation(AVLNode node1) {
		node1.right = LLRotation(node1.right);
		return RRRotation(node1);
	}
	private AVLNode insert(AVLNode tree,int key) {
		if (tree == null) {
	        // 新建节点
	        tree = new AVLNode(key, null, null);
	    } else {
	           if (key < tree.key) {    // 应该将key插入到"root的左子树"的情况
	            tree.left = insert(tree.left, key);
	            // 插入节点后，若AVL树失去平衡，则进行相应的调节。
	            if (getHeight(tree.left) - getHeight(tree.right) == 2) {
	                if (key < tree.left.key)
	                	tree = LLRotation(tree);
	                else
	                	tree = LRRotation(tree);
	            }
	        } else if (key > tree.key) {    // 应该将key插入到"root的右子树"的情况
	        	tree.right = insert(tree.right, key);
	            // 插入节点后，若AVL树失去平衡，则进行相应的调节。
	            if (getHeight(tree.right) - getHeight(tree.left) == 2) {
	                if (key > tree.right.key)
	                	tree = RRRotation(tree);
	                else
	                	tree = RLRotation(tree);
	            }
	        } else {    // cmp==0
	            System.out.println("添加失败：不允许添加相同的节点！");
	        }
	    }

	    tree.height = max( getHeight(tree.left), getHeight(tree.right)) + 1;
	    return tree;
	}
	public void insert(int key) {
		root = this.insert(root,key);
	}
	private AVLNode remove(AVLNode tree, AVLNode keyNode) {
		if(tree == null || keyNode == null) {
			return null;
		}
		if(keyNode.key < tree.key) {
			tree.left = remove(tree.left,keyNode);
			if(getHeight(tree.right) - getHeight(tree.left) == 2) {
				AVLNode rAvlNode = tree.right;
				if(getHeight(rAvlNode.left) > getHeight(rAvlNode.right)) {
					tree = RLRotation(tree);
				}else {
					tree = RRRotation(tree);
				}
			}
		}else if(keyNode.key > tree.key) {
			tree.right = remove(tree.right, keyNode);
			if(getHeight(tree.left) - getHeight(tree.right) == 2) {
				AVLNode lAvlNode = tree.left;
				if(getHeight(lAvlNode.right) > getHeight(lAvlNode.left)) {
					tree = LRRotation(tree);
				}else {
					tree = LLRotation(tree);
				}
			}
		}else { //删除tree的tree正好对应要删除的节点  
			if((tree.left != null && tree.right!=null)) {
				if(getHeight(tree.left) > getHeight(tree.right)) {
					//如果左子树比右子树高的话，找出左子树中最大值的节点
					AVLNode maxNode = maxKeyNode(tree.left);
					tree.key = maxNode.key;
					tree.left = remove(tree.left, maxNode);
				}else {
					AVLNode minNode = minKeyNode(tree.right);
					tree.key = minNode.key;
					tree.right = remove(tree.right, minNode);
				}
			}else {
				//两边孩子有一边为空，或者全为空
				AVLNode temp = tree;
				tree = tree.left == null ? tree.right : tree.left;
				temp = null;
			}
		}
		return tree;
	}
	public void remove(int key) {
		AVLNode node = search(root, key);
		//在树中存在才需要移
		if(node.key == key ) {
			root = remove(root, node);
		}
	}
}
