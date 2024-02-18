package amalgama.chat.network.utils;

import amalgama.chat.network.DataTypes;

public class DataTypesUtils {
    public static String typeToString(DataTypes type) {
        return type.toString().toLowerCase();
    }

    public static DataTypes stringToType(String type) {
        if (type.equalsIgnoreCase("lobby"))
            return DataTypes.LOBBY;
        if (type.equalsIgnoreCase("room"))
            return DataTypes.ROOM;
        if (type.equalsIgnoreCase("profile"))
            return DataTypes.PROFILE;
        if (type.equalsIgnoreCase("system"))
            return DataTypes.SYSTEM;
        if (type.equalsIgnoreCase("auth"))
            return DataTypes.AUTH;
        return DataTypes.UNKNOWN;
    }
}
