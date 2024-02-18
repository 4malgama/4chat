package amalgama.chat.network;
import amalgama.chat.network.utils.DataTypesUtils;

import java.util.Arrays;

public class Command {
    public final DataTypes type;
    public final String[] args;
    public final String source;

    public Command(String source) {
        this.source = source;
        String[] _args = source.split(";");
        type = DataTypesUtils.stringToType(_args[0]);
        args = Arrays.copyOfRange(_args, 1, _args.length);
    }
}
