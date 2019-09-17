package binaryTree;
import java.util.*;

public class Main {
	static int NUMBER = 10000;
	static int TIMES = 400;
	public static void main(String[] args) {
		Set<Integer> set = new HashSet<Integer>();
		int[] arr;
		int[] reverse;
		long[] time;
		arr = new int[NUMBER];
		reverse = new int[NUMBER];
		time = new long[TIMES];
		Random rand = new Random();
		set.clear();
		for(int i = 0; i < NUMBER;i++) { //在这里插入随机数。最好保证都不一样？
			int temp = rand.nextInt(100000);
//			System.out.println(set);
			if(!set.contains(temp)) {
				set.add(temp);
			}
//			arr[i] = i;
//			reverse[i] = NUMBER - i - 1;
		}
		System.out.println("总共取了" + set.size() + "个点");
		for(int i = 0; i < TIMES; i++) {
			BTree tree = new BTree();
			
			for(int x : set) {
				tree.insert(x);
			}
			
			long startTime =  System.currentTimeMillis();
			for( int z : set) {
				tree.remove(z);
			}
			long endTime=System.currentTimeMillis();
			
			time[i] = endTime -startTime;
//			for(int x : arr) {
//				tree.insert(x);
//			}
//			for(int z : reverse) {
//				tree.remove(z);
//			}
		}
		
		long allTime = 0;
		for( long y : time) {
			allTime += y;
		}
		System.out.println("总时间为： " + allTime);
		System.out.println("程序运行时间： "+(allTime/(float)TIMES)+"ms");
		
//		tree.print();
//		System.out.println(tree.maxKeyNode(root).key);
    }
}
