package amalgama.chat.network;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class NetworkPacker {
    public static String pack(String cryptedData, int length, int id) {
        JSONObject json = new JSONObject();
        json.put("data", cryptedData);
        json.put("ln", length);
        json.put("id", id);
        return json.toJSONString() + "$end~";
    }

    public static PackageModel unpack(String jsonData) {
        try {
            JSONParser parser = new JSONParser();
            JSONObject json = (JSONObject) parser.parse(jsonData);
            PackageModel model = new PackageModel();
            model.data = (String) json.get("data");
            model.length = (int) (long) json.get("ln");
            model.id = (int) (long) json.get("id");
            return model;
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return null;
    }
}
