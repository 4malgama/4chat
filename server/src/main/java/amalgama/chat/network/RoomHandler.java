package amalgama.chat.network;

import amalgama.chat.GlobalVars;
import amalgama.chat.database.DAOFactory;
import amalgama.chat.database.User;
import amalgama.chat.database.UserDAO;
import amalgama.chat.models.MessageModel;
import amalgama.chat.models.RoomModel;
import amalgama.chat.utils.RankUtils;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.sql.SQLException;

public class RoomHandler implements IHandler {

    public static void roomBroadcast(String roomId, DataTypes type, String ... args) throws IOException {
        RoomModel room = GlobalVars.rooms.get(roomId);
        if (room != null) {
            for (String name : room.users)
                GlobalVars.clients.get(name).send(type, args);
        }
    }

    @Override
    public void handle(Client client, Command cmd) throws IOException, SQLException {
        if (!client.isAuth)
            return;

        String command = cmd.args[0];
        if (command.equals("get_init_room_messages")) {
            if (cmd.args.length < 2)
                return;

            JSONObject json = new JSONObject();

            String roomId = cmd.args[1];
            RoomModel room = GlobalVars.rooms.get(roomId);

            json.put("roomId", roomId);
            json.put("roomName", room.name);

            JSONArray arr = new JSONArray();

            for (MessageModel msg : room.messages) {
                JSONObject obj = new JSONObject();
                obj.put("author", msg.author);
                obj.put("text", msg.text);
                arr.add(obj);
            }

            json.put("messages", arr);

            client.send(DataTypes.ROOM, "init_room_messages", json.toJSONString());
        }
        else if (command.equals("send_message")) {
            if (cmd.args.length < 3)
                return;

            String roomId = cmd.args[1];
            String text = cmd.args[2];

            RoomModel room = GlobalVars.rooms.get(roomId);
            if (room != null) {
                MessageModel message = new MessageModel();
                message.id = room.messages.size();
                message.author = client.login;
                message.text = text;
                room.messages.add(message);

                JSONObject json = new JSONObject();
                json.put("id", message.id);
                json.put("author", message.author);
                json.put("text", message.text);

                UserDAO userDAO = DAOFactory.getInstance().getUserDAO();

                User user = userDAO.getUserByLogin(client.login);

                client.account.score += 10;
                client.send(DataTypes.PROFILE, "add_score", "10");
                if (client.account.score >= client.account.nextScore) {
                    client.account.rank++;
                    client.account.nextScore = RankUtils.nextScore(client.account.rank);
                    client.account.money += 250;
                    client.send(DataTypes.PROFILE, "rank_up");
                    client.send(DataTypes.PROFILE, "add_money", "250");
                    user.setRank(client.account.rank);
                    user.setMoney(client.account.money);
                }
                user.setScore(client.account.score);

                userDAO.updateUser(user);

                roomBroadcast(roomId, DataTypes.ROOM, "message", roomId, json.toJSONString());
            }
        }
    }
}
