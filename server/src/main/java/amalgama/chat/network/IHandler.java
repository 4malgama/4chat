package amalgama.chat.network;

import java.io.IOException;
import java.sql.SQLException;

public interface IHandler {
    void handle(Client client, Command cmd) throws IOException, SQLException;
}
