package amalgama.chat.database;

import jakarta.persistence.*;

@Entity
@Table(name = "messages")
public class Message {
    private long id;
    private User author;
    private String text;
    private long time;
    private String attachments;
    private boolean isSticker;

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @ManyToOne
    @JoinColumn(name = "author", referencedColumnName = "id")
    public User getAuthor() {
        return author;
    }

    public void setAuthor(User author) {
        this.author = author;
    }

    @Column(name = "text")
    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    @Column(name = "time")
    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }

    @Column(name = "attachments")
    public String getAttachments() {
        return attachments;
    }

    public void setAttachments(String attachments) {
        this.attachments = attachments;
    }

    @Column(name = "isSticker")
    public boolean isSticker() {
        return isSticker;
    }

    public void setSticker(boolean sticker) {
        isSticker = sticker;
    }
}
