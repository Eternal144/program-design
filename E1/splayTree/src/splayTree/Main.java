package splayTree;

public class Main {
	static int NUMBER = 10000;
	public static void main(String[] args) {
		int[] arr ; 
//		int arr[] = {8,4,30,26,9,38,1,3,5,7,33,39,31,34};
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
		//删除这里错了。
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

//只改了search，就从5k溢出变成了7k溢出。
