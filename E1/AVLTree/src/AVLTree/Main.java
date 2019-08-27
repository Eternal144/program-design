package AVLTree;

public class Main {
	static int NUMBER = 10000;
	public static void main(String[] args) {
		int[] arr ;
		arr = new int[NUMBER];
		for(int i = 0; i < NUMBER;i++) {
			arr[i] = 1000+i;
//			System.out.println(arr[i]);
		}
		AVLTree tree = new AVLTree();
		long startTime=System.currentTimeMillis(); 
		for (int x : arr) {
			if(x == 10000) {
				System.out.println("确实插入了1w");
			}
			tree.insert(x);
		}
		long endTime=System.currentTimeMillis();
//		long startTime=System.currentTimeMillis(); 
		for(int x : arr) {
			
			tree.remove(x);
		}
		
		System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
	}
}
