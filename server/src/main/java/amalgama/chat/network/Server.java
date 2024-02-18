package amalgama.chat.network;

import javax.security.auth.DestroyFailedException;
import javax.security.auth.Destroyable;
import java.io.IOException;
import java.net.ServerSocket;
import java.util.logging.Logger;

public class Server implements Destroyable {
    public static boolean open = false;

    public static void start() {
        if (open) return;

        try (ServerSocket socket = new ServerSocket(1337, 50)) {
            Server.open = true;
            Logger.getGlobal().info("Server opened on port: " + socket.getLocalPort());
            while (!socket.isClosed() && open) {
                ClientHandler clientHandler = new ClientHandler();
                clientHandler.setClient(new Client());
                clientHandler.setSocket(socket.accept());
                new Thread(clientHandler).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        Server.open = false;
    }

    public static void close() {
        open = false;
        Logger.getGlobal().warning("Server closed.");
    }

    @Override
    public void destroy() throws DestroyFailedException {
        Logger.getGlobal().warning("Server destroyed.");
        Destroyable.super.destroy();
    }
}
