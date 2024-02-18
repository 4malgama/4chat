package amalgama.chat.network;

import amalgama.chat.network.crypt.AesCrypt;
import amalgama.chat.network.crypt.SimpleCrypt;

import java.io.*;
import java.net.Socket;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.logging.Logger;

public class ClientHandler implements Runnable {
    private Client client;

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public void setSocket(Socket socket) {
        client.socket = socket;
    }

    private boolean requireEncrypt() throws IOException {
        if (!client.encrypted) {
            client.send(DataTypes.SYSTEM, "bad_key");
            return false;
        }
        return true;
    }

    public void handle(String data) throws IOException, SQLException {
        if (data == null)
            return;

        Command command = new Command(data);
        IHandler handler;

        System.out.println("Received: " + data);

        if (command.type == DataTypes.SYSTEM) {
            requireEncrypt();
            handler = new SystemHandler();
            handler.handle(client, command);
        }
        else if (command.type == DataTypes.AUTH) {
            handler = new AuthHandler();
            handler.handle(client, command);
        }
        else if (command.type == DataTypes.LOBBY) {
            handler = new LobbyHandler();
            handler.handle(client, command);
        }
        else if (command.type == DataTypes.ROOM) {
            handler = new RoomHandler();
            handler.handle(client, command);
        }
    }

    @Override
    public void run() {
        client.login = "#guest";
        client.roomId = "";
        client.account = new Account();
        Logger.getGlobal().info(client.toString() + " > connected.");
        try {
            while (!client.socket.isClosed()) {
                byte[] bytes = new byte[1024];
                int length = client.socket.getInputStream().read(bytes);
                if (length > 0) {
                    String pkg = new String(Arrays.copyOf(bytes, length));

                    PackageModel packageModel = NetworkPacker.unpack(pkg);
                    String decrypted = "";
                    if (client.encrypted) {
                        try {
                            decrypted = AesCrypt.decrypt(packageModel.data, client.privateKey);
                            int pos = decrypted.lastIndexOf("#end~");
                            if (pos != -1)
                                decrypted = decrypted.substring(0, pos);
                        } catch (IllegalArgumentException | NullPointerException e) {
                            Logger.getGlobal().warning("Read exception: " + e.getMessage());
                        }
                    }
                    else {
                        decrypted = SimpleCrypt.decode(packageModel.data, client.publicKey);
                    }

                    try {
                        handle(decrypted);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        } catch (IOException e) {
            Logger.getGlobal().warning("Socket exception: " + e.getMessage());
        }

        try {
            client.socket.close();
            Logger.getGlobal().info(client.toString() + " > disconnected.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}