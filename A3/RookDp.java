public class RookDp {

    public int shortestPath(int boardSize) {
        int[][] dp = new int[boardSize + 1][boardSize + 1];
        for (int i = 1; i <= boardSize; i++) {
            dp[i][1] = 1;
            dp[1][i] = 1;
        }
        for (int i = 2; i <= boardSize; i++) {
            for (int j = 2; j <= boardSize; j++) {
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
        }
        return dp[boardSize][boardSize];
    }

    public static void main(String[] args) {
        RookDp rookDp = new RookDp();
        System.out.println(rookDp.shortestPath(8));
    }
}
