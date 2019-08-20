package splayTree;

public class Main {
//	{3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
//	private static int[] arr = {8,4,30,2,6,9,38,1,3,5,7,33,39,31,34};
	static int NUMBER = 5000;
	public static void main(String[] args) {
		int[] arr ;
		arr = new int[NUMBER];
		for(int i = 0; i < NUMBER;i++) {
			arr[i] = 1000+i;
//			System.out.println(arr[i]);
		}
		STree tree = new STree();
//		long startTime=System.currentTimeMillis(); 
		for(int x : arr) {
			tree.insert(x);
		}
//		long endTime=System.currentTimeMillis();
		long startTime = System.currentTimeMillis(); 
		for(int x : arr) {
			tree.remove(x);
		}
		long endTime = System.currentTimeMillis();
		System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
//		tree.print();
//		System.out.println();
//		tree.search(33);
//		tree.remove(31);
//		tree.print();
	}
}
