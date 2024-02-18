package amalgama.chat.utils;

public class RankUtils {
    private static final int MAX_RANK_SCORE = 100000;
    private static final int START_NEXT_SCORE = 100;
    private static final int STEP_NEXT_SCORE = 300;

    private static int clamp(int min, int max, int value) {
        return (value < min ? min : (value > max ? max : value));
    }

    public static int nextDeltaScore(int rank) {
        return clamp(0, MAX_RANK_SCORE, START_NEXT_SCORE + STEP_NEXT_SCORE * rank);
    }

    public static int nextScore(int rank) {
        int d = 0;
        for (int i = 0; i <= rank; i++)
            d += nextDeltaScore(i);
        return d;
    }
}
