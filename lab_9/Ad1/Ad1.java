import java.util.Random;
import java.util.Arrays;

class Thr extends Thread {
	private int number;
	private int num_threads;

	private int[] vectorA;
	private int[] vectorB;
	private int[] vectorC;

	public Thr(int number, int num_threads, int[] vectorA, int[] vectorB, int[] vectorC) {
		this.number = number;
		this.num_threads = num_threads;
		
		this.vectorA = vectorA;
		this.vectorB = vectorB;
		this.vectorC = vectorC;
	}

	public void run() {
		for (int i = number; i < vectorC.length; i += num_threads) {
			vectorC[i] = vectorA[i] + vectorB[i];
		}
	}
}

public class Ad1 {
	public static void randomFill(int[] vector) {
		Random random = new Random();

		for (int i = 0; i < vector.length; ++i) {
			vector[i] = random.nextInt(10);
		}
	}

	public static void main(String args[]) {
		int n = 15;
		int num_threads = 10;

		int vectorA[] = new int[n];
		int vectorB[] = new int[n];
		int vectorC[] = new int[n];

		randomFill(vectorA);
		randomFill(vectorB);

		System.out.println(Arrays.toString(vectorA));
		System.out.println("+");
		System.out.println(Arrays.toString(vectorB));
		System.out.println("=");

		Thr[] newThr = new Thr[num_threads];

		for (int i = 0; i < num_threads; ++i) {
			(newThr[i] = new Thr(i, num_threads, vectorA, vectorB, vectorC)).start();
		}

		for (int i = 0; i < num_threads; ++i) {
			try {
				newThr[i].join();
			} catch (InterruptedException e) {}
		}

		System.out.println(Arrays.toString(vectorC));
	}
}
