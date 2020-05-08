import java.util.Random;
import java.util.Arrays;

class Thr extends Thread {
	private int number;
	private int num_threads;

	private char[][] matrix;
	private int[] stats;

	public Thr(int number, int num_threads, char[][] matrix, int[] stats) {
		this.number = number;
		this.num_threads = num_threads;
		
		this.matrix = matrix;
		this.stats = stats;
	}

	public void run() {
		for (char symbol = (char)(number + 33); symbol < (char)(94 + 33); symbol += (char)num_threads) {
			for (int i = 0; i < matrix.length; ++i) {
				for (int j = 0; j < matrix[i].length; ++j) {
					if (matrix[i][j] == symbol) {
						++stats[(int)symbol - 33];
					}
				}
			}

			System.out.println("Wątek " + number + ":\t" + symbol + " " + stats[(int)symbol - 33] + "x");
		}
	}
}

public class Ad2 {
	public static void randomFill(char[][] matrix) {
		Random random = new Random();

		for (int i = 0; i < matrix.length; ++i) {
			for (int j = 0; j < matrix[i].length; ++j) {
				matrix[i][j] = (char)(random.nextInt(94) + 33);
			}
		}
	}

	public static void main(String args[]) {
		int n = 15;
		int m = 20;
		int stats[] = new int[94];
		int num_threads = 10;

		char matrix[][] = new char[n][m];

		randomFill(matrix);

		System.out.println("Calculating histogram for image:");

		for (int i = 0; i < matrix.length; ++i) {
			System.out.println(Arrays.toString(matrix[i]));
		}

		Thr[] newThr = new Thr[num_threads];

		for (int i = 0; i < num_threads; ++i) {
			(newThr[i] = new Thr(i, num_threads, matrix, stats)).start();
		}

		for (int i = 0; i < num_threads; ++i) {
			try {
				newThr[i].join();
			} catch (InterruptedException e) {}
		}
	}
}
