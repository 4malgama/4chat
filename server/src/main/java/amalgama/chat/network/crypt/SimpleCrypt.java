package amalgama.chat.network.crypt;

public class SimpleCrypt {
    public static String encode(String data, int key) {
        byte[] bytes = data.getBytes();
        for (int i = 0; i < bytes.length; i++) {
            bytes[i] += key;
        }
        return new String(bytes);
    }

    public static String decode(String data, int key) {
        byte[] bytes = data.getBytes();
        for (int i = 0; i < bytes.length; i++) {
            bytes[i] -= key;
        }
        return new String(bytes);
    }
}
