package amalgama.chat.models;


import java.util.ArrayList;
import java.util.List;

public class MessageModel {
    public long id;
    public String author;
    public String text;
    public List<String> attachments;
    public String sticker;

    public MessageModel() {
        attachments = new ArrayList<>();
    }
}
