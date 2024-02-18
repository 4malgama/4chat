package amalgama.chat.network.crypt;

import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class KeyManager {
    private static final List<String> keys = new ArrayList<>();
    private static final long KEY_LIMIT = 1000000L;
    private static final int KEY_LENGTH = 128;
    public static String getKey() {
        for (long i = 0; i < KEY_LIMIT; i++) {
            Random rnd = new Random();
            byte[] data = new byte[KEY_LENGTH];
            for (int j = 0; j < KEY_LENGTH; j++) {
                byte c = (byte) rnd.nextInt('A', 'z');
                data[j] = c;
            }
            String result = new String(data);

            if (keys.contains(result))
                continue;
			
			keys.add(result);

            return result;
        }
        return null;
    }

    public static SecretKey getAesKey() {
        SecretKey key = null;
        try {
            KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
            keyGenerator.init(KEY_LENGTH);
            key = keyGenerator.generateKey();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return key;
    }
}
