package amalgama.chat.network.crypt;


import java.util.Arrays;

public class StringCodec {
    @Deprecated(forRemoval = true)
    public static String encode(String data, String key) {
        char[] dataChars = data.toCharArray();
        char[] keyChars = key.toCharArray();

        for (int i = 0; i < dataChars.length; i++) {
            char c = (char) ((dataChars[i] + keyChars[i % keyChars.length]) % 0xFF);
            dataChars[i] = c;
        }

        return new String(dataChars);
    }

    @Deprecated(forRemoval = true)
    public static String decode(String data, String key) {
        char[] dataChars = data.toCharArray();
        char[] keyChars = key.toCharArray();

        for (int i = 0; i < dataChars.length; i++) {
            char c = (char) Math.abs((dataChars[i] % 0xFF) - keyChars[i % keyChars.length]);
            dataChars[i] = c;
        }

        return new String(dataChars);
    }

    public static byte[] encode2(byte[] data, byte[] key) {
        byte[] dataChars = data.clone();
        byte[] keyChars = key.clone();

        for (int i = 0; i < dataChars.length; i++)
            dataChars[i] = (byte) ((dataChars[i] + keyChars[i % keyChars.length]));

        return dataChars;
    }

    public static byte[] decode2(byte[] data, byte[] key) {
        byte[] dataChars = data.clone();
        byte[] keyChars = key.clone();

        for (int i = 0; i < dataChars.length; i++)
            dataChars[i] = (byte) ((dataChars[i]) - keyChars[i % keyChars.length]);

        return dataChars;
    }
}
