package amalgama.chat.database;

import org.hibernate.Session;
import org.hibernate.query.Query;
import org.hibernate.transform.Transformers;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class UserDAO implements IUserDAO {
    @Override
    public void addUser(User usr) throws SQLException {
        Session session = null;
        try {
            session = HibernateUtil.getFactory().openSession();
            session.beginTransaction();
            session.save(usr);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
    }

    @Override
    public void updateUser(User usr) throws SQLException {
        Session session = null;
        try {
            session = HibernateUtil.getFactory().openSession();
            session.beginTransaction();
            session.update(usr);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
    }

    @Override
    public User getUserById(Long id) throws SQLException {
        Session session = null;
        User user = null;
        try {
            session = HibernateUtil.getFactory().openSession();
            user = session.load(User.class, id);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen()) {
                session.close();
            }
        }
        return user;
    }

    @Override
    public Collection getUsers() throws SQLException {
        Session session = null;
        List<User> users = new ArrayList<>();
        try {
            session = HibernateUtil.getFactory().openSession();
            Query query = session.createNativeQuery("SELECT * FROM users;");
            query.setResultTransformer(Transformers.aliasToBean(User.class));
            users = (ArrayList<User>) query.getResultList();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
        return users;
    }

    @Override
    public void deleteUser(User usr) throws SQLException {
        Session session = null;
        try {
            session = HibernateUtil.getFactory().openSession();
            session.beginTransaction();
            session.delete(usr);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
    }

    @Override
    public User getUserByLogin(String login) throws SQLException {
        Session session = null;
        User user = null;
        try {
            session = HibernateUtil.getFactory().openSession();
            session.beginTransaction();
            Query q = session.createQuery("from User where login = ?1")
                    .setParameter(1, login);
            List<User> rows = q.list();
            if (rows.size() == 1)
                user = rows.get(0);
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
            user = null;
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
        return user;
    }

    @Override
    public boolean checkLoginValid(String login, String password) throws SQLException {
        Session session = null;
        boolean ok = false;
        try {
            session = HibernateUtil.getFactory().openSession();
            session.beginTransaction();
            Query q = session.createQuery("from User where login = ?1 and password = ?2")
                    .setParameter(1, login)
                    .setParameter(2, password);
            List<User> rows = q.list();
            ok = rows.size() == 1;
            session.getTransaction().commit();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (session != null && session.isOpen())
                session.close();
        }
        return ok;
    }
}
