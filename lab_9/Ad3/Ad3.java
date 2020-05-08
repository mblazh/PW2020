import java.util.Arrays;

class Thr extends Thread {
	private int start;
	private int finish;

	private int[] vector;

	public Thr(int start, int finish, int[] vector) {
		this.start = start;
		this.finish = finish;
		
		this.vector = vector;
	}

	public void run() {
		for (int i = 1; i < vector.length; ++i) {
			if (vector[i] == -1) {
				continue;
			}

			for (int j = start; j < finish; ++j) {
				if (vector[j] != vector[i] && vector[j] % vector[i] == 0) {
					vector[j] = -1;
				}
			}
		}
	}
}

public class Ad3 {
	public static void consecutiveFill(int[] vector) {
		for (int i = 0; i < vector.length; ++i) {
			vector[i] = i + 1;
		}
	}

	public static void main(String args[]) {
		int n = 100;
		int num_threads = 8;

		int vector[] = new int[n];

		consecutiveFill(vector);

		System.out.println("Vector before sieving:");
		System.out.println(Arrays.toString(vector) + "\n");

		Thr[] newThr = new Thr[num_threads];

		int start = 0;
		int extra = n % num_threads;

		for (int i = 0; i < num_threads; ++i) {
			int portion = n / num_threads;
			if (extra > 0) {
				++portion;
				--extra;
			}

			System.out.println("wątek " + i + " szuka liczb w przedziale " + start + "-" + (start + portion - 1));

			(newThr[i] = new Thr(start, start + portion, vector)).start();

			start = start + portion;
		}

		for (int i = 0; i < num_threads; ++i) {
			try {
				newThr[i].join();
			} catch (InterruptedException e) {}
		}

		System.out.println("\nVector after sieving:");
		System.out.println(Arrays.toString(Arrays.stream(vector).filter(x -> x > 0).toArray()));
	}
}
