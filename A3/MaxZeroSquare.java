import java.util.Random;

public class MaxZeroSquare {
    private final static Random random = new Random(System.nanoTime());
    private final static Runtime runtime = Runtime.getRuntime();

    private void solve(int[][] matrix) {
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

    private int[][] generateMatrix(int m, int n) {
        int[][] matrix = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = random.nextBoolean() ? 1 : 0;
            }
        }
        return matrix;
    }


    public static void main(String[] args) {
        MaxZeroSquare maxZeroSquare = new MaxZeroSquare();
        /*
        maxZeroSquare.solve(new int[][]{{0, 0}, {0, 0}});                                     // 2
        maxZeroSquare.solve(new int[][]{{0}});                                               // 1
        maxZeroSquare.solve(new int[][]{{1}});                                               // 0
        maxZeroSquare.solve(new int[][]{{1, 1}, {1, 1}});                                    // 0
        maxZeroSquare.solve(new int[][]{{0, 0, 0}, {0, 1, 1}, {0, 1, 1}});                    // 1
        maxZeroSquare.solve(new int[][]{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});                    // 1
        maxZeroSquare.solve(new int[][]{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});                    // 0
        maxZeroSquare.solve(new int[][]{{0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}); // 3
        maxZeroSquare.solve(new int[][]{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}); // 4
        */

        int[][] testCases = new int[][]{{10, 10}, {10, 100}, {10, 1000}, {100, 1000}, {1000, 1000}};

        for (int[] testCase : testCases) {
            int[][] matrix = maxZeroSquare.generateMatrix(testCase[0], testCase[1]);

            long usedMemoryBefore = runtime.totalMemory() - runtime.freeMemory();
            long startTime = System.nanoTime();

            maxZeroSquare.solve(matrix);

            long usedMemoryAfter = runtime.totalMemory() - runtime.freeMemory();
            long endTime = System.nanoTime();

            double duration = (endTime - startTime);
            duration /= 1000000;

            double memory = usedMemoryAfter - usedMemoryBefore;
            memory /= 1000;
            System.out.printf("Execution time is %f milliseconds\nMemory is %f KB\n\n", duration, memory);
        }
    }
}
