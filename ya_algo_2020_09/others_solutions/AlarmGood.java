import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

/**
 * https://contest.yandex.ru/yacup/contest/19036/problems/B/
 */
public class AlarmClocks {
    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        String first = r.readLine();
        String[] s = first.trim().split(" ");
        int N = Integer.parseInt(s[0]);
        int X = Integer.parseInt(s[1]);
        int K = Integer.parseInt(s[2]);
        String second = r.readLine();
        Integer[] starts = Arrays.stream(second.trim().split("\\s")).map(Integer::parseInt).sorted().toArray(Integer[]::new);
        System.out.println(countAlarms(X, K, starts));
    }

    private static long countAlarms(int x, int k, Integer[] times) {
        Map<Integer, Integer> groups = new HashMap<>();
        for (Integer time : times) {
            groups.put(time % x, Math.min(time, groups.getOrDefault(time % x, Integer.MAX_VALUE)));
        }

        Integer[] newTimes = groups.values().toArray(new Integer[0]);
        Arrays.sort(newTimes);


        long left = 0;
        long right = Long.MAX_VALUE;
        while (right > left) {
            long T = left + (right - left) / 2;

            long z = 0;
            for (Integer newTime : newTimes) {
                z += countTimes(newTime, T, x);
            }
            if (z < k) {
                left = T + 1;
            } else {
                right = T;
            } 
        }
    	return left;
    }

    private static long countTimes(long ti, long t, int x) {
        return Math.max((t - ti + x) / x, 0);
    }
}
