package amalgama.chat.utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUtils {
    public static byte[] getFileData(String path) throws IOException {
        Path fp = Paths.get(System.getenv("APPDATA") + "\\achat\\" + path);
        return Files.readAllBytes(fp);
    }
}
