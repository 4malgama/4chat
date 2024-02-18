package amalgama.chat.network;

import amalgama.chat.GlobalVars;
import amalgama.chat.database.DAOFactory;
import amalgama.chat.database.User;
import amalgama.chat.database.UserDAO;
import amalgama.chat.models.RoomModel;
import amalgama.chat.utils.FileUtils;
import amalgama.chat.utils.StringUtils;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Set;

public class LobbyHandler implements IHandler {

    private void broadcast(DataTypes type, String ... args) throws IOException {
        Set<String> keys = GlobalVars.clients.keySet();
        for (String key : keys) {
            Client client = GlobalVars.clients.get(key);
            if (client != null) {
                client.send(type, args);
            }
        }
    }

    private void sendAddRoom(RoomModel room) throws IOException {
        JSONObject json = new JSONObject();

        json.put("id", room.id);
        json.put("name", room.name);
        json.put("count", room.users.size());
        json.put("maxCount", room.maxCount);
        json.put("minRank", room.minRank);
        json.put("maxRank", room.maxRank);
        json.put("vip", room.cost > 0);
        json.put("cost", room.cost);

        broadcast(DataTypes.LOBBY, "add_room", json.toJSONString());
    }

    @Override
    public void handle(Client client, Command cmd) throws IOException {
        if (!client.isAuth)
            return;

        if (cmd.args[0].equals("get_init_rooms")) {
            Set<String> keys = GlobalVars.rooms.keySet();
            JSONArray roomsJson = new JSONArray();
            for (String key : keys) {
                RoomModel room = GlobalVars.rooms.get(key);
                if (room != null) {
                    JSONObject roomJson = new JSONObject();
                    roomJson.put("id", room.id);
                    roomJson.put("name", room.name);
                    roomJson.put("count", room.users.size());
                    roomJson.put("maxCount", room.maxCount);
                    roomJson.put("minRank", room.minRank);
                    roomJson.put("maxRank", room.maxRank);
                    roomJson.put("cost", room.cost);
                    roomsJson.add(roomJson);
                }
            }
            client.send(DataTypes.LOBBY, "init_rooms", roomsJson.toJSONString());
        }
        else if (cmd.args[0].equals("create_room")) {
            if (cmd.args.length < 2)
                return;

            try {
                JSONParser parser = new JSONParser();
                JSONObject json = (JSONObject) parser.parse(cmd.args[1]);

                RoomModel rm = new RoomModel();

                rm.name = (String) json.get("name");
                rm.maxCount = (int) (long) json.get("maxCount");
                rm.minRank = (int) (long) json.get("minRank");
                rm.maxRank = (int) (long) json.get("maxRank");
                boolean vip = (boolean) json.get("vip");
                rm.cost = vip ? ((int) (long) json.get("cost")) : 0;

                if (StringUtils.contains(rm.name, "!@#$%^&*():;'\"|\\?/.,[]{}-+"))
                    return;

                if (rm.minRank > rm.maxRank)
                    return;

                if (rm.minRank < 0 || rm.maxCount < 0)
                    return;

                if (vip && (rm.cost < 5 || rm.cost > 1000))
                    return;

                if (client.account.rank < rm.minRank || client.account.rank > rm.maxRank)
                    return;

                GlobalVars.createRoom(rm);
                sendAddRoom(rm);
            } catch (ParseException e) {
                e.printStackTrace();
            }
        }
        else if (cmd.args[0].equals("enter_room")) {
            if (cmd.args.length < 2)
                return;

            String roomId = cmd.args[1];

            RoomModel room = GlobalVars.rooms.get(roomId);
            if (room != null) {
                if (room.minRank > client.account.rank)
                    return;
                if (room.maxRank < client.account.rank)
                    return;
                if (room.maxCount > 0 && room.users.size() >= room.maxCount)
                    return;

                JSONArray json = new JSONArray();

                for (String name : room.users) {
                    JSONObject obj = new JSONObject();
                    byte[] imageBytes = FileUtils.getFileData("avatars/" + name + ".jpg");
                    JSONArray bytes = new JSONArray();
                    for (byte b : imageBytes)
                        bytes.add(b);

                    obj.put("id", name);
                    obj.put("data", bytes);
                    json.add(obj);
                }

                room.users.add(client.login);
                client.send(DataTypes.ROOM, "init_room_avatars", json.toJSONString());

                {
                    byte[] imageBytes = FileUtils.getFileData("avatars/" + client.login + ".jpg");

                    JSONObject obj = new JSONObject();
                    JSONArray bytes = new JSONArray();
                    for (byte b : imageBytes)
                        bytes.add(b);
                    obj.put("avatar", bytes);

                    RoomHandler.roomBroadcast(roomId, DataTypes.ROOM, "init_user", client.login, obj.toJSONString());
                }
            }
        }
    }
}
