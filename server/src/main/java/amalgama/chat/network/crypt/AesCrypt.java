package amalgama.chat.network.crypt;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import java.util.Base64;

public class AesCrypt {
    public static String crypt(String input, SecretKey key) {
        String ret = null;
        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, key);
            byte[] cipherText = cipher.doFinal(input.getBytes());
            ret = Base64.getEncoder().encodeToString(cipherText);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return ret;
    }

    public static String decrypt(String input, SecretKey key) {
        String ret = null;
        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/NoPadding");
            cipher.init(Cipher.DECRYPT_MODE, key);
            byte[] plainText = cipher.doFinal(Base64.getDecoder().decode(input));
            ret = new String(plainText);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return ret;
    }

    public static String prepareString(String in) {
        int c = in.length() % 16;
        if (c != 0) {
            StringBuilder builder = new StringBuilder();
            builder.append(in);
            for (int i = 0; i < 16 - c; i++) {
                builder.append(' ');
            }
            return new String(builder);
        }
        return in;
    }
}