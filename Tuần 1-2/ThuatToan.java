import java.util.ArrayList;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
import java.util.Random;

class Pair_er implements Comparable<Pair_er> {
    int wide_index;
    int length_index;
    int price;

    Pair_er(int b, int n, int m) {
        wide_index = n;
        length_index = b;
        price = m;
    }

    @Override
    public int compareTo(Pair_er other) {
        return Integer.compare(this.price, other.price);
    }
}

class Algorithm {
    private int length;
    private int wide;
    private ArrayList<String> ArrayList;
    private int[] hang = {-1, 0, 0, 1};
    private int[] cot = {0, 1, -1, 0};

    public void input() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("So hang can nhap: ");
        this.length = scanner.nextInt();
        System.out.print("So cot can nhap: ");
        this.wide = scanner.nextInt();
        scanner.nextLine(); // Consume newline left-over
        ArrayList = new ArrayList<>();
        for (int i = 0; i < length; i++) {
            String x = scanner.nextLine();
            this.ArrayList.add(x);
        }
    }

    public void output() {
        for (String s : ArrayList) {
            System.out.println(s);
        }
    }

    public void DFS(int n, int m) {
        if (this.ArrayList.get(n).charAt(m) == ' ') {
            StringBuilder sb = new StringBuilder(this.ArrayList.get(n));
            sb.setCharAt(m, 'o');
            this.ArrayList.set(n, sb.toString());
            for (int i = 0; i < 4; i++) {
                if (((n + this.hang[i] >= 0) && (n + this.hang[i] < length)) && ((m + this.cot[i] >= 0) && (m + this.cot[i] < wide))) {
                    int k = n + this.hang[i];
                    int l = m + this.cot[i];
                    if (this.ArrayList.get(k).charAt(l) == ' ') {
                        DFS(k, l);
                    }
                }
            }
        }
    }

    public void BFS(int n, int m) {
        Queue<Pair_er> ListQueue = new LinkedList<>();
        ListQueue.add(new Pair_er(n, m, 0));
        while (!ListQueue.isEmpty()) {
            Pair_er q = ListQueue.poll();
            if (this.ArrayList.get(q.length_index).charAt(q.wide_index) == 'S') {
                break;
            }
            StringBuilder sb = new StringBuilder(this.ArrayList.get(q.length_index));
            sb.setCharAt(q.wide_index, 'o');
            this.ArrayList.set(q.length_index, sb.toString());
            for (int i = 0; i < 4; i++) {
                if (q.length_index + this.hang[i] >= 0 && q.length_index + this.hang[i] < length &&
                    q.wide_index + this.cot[i] >= 0 && q.wide_index + this.cot[i] < wide) {
                    int k = q.length_index + this.hang[i];
                    int l = q.wide_index + this.cot[i];
                    if (this.ArrayList.get(k).charAt(l) != 'x') {
                        ListQueue.add(new Pair_er(k, l, 0));
                    }
                }
            }
        }
    }

    public void USC(int n, int m) {
        PriorityQueue<Pair_er> p = new PriorityQueue<>();
        Random rand = new Random();
        p.add(new Pair_er(n, m, rand.nextInt(100) + 1));
        while (!p.isEmpty()) {
            Pair_er q = p.poll();
            if (this.ArrayList.get(q.length_index).charAt(q.wide_index) == 'S') {
                break;
            }
            StringBuilder sb = new StringBuilder(this.ArrayList.get(q.length_index));
            sb.setCharAt(q.wide_index, 'o');
            this.ArrayList.set(q.length_index, sb.toString());
            for (int i = 0; i < 4; i++) {
                if (q.length_index + this.hang[i] >= 0 && q.length_index + this.hang[i] < length &&
                    q.wide_index + this.cot[i] >= 0 && q.wide_index + this.cot[i] < wide) {
                    int f = q.length_index + this.hang[i];
                    int g = q.wide_index + this.cot[i];
                    if (this.ArrayList.get(f).charAt(g) != 'x') {
                        p.add(new Pair_er(f, g, rand.nextInt(100) + 1));
                    }
                }
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Algorithm Test = new Algorithm();
        Test.input();
        Test.USC(1, 1);
        Test.output();
    }
}