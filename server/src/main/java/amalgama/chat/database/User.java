package amalgama.chat.database;

import jakarta.persistence.*;

import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name="users")
public class User {
    private long id;
    private String login;
    private String password;
    private String displayName;
    private int rank;
    private int score;
    private int nextScore;
    private int money;
    private int gold;
    private int adminRank;
    private String avatarPath;

    @OneToMany(mappedBy = "users")
    private Set<Message> messages = new HashSet<>();

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")
    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    @Column(name = "user_login")
    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    @Column(name = "user_password")
    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Column(name = "display_name")
    public String getDisplayName() {
        return displayName;
    }

    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    @Column(name = "user_rank")
    public int getRank() {
        return rank;
    }

    public void setRank(int rank) {
        this.rank = rank;
    }

    @Column(name = "user_score")
    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    @Column(name = "next_score")
    public int getNextScore() {
        return nextScore;
    }

    public void setNextScore(int nextScore) {
        this.nextScore = nextScore;
    }

    @Column(name = "money")
    public int getMoney() {
        return money;
    }

    public void setMoney(int money) {
        this.money = money;
    }

    @Column(name = "gold")
    public int getGold() {
        return gold;
    }

    public void setGold(int gold) {
        this.gold = gold;
    }

    @Column(name = "admin_rank")
    public int getAdminRank() {
        return adminRank;
    }

    public void setAdminRank(int adminRank) {
        this.adminRank = adminRank;
    }

    @Column(name = "avatar_path")
    public String getAvatarPath() {
        return avatarPath;
    }

    public void setAvatarPath(String avatarPath) {
        this.avatarPath = avatarPath;
    }
}
