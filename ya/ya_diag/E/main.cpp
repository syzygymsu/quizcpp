#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

class RobotStatistics {
public:
    RobotStatistics(int threshold, int all_threshold, int time_limit);
    int onEvent(time_t now, int userId);
private:
    void removeOld(time_t now);
    std::unordered_map<int, int> usersToCount;
    std::queue<std::pair<time_t, int>> q;
    int threshold;
    int all_threshold;
    int time_limit;
};

RobotStatistics::RobotStatistics(int _threshold, int _all_threshold, int _timelimit)
    : threshold(_threshold), all_threshold(_all_threshold), time_limit(_timelimit){}

void RobotStatistics::removeOld(time_t now) {
    while (!q.empty()) {
        auto& elem = q.front();
        if (elem.first + time_limit < now) {
            q.pop();
            auto userCount = usersToCount.find(elem.second);
            if (userCount->second == 1) {
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

int RobotStatistics::onEvent(time_t now, int userId) {
    removeOld(now);
    auto userCount = usersToCount.find(userId);
    if (userCount != usersToCount.end()) {
        if (userCount->second == threshold) {
            return 429;
        }
        if (q.size() >= all_threshold) {
            return 503;
        }
        ++userCount->second;
    }
    else {
        if (q.size() >= all_threshold) {
            return 503;
        }
        usersToCount[userId] = 1;
    }
    q.push(std::make_pair(now, userId));
    return 200;
}


int main()
{
    int userLimit, serviceLimit;
    time_t duration;
    std::cin >> userLimit >> serviceLimit >> duration;
    RobotStatistics robotStatistics(userLimit, serviceLimit, duration);
    while (true) {
        int time;
        std::cin >> time;
        if (time == -1) {
            break;
        }
        int userId;
        std::cin >> userId;
        std::cout << robotStatistics.onEvent(time, userId) << '\n';
    }
    std::cout << std::flush;
    return 0;
}
