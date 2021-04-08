import java.util.Random;

/**
 * To find the largest square sub matrix of 0's in a matrix of size M x N
 */
public class MaxZeroSquare {
    private final static Random random = new Random(System.nanoTime());
    private final static Runtime runtime = Runtime.getRuntime();

    // Algorithm
    private int[] solve(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        int res = 0;
        int[][] memo = new int[m][n];
        int matrix_row_start = 0;
        int matrix_col_start = 0;

        for (int i = 0; i < m; i++) {
            memo[i][0] = matrix[i][0] == 0 ? 1 : 0;
            if (res < memo[i][0]) {
                res = memo[i][0];
                matrix_row_start = i;
                matrix_col_start = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            memo[0][i] = matrix[0][i] == 0 ? 1 : 0;
            res = Math.max(res, memo[0][i]);
            if (res < memo[0][i]) {
                res = memo[0][i];
                matrix_row_start = 0;
                matrix_col_start = i;
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    memo[i][j] = Math.min(memo[i][j - 1], Math.min(memo[i - 1][j], memo[i - 1][j - 1])) + 1;
                } else {
                    memo[i][j] = 0;
                }
                if (res < memo[i][j]) {
                    res = memo[i][j];
                    matrix_row_start = i;
                    matrix_col_start = j;
                }
            }
        }

        return new int[]{res, matrix_row_start, matrix_col_start};
    }

    // Prints the largest square sub matrix of zeros
    private void printMatrix(int[][] matrix, int[] arr) {
        int res = arr[0];
        int matrix_row_start = arr[1];
        int matrix_col_start = arr[2];
        System.out.println("Size of Maximum size square sub-matrix is: " + res);

        if (res > 0) {
            System.out.println("and the sub-matrix is: ");
            for (int i = matrix_row_start; i > (matrix_row_start - res); i--) {
                for (int j = matrix_col_start; j > matrix_col_start - res; j--) {
                    System.out.print(matrix[i][j] + " ");
                }
                System.out.println();
            }


        }
    }

    // Helper methods generates random matrix of size m x n
    private int[][] generateMatrix(int m, int n) {
        int[][] matrix = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = random.nextBoolean() ? 1 : 0;
            }
        }
        return matrix;
    }

    // Main function
    public static void main(String[] args) {
        MaxZeroSquare maxZeroSquare = new MaxZeroSquare();

        // Sample Case
        int[][] m = new int[][]{{0}};
        maxZeroSquare.printMatrix(m, maxZeroSquare.solve(m));

        // Provided Test Cases
        int[][] testCases = new int[][]{{10, 10}, {10, 100}, {10, 1000}, {100, 1000}, {1000, 1000}};
        for (int[] testCase : testCases) {
            System.gc();
            int[][] matrix = maxZeroSquare.generateMatrix(testCase[0], testCase[1]);

            long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();
            long startTime = System.nanoTime();

            maxZeroSquare.printMatrix(matrix, maxZeroSquare.solve(matrix));
            long endTime = System.nanoTime();
            long usedMemoryAfter = runtime.totalMemory() - runtime.freeMemory();


            double duration = (endTime - startTime);
            duration /= 1000000;

            double memory = usedMemoryAfter - usedMemoryBefore;
            memory /= 1000;
            System.out.printf("Execution time is %f milliseconds\nMemory is %f KB\n\n", duration, memory);
        }
    }
}
