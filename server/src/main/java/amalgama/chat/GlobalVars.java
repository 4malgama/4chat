package amalgama.chat;

import amalgama.chat.models.RoomModel;
import amalgama.chat.network.Client;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class GlobalVars {
    private static final int ID_LENGTH = 10;
    private static final long ID_LIMIT = 10000L;

    public static Map<String, Client> clients;
    public static Map<String, RoomModel> rooms;
    static {
        clients = new HashMap<>();
        rooms = new HashMap<>();
        createSystemRoom("main", "Основной канал", 0, 0, 0, 10, 0);
        createSystemRoom("vip", "VIP канал", 0, 0, 1, 10, 100);
        createSystemRoom("private", "Приватный канал", 0, 0, 7, 10, 0);
    }

    public static void createRoom(String name, int count, int maxCount, int minRank, int maxRank, int cost) {
        RoomModel room = new RoomModel();
        room.id = genId();
        room.name = name;
        //room.count = count;
        room.maxCount = maxCount;
        room.minRank = minRank;
        room.maxRank = maxRank;
        room.cost = cost;
        if (room.id != null)
            rooms.put(room.id, room);
    }

    public static void createRoom(RoomModel room) {
        room.id = genId();
        if (room.id != null)
            rooms.put(room.id, room);
    }

    private static synchronized String genId() {
        for (long i = 0; i < ID_LIMIT; i++) {
            Random random = new Random();
            byte[] data = new byte[ID_LENGTH];

            for (int j = 0; j < ID_LENGTH; j++) {
                byte c = (byte) random.nextInt('A', 'Z' + 1);
                data[j] = c;
            }

            String result = new String(data) + "#" + i;

            if (rooms.containsKey(result))
                continue;

            return result;
        }
        return null;
    }

    private static void createSystemRoom(String id, String name, int count, int maxCount, int minRank, int maxRank, int cost) {
        RoomModel room = new RoomModel();
        room.id = id;
        room.name = name;
        //room.count = count;
        room.maxCount = maxCount;
        room.minRank = minRank;
        room.maxRank = maxRank;
        room.cost = cost;
        rooms.put(room.id, room);
    }
}
