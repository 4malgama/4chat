package amalgama;

import amalgama.chat.database.HibernateUtil;
import org.hibernate.Session;

import java.util.logging.Logger;

public class ServerLoader {

    public static void loadDatabase() {
        Session session = HibernateUtil.getFactory().openSession();
        boolean b = session.isConnected() && session.isOpen();
        session.close();
        assert b : "Error open or connect with session.";
        Logger.getGlobal().info("Database loaded.");
    }
}
