package splayTree;

public class Main {
	static int NUMBER = 20;
	public static void main(String[] args) {
		int[] arr ;
		arr = new int[NUMBER];
		for(int i = 0; i < NUMBER;i++) {
			arr[i] = 1000+i;
//			System.out.println(arr[i]);
		}
		STree tree = new STree();
		long startTime=System.currentTimeMillis(); 
		for(int x : arr) {
			tree.insert(x);
		}
		long endTime=System.currentTimeMillis();
//		long startTime = System.currentTimeMillis(); 
		//删除这里错了。
		for(int x : arr) {
			if(x == 1100) {
				System.out.println("1000了都没有溢出");
			}
			tree.remove(x);
		}
//		long endTime = System.currentTimeMillis();
		System.out.println("程序运行时间： "+(endTime - startTime)+"ms");
//		tree.print();
//		System.out.println();
//		tree.search(33);
//		tree.remove(31);
//		tree.print();
	}
}
