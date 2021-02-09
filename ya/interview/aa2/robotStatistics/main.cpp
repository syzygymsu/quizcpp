#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <queue>

class RobotStatistics {
public:
    RobotStatistics(int threshold, int time_limit);
    void onEvent(time_t now, int userId);
    int getRobotCount(time_t now);
private:
    void removeOld(time_t now);
    std::unordered_map<int, int> usersToCount;
    std::queue<std::pair<time_t, int>> q;
    int threshold;
    int time_limit;
    int robot_count;
};

RobotStatistics::RobotStatistics(int _threshold, int _timelimit) 
    : threshold(_threshold), time_limit(_timelimit), robot_count(0) {}

void RobotStatistics::removeOld(time_t now) {
    while (!q.empty()) {
        auto& elem = q.front();
        if (elem.first + time_limit < now) {
            q.pop();
            auto userCount = usersToCount.find(elem.second);
            if (userCount->second == threshold) {
                --robot_count;
                --userCount->second;
            }
            else if (userCount->second == 1) {
                usersToCount.erase(userCount);
            }
            else {
                --userCount->second;
            }
        }
        else {
            return;
        }
    }
}

void RobotStatistics::onEvent(time_t now, int userId) {
    removeOld(now);
    q.push(std::make_pair(now, userId));
    auto userCount = usersToCount.find(userId);
    if (userCount != usersToCount.end()) {
        ++userCount->second;
        if (userCount->second == threshold) {
            ++robot_count;
        }
    }
    else {
        usersToCount[userId] = 1;
    }

}

int RobotStatistics::getRobotCount(time_t now) {
    removeOld(now);
    return robot_count;
}

int main()
{
    RobotStatistics robotStatistics(3, 10);

    assert(robotStatistics.getRobotCount(5) == 0);

    robotStatistics.onEvent(0, 4);
    robotStatistics.onEvent(1, 2);
    robotStatistics.onEvent(2, 4);
    robotStatistics.onEvent(3, 4);
    robotStatistics.onEvent(4, 4);
    robotStatistics.onEvent(5, 4);
    robotStatistics.onEvent(6, 1);
    int res = robotStatistics.getRobotCount(7);
    assert(res == 1);
    return 0;
}
