package amalgama.chat.database;

public class DAOFactory {
    private static UserDAO userDAO = null;
    private static MessageDAO messageDAO = null;
    private static DAOFactory instance = null;

    public static synchronized DAOFactory getInstance() {
        if (instance == null)
            instance = new DAOFactory();
        return instance;
    }

    public UserDAO getUserDAO() {
        if (userDAO == null)
            userDAO = new UserDAO();
        return userDAO;
    }

    public MessageDAO getMessageDAO() {
        if (messageDAO == null)
            messageDAO = new MessageDAO();
        return messageDAO;
    }
}
