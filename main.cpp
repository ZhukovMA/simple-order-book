#include <iostream>
#include "headers/Message.h"
#include "parser/Parser.h"
#include <vector>
#include <fstream>
#include <chrono>

void updateSnapshotBids(LevelUpdate& snapshot, LevelUpdate& update) {
    for (auto &updateAsk: update.asks) {
        if(updateAsk.second == 0)
            continue;

        for (auto &snapshotBid: snapshot.bids) {
            if (updateAsk.first > snapshotBid.first) {
                snapshot.asks[updateAsk.first] += updateAsk.second;
                break;
            }

            if(snapshotBid.second <= updateAsk.second) {
                updateAsk.second -= snapshotBid.second;
                snapshot.bids.erase(snapshotBid.first);
            } else {
                snapshotBid.second -= updateAsk.second;
                break;
            }
        }
    }
}

void updateSnapshotAsks(LevelUpdate& snapshot, LevelUpdate& update) {
    for (auto &updateBid: update.bids) {
        if(updateBid.second == 0)
            continue;

        for (auto &snapshotAsk: snapshot.asks) {
            if (updateBid.first < snapshotAsk.first) {
                snapshot.bids[updateBid.first] += updateBid.second;
                break;
            }

            if(snapshotAsk.second <= updateBid.second) {
                updateBid.second -= snapshotAsk.second;
                snapshot.asks.erase(snapshotAsk.first);
            } else {
                snapshotAsk.second -= updateBid.second;
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cout << "HELP:\n \targv[1] -- path to data.log,\n \targv[2] -- path to output.log\n";
        exit(1);
    }

    std::ifstream inf(argv[1]);
    std::ofstream outf(argv[2]);
    std::ofstream outTime("logsTime.log");

    if (!inf || !outf || !outTime)
    {
        exit(1);
    }

//    outTime << "std::map<double, int>" << std::endl;
//
//    typedef std::chrono::duration<float> float_seconds;
//    typedef std::chrono::high_resolution_clock clock;

    Parser parser;
    std::string snapshotInput;
    getline(inf, snapshotInput);
    LevelUpdate snapshot = parser.parseUpdate(snapshotInput);

    while (inf) {
        std::string updateInput;
        getline(inf, updateInput);

        if(updateInput.empty()) {
            continue;
        }

        LevelUpdate update = parser.parseUpdate(updateInput);

//        auto startExecutionTime = clock::now();

        updateSnapshotAsks(snapshot, update);
        updateSnapshotBids(snapshot, update);

//        std::chrono::duration<double> duration = clock::now() - startExecutionTime;
//        outTime << update.asks.size() + update.bids.size() << std::endl;
//        outTime << duration.count() * 1000000.0 << '\n';
        outf << update.time << ", " << std::setprecision(15) << snapshot.bids.begin()->first << ", " << snapshot.bids.begin()->second << ", " << snapshot.asks.begin()->first << ", " << snapshot.asks.begin()->second << std::endl;
    }

    return 0;
}
