import java.util.*;

public class Skyline {

    private final static Random random = new Random(System.nanoTime());
    private final static int BOUND = 100;

    static class Point implements Comparable<Point> {
        int coordinate;
        int height;
        boolean isStart;


        @Override
        public int compareTo(Point o) {
            if (this.coordinate != o.coordinate) {
                return this.coordinate - o.coordinate;
            } else {
                return (this.isStart ? -this.height : this.height) - (o.isStart ? -o.height : o.height);
            }
        }
    }

    static class IpPoint {
        int left;
        int height;
        int right;
    }

    public List<List<Integer>> getSkyline(IpPoint[] ipPoints) {
        int noOfBuildings = ipPoints.length;
        Point[] points = new Point[2 * noOfBuildings];

        int idx = 0;
        for (IpPoint ipPoint : ipPoints) {
            points[idx] = new Point();
            points[idx].coordinate = ipPoint.left;
            points[idx].height = ipPoint.height;
            points[idx].isStart = true;

            points[idx + 1] = new Point();
            points[idx + 1].coordinate = ipPoint.right;
            points[idx + 1].height = ipPoint.height;
            points[idx + 1].isStart = false;
            idx += 2;
        }

        // sort the building points
        Arrays.sort(points);

        TreeMap<Integer, Integer> maxPriorityQueue = new TreeMap<>();

        // Building height is 0 and it occurred 1 time
        maxPriorityQueue.put(0, 1);

        int prevMaxHeight = 0;

        List<List<Integer>> result = new ArrayList<>();

        for (Point point : points) {
            if (point.isStart) {
                maxPriorityQueue.compute(point.height, (key, value) -> {
                    if (value != null) {
                        return value + 1;
                    }
                    return 1;
                });
            } else {
                maxPriorityQueue.compute(point.height, (key, value) -> {
                    if (value == null || value == 1) {
                        return null;
                    }
                    return value - 1;
                });
            }

            int currentMaxHeight = maxPriorityQueue.lastKey();

            if (prevMaxHeight != currentMaxHeight) {
                result.add(Arrays.asList(point.coordinate, currentMaxHeight));
                prevMaxHeight = currentMaxHeight;
            }
        }
        return result;
    }

    private void compareAndSwap(IpPoint ipPoint) {
        // loop until left and right are not equal
        while (ipPoint.left == ipPoint.right) {
            ipPoint.right = random.nextInt(BOUND);
        }

        // If left is greater than right swap
        if (ipPoint.left > ipPoint.right) {
            int temp = ipPoint.left;
            ipPoint.left = ipPoint.right;
            ipPoint.right = temp;
        }
    }

    private IpPoint generateIpPoint() {
        IpPoint ipPoint = new IpPoint();
        ipPoint.left = random.nextInt(BOUND);
        ipPoint.height = random.nextInt(BOUND);
        ipPoint.right = random.nextInt(BOUND);
        compareAndSwap(ipPoint);
        return ipPoint;
    }

    private IpPoint[] generateIpPoints(int noOfPoints) {
        IpPoint[] ipPoints = new IpPoint[noOfPoints];
        for (int i = 0; i < noOfPoints; i++)
            ipPoints[i] = generateIpPoint();
        return ipPoints;
    }

    public static void main(String[] args) {
        Skyline skyline = new Skyline();
        skyline.getSkyline(skyline.generateIpPoints(5));
        for (int i = 10; i <= 100000; i *= 10) {
            IpPoint[] ipPoints = skyline.generateIpPoints(i);
            long startTime = System.nanoTime();
            List<List<Integer>> result = skyline.getSkyline(ipPoints);
            long endTime = System.nanoTime();
            double duration = (endTime - startTime);
            duration /= 1000000;
            System.out.printf("For N = %d:\n\tExecution time is %f secs\n\tOutput:%s\n\n", i, duration, result);
        }
    }
}
