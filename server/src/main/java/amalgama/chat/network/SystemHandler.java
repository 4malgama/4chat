package amalgama.chat.network;

import amalgama.chat.GlobalVars;
import amalgama.chat.database.DAOFactory;
import amalgama.chat.database.User;
import amalgama.chat.database.UserDAO;
import amalgama.chat.utils.FileUtils;
import amalgama.chat.utils.RankUtils;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.IOException;
import java.sql.SQLException;

public class SystemHandler implements IHandler {
    @Override
    public void handle(Client client, Command cmd) throws IOException, SQLException {
        if (cmd.args.length == 0)
            return;

        String command = cmd.args[0];

        if (command.equals("get_auth_form")) {
            client.send(DataTypes.SYSTEM, "set_auth_form");
        }
        else if (command.equals("login")) {
            if (cmd.args.length < 2)
                return;

            try {
                JSONParser parser = new JSONParser();
                JSONObject json = (JSONObject) parser.parse(cmd.args[1]);
                String login = (String) json.get("login");
                String password = (String) json.get("password");
                UserDAO userDAO = DAOFactory.getInstance().getUserDAO();
                if (userDAO.checkLoginValid(login, password)) {
                    client.login = login;
                    client.isAuth = true;
                    GlobalVars.clients.put(client.login, client);
                    User user = userDAO.getUserByLogin(client.login);
                    client.account.money = user.getMoney();
                    client.account.gold = user.getGold();
                    client.account.rank = user.getRank();
                    client.account.score = user.getScore();
                    client.account.nextScore = RankUtils.nextScore(client.account.rank);
                    client.account.displayName = user.getDisplayName();
                    client.account.avatarPath = user.getAvatarPath();
                    client.send(DataTypes.SYSTEM, "auth_accept");
                }
                else {
                    JSONObject jsonError = new JSONObject();
                    jsonError.put("code", 403);
                    jsonError.put("message", "Неверный логин или пароль.");
                    client.send(DataTypes.SYSTEM, "auth_reject", jsonError.toJSONString());
                }
            } catch (ParseException e) {
                e.printStackTrace();
            }
        }
        else if (command.equals("get_account_data")) {
            if (client.isAuth) {
                JSONObject json = new JSONObject();
                json.put("money", client.account.money);
                json.put("gold", client.account.gold);
                json.put("rank", client.account.rank);
                json.put("score", client.account.score);
                json.put("nextScore", client.account.nextScore);
                json.put("displayName", client.account.displayName);
                client.send(DataTypes.SYSTEM, "set_account_data", json.toJSONString());
            }
        }
        else if (command.equals("get_avatar_data")) {
            if (client.isAuth) {
                JSONArray json = new JSONArray();
                byte[] bytes = FileUtils.getFileData("avatars/" + client.login + ".jpg");
                for (byte aByte : bytes)
                    json.add(aByte);
                client.send(DataTypes.SYSTEM, "set_avatar_data", json.toJSONString());
            }
        }
        else if (command.equals("c01")) {
            client.isAuth = false;
            client.encrypted = false;
            client.socket.close();
        }
    }
}
