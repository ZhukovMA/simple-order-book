//
// Created by Жуков Максим Александрович on 19.06.2021.
//

#include "Parser.h"
#include <sstream>
#include <map>

std::string Parser::makeFullJsonString(const std::string& updateString) {
    std::string currentTime, message, tempString, fullJsonString;
    std::istringstream stream(updateString);
    fullJsonString.append("{");
    while(stream >> tempString) {
        if(tempString == "time:") {
            stream >> currentTime;
            fullJsonString.append(R"("time")");
            fullJsonString.append(":");
            fullJsonString.append(currentTime);
        } else if(tempString == "message:") {
            stream >> message;
            fullJsonString.append(R"("message")");
            fullJsonString.append(":");
            fullJsonString.append(message);
        }
    }
    fullJsonString.append("}");
    return fullJsonString;
}

LevelUpdate Parser::parseUpdate(const std::string& updateString) {
    std::string fullJsonString = makeFullJsonString(updateString);
    nlohmann::json result = nlohmann::json::parse(fullJsonString);

    LevelUpdate levelUpdate;
    levelUpdate.time = (unsigned long)(result["time"]);
    for (const auto& score: result["message"]["tick"]["asks"]) {
        levelUpdate.asks.insert(std::make_pair(double(score[0]), int(score[1])));
    }
    for (const auto& score: result["message"]["tick"]["bids"]) {
        levelUpdate.bids.insert(std::make_pair(double(score[0]), int(score[1])));
    }

    return levelUpdate;
}

