package amalgama.chat.network;

import amalgama.chat.network.crypt.AesCrypt;
import amalgama.chat.network.crypt.SimpleCrypt;
import amalgama.chat.network.crypt.StringCodec;
import amalgama.chat.network.utils.DataTypesUtils;

import javax.crypto.SecretKey;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class Client {
    public Socket socket;
    public String login;
    public String roomId;
    public Account account;
    public boolean encrypted = false;
    public boolean isAuth = false;
    public SecretKey privateKey;
    public int publicKey = 2;

    @Override
    public String toString() {
        return "Client(\"" + login + "\", " + socket.getLocalAddress().toString() + ")";
    }

    public void setEncryption(SecretKey pKey) {
        privateKey = pKey;
        encrypted = true;
    }

    public void send(DataTypes type, String ... args) throws IOException {
        String data = DataTypesUtils.typeToString(type) + ";" + String.join(";", args);
        OutputStream os = socket.getOutputStream();
        if (this.encrypted) {
            String encrypted = AesCrypt.crypt(data + "#end~", privateKey);
            String pkg = NetworkPacker.pack(encrypted, data.length(), 0);
            os.write(pkg.getBytes());
            os.flush();
        }
        else {
            String encrypted = SimpleCrypt.encode(data, publicKey);
            String pkg = NetworkPacker.pack(encrypted, data.length(), 0);
            os.write(pkg.getBytes());
            os.flush();
        }
    }
}