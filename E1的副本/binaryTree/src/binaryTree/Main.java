package binaryTree;

public class Main {
	static int NUMBER = 10000;
	public static void main(String[] args) {
		int[] arr ;
		arr = new int[NUMBER];
		for(int i = 0; i < NUMBER;i++) {
			arr[i] = 1000+i;
//			System.out.println(arr[i]);
		}
		BTree tree = new BTree();
		long startTime=System.currentTimeMillis(); 
		for(int x : arr) {
			tree.insert(x);
			if(x == 1020) {
				System.out.println("确实1w我也添加了");

			}
		}
		long endTime=System.currentTimeMillis();
//		long startTime=System.currentTimeMillis(); 
//		for(int x : arr) {
//			tree.remove(x);
//		}
//		long endTime=System.currentTimeMillis();
//		System.out.println(endTime);
		System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
//		tree.print();
//		System.out.println(tree.maxKeyNode(root).key);
    }
}
