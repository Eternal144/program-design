package AVLTree;

public class Main {
	static int NUMBER = 9000;
	public static void main(String[] args) {
		int[] arr ;
		arr = new int[NUMBER];
		for(int i = 0; i < NUMBER;i++) {
			arr[i] = 1000+i;
//			System.out.println(arr[i]);
		}
		AVLTree tree = new AVLTree();
//		long startTime=System.currentTimeMillis(); 
		for (int x : arr) {
			tree.insert(x);
		}
		long startTime=System.currentTimeMillis(); 
		for(int x : arr) {
			tree.remove(x);
		}
		long endTime=System.currentTimeMillis();
		System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
	}
}
