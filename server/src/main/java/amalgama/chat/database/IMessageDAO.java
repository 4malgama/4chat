package amalgama.chat.database;

import java.sql.SQLException;

public interface IMessageDAO {
    void addMessage(Message message) throws SQLException;
    void updateMessage(Message message) throws SQLException;
    void getMessage(Long id) throws SQLException;
    void deleteMessage(Message message) throws SQLException;
}
