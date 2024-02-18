package amalgama.chat.utils;

import java.util.Random;

public class StringUtils {
    public static boolean contains(String str, String chars) {
        byte[] strBytes = str.getBytes();
        byte[] charsBytes = chars.getBytes();
        for (byte strByte : strBytes) {
            for (byte aByte : charsBytes) {
                if (strByte == aByte)
                    return true;
            }
        }
        return false;
    }
}
