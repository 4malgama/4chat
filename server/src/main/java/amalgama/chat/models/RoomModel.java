package amalgama.chat.models;

import java.util.ArrayList;
import java.util.List;

public class RoomModel {
    public String id;
    public String name;
    public List<String> users;
    public List<MessageModel> messages;
    //public int count;
    public int maxCount;
    public int minRank;
    public int maxRank;
    public int cost;

    public RoomModel() {
        users = new ArrayList<>();
        messages = new ArrayList<>();
    }
}
