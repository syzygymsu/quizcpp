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

    private static int countAlarms(int x, int k, Integer[] times) {
        Map<Integer, Integer> groups = new HashMap<>();
        for (Integer time : times) {
            groups.put(time % x, Math.min(time, groups.getOrDefault(time % x, Integer.MAX_VALUE)));
        }

        Integer[] newTimes = groups.values().toArray(new Integer[0]);
        Arrays.sort(newTimes);


        int left = 0;
        int right = Integer.MAX_VALUE;
        while (true) {
            int T = left + (right - left) / 2;

            int z = 0;
            for (Integer newTime : newTimes) {
                z += countTimes(newTime, T, x);
            }
            if (z < k) {
                left = T;
            } else if (z > k) {
                right = T;
            } else {
                return T;
            }
        }


    }

    private static int countTimes(int ti, int t, int x) {
        return 1 + Math.max((t - ti) / x, 0);
    }
}
