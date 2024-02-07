#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <unordered_map>

class RateLimiter {
public:
    RateLimiter(int userLimit, int serviceLimit, int duration);
    int request(time_t now, int userId);
private:
    void erase(time_t now);
    std::unordered_map<int, int> usersToCount;
    std::queue<std::pair<time_t, int>> q;
    int userLimit;
    int serviceLimit;
    int duration;
};

RateLimiter::RateLimiter(int _userLimit, int _serviceLimit, int _duration)
    : userLimit(_userLimit), serviceLimit(_serviceLimit), duration(_duration) {}

void RateLimiter::erase(time_t now) {
    while (!q.empty()) {
        const auto& elem = q.front();
        if (elem.first + duration >= now) {
            return;
        }
        q.pop();
        auto userCount = usersToCount.find(elem.second);
        if (userCount->second == 1) {
            usersToCount.erase(userCount);
        } else {
            --userCount->second;
        }
    }
}

int RateLimiter::request(time_t now, int userId) {
    erase(now);
    auto pair = usersToCount.try_emplace(userId, 0);
    auto userCount = pair.first;
    if (userCount->second >= userLimit) {
        return 429;
    }
    if (q.size() >= serviceLimit) {
        return 503;
    }
    ++userCount->second;
    q.push(std::make_pair(now, userId));
    return 200;
}


int main()
{
    int userLimit, serviceLimit;
    time_t duration;
    std::cin >> userLimit >> serviceLimit >> duration;
    RateLimiter rateLimiter(userLimit, serviceLimit, duration);
    while (true) {
        time_t time;
        std::cin >> time;
        if (time == -1) {
            break;
        }
        int userId;
        std::cin >> userId;
        std::cout << rateLimiter.request(time, userId) << '\n';
    }
    std::cout << std::flush;
    return 0;
}
