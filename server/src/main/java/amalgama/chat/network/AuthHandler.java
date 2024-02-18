package amalgama.chat.network;

import amalgama.chat.network.crypt.KeyManager;

import javax.crypto.SecretKey;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Base64;

public class AuthHandler implements IHandler {
    @Override
    public void handle(Client client, Command cmd) throws IOException {
        if (cmd.args[0].equals("hello")) {
            if (client.encrypted)
                return;

            SecretKey privateKey = KeyManager.getAesKey();
            client.send(DataTypes.AUTH, "set_key", Base64.getEncoder().encodeToString(privateKey.getEncoded()));
            client.setEncryption(privateKey);
        }
    }
}
