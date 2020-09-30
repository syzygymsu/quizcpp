package me.khabib.yandex;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Stones {
    public static void main(String[] args) throws Exception {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

        String J = r.readLine();
        String S = r.readLine();
        System.out.println(checkStones(J, S));
    }

    private static int checkStones(String j, String s) {
        int k = 0;
        for (char c : s.toCharArray()) {
            if (j.indexOf(c) >= 0) k++;
        }
        return k;
    }
}
