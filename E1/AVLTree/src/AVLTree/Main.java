package AVLTree;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class Main {
	static int NUMBER = 10008;
	static int TIMES = 200;
	public static void main(String[] args) {
		Set<Integer> set = new HashSet<Integer>();
//		int[] arr;
//		int[] reverse;
		long[] time;
//		arr = new int[NUMBER];
//		reverse = new int[NUMBER];
		time = new long[TIMES];
		Random rand = new Random();
		for(int i = 0; i < NUMBER;i++) {
			int temp = rand.nextInt(100000);
			if(!set.contains(temp)) {
				set.add(temp);
			}
//			arr[i] = i;
//			reverse[i] = NUMBER - i -1;
//			System.out.println(arr[i]);
		}
		System.out.println(set.size());
		for(int i = 0; i < TIMES; i++) {
			AVLTree tree = new AVLTree();
			
//			for(int x : arr) {
//				tree.insert(x);
//			}
			
			for(int x : set) {
			tree.insert(x);
			}
			long startTime =  System.currentTimeMillis();
			
			for( int z : set) {
				tree.remove(z);
			}
			long endTime=System.currentTimeMillis();
//			for(int z : arr) {
//				tree.remove(z);
//			}
			
			time[i] = endTime -startTime;
		}
		long allTime = 0;
		for( long y : time) {
			allTime += y;
		}
		System.out.println(allTime);
		System.out.println("程序运行时间： "+(allTime/(float)TIMES)+"ms");
	}
}
