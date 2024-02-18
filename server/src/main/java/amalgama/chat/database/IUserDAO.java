package amalgama.chat.database;

import java.sql.SQLException;
import java.util.Collection;

public interface IUserDAO {
    void addUser(User usr) throws SQLException;
    void updateUser(User usr) throws SQLException;
    User getUserById(Long id) throws SQLException;
    Collection getUsers() throws SQLException;
    void deleteUser(User usr) throws SQLException;
    User getUserByLogin(String login) throws SQLException;
    boolean checkLoginValid(String login, String password) throws SQLException;
}
