#include <iostream>
#include <string>
#include <json/json.h>
void test_serialize(std::string &str) {
    Json::Value root;
    Json::Value data;
    root["action"] = "run";
    data["number"] = 1;
    root["data"] = data;

    Json::StreamWriterBuilder builder;
    str = Json::writeString(builder,root);
    std::cout << str << std::endl;
}
void test_deserialize(const std::string &str) {
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader>reader(builder.newCharReader());

    JSONCPP_STRING err;
    Json::Value root;
    Json::Value data;

    if (std::string::npos == str.find("{")) {   // jsoncpp对没有"{"会产生异常 parse不会出错 但root["action"].asString()这样代码会出错
        std::cout << "json invalid." << std::endl;
        return;
    }
    if (!reader->parse(str.c_str(), str.c_str() + str.size(), &root, &err)) {
        std::cout << err << std::endl;
        return;
    }

    std::string x = root["action"].asString();
    std::cout << x << std::endl;

    data = root["data"];
    int y = data["number"].asInt();
    std::cout << y << std::endl;
}
int main() {
    std::string str;
    test_serialize(str);
    test_deserialize(str);
    return 0;
}