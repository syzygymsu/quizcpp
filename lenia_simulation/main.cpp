#include <iostream>

#include <vector>
#include <string>
#include <limits>

// using namespace std;

enum class ShootingType {
    SENSING,
    DOWNLOAD,
    BOTH
};

struct Segment {
    double left;
    double right;
    ShootingType type;
};



std::ostream& operator<<(std::ostream& os, const Segment& s) {
    return os << s.left << " -> " << s.right << " " << static_cast<int>(s.type);
}

class Simulation {
public:
    Simulation(const std::vector<std::pair<double, double>>& sensing,
        const std::vector<std::pair<double, double>>& downlink)
        : sensing(sensing),
        downlink(downlink)
    {}

    // Рассчитывает производительность спутника при заданных скоростях съемки (uprate) и сброса (downrate)
    double capacity(double uprate, double downrate) const;



    std::vector <Segment> generateSegments(const std::vector<std::pair<double, double>>& sensing,
        const std::vector<std::pair<double, double>>& downlink) const;

private:

    std::pair<double, double> nextElem(const std::vector<std::pair<double, double>>& collection, int index) const {
        if (index < collection.size()) {
            return collection[index];
        }
        return std::make_pair(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    }

    std::vector<std::pair<double, double>> sensing; // Набор интервалов съемки
    std::vector<std::pair<double, double>> downlink; // Набор интервалов сброса
};

std::vector<Segment> Simulation::generateSegments(const std::vector<std::pair<double, double>>& sensing,
    const std::vector<std::pair<double, double>>& downlink) const {

    std::vector<Segment> segments;
    if (sensing.empty() || downlink.empty()) {
        return segments;
    }
    int sensingInd = 0;
    int downlinkInd = 0;
    auto sens = sensing[sensingInd];
    auto down = downlink[downlinkInd];
    while (sensingInd < sensing.size() || downlinkInd < downlink.size()) {
        // cout << sensingInd << "  ___" << downlinkInd << endl;
        if (sens.second < down.first) {
            Segment s;
            s.type = ShootingType::SENSING;
            s.left = sens.first;
            s.right = sens.second;
            segments.push_back(s);
            ++sensingInd;
            sens = nextElem(sensing, sensingInd);
            // cout << "1\n";
        }
        else {
            if (down.second < sens.first) {
                Segment s;
                s.type = ShootingType::DOWNLOAD;
                s.left = down.first;
                s.right = down.second;
                segments.push_back(s);
                ++downlinkInd;
                down = nextElem(downlink, downlinkInd);
                // cout << "2\n" ;
            }
            else {
                if (sens.second < down.second) {
                    if (sens.first < down.first) {
                        Segment s;
                        s.type = ShootingType::SENSING;
                        s.left = sens.first;
                        s.right = down.first;
                        segments.push_back(s);

                        Segment b;
                        b.type = ShootingType::BOTH;
                        b.left = down.first;
                        b.right = sens.second;
                        segments.push_back(b);
                        // std::cout << "3\n";
                    }
                    else {
                        Segment d;
                        d.type = ShootingType::DOWNLOAD;
                        d.left = down.first;
                        d.right = sens.first;
                        segments.push_back(d);

                        Segment b;
                        b.type = ShootingType::BOTH;
                        b.left = sens.first;
                        b.right = sens.second;
                        segments.push_back(b);
                        // std::cout << "4\n";
                    }
                    ++sensingInd;
                    down.first = sens.second;
                    sens = nextElem(sensing, sensingInd);
                }
                else {
                    if (sens.first < down.first) {
                        Segment s;
                        s.type = ShootingType::SENSING;
                        s.left = sens.first;
                        s.right = down.first;
                        segments.push_back(s);

                        Segment b;
                        b.type = ShootingType::BOTH;
                        b.left = down.first;
                        b.right = down.second;
                        segments.push_back(b);
                        // cout << "5\n";

                    }
                    else {
                        Segment d;
                        d.type = ShootingType::DOWNLOAD;
                        d.left = down.first;
                        d.right = sens.first;
                        segments.push_back(d);

                        Segment b;
                        b.type = ShootingType::BOTH;
                        b.left = sens.first;
                        b.right = down.second;
                        segments.push_back(b);
                        // cout << "6\n";
                    }
                    sens.first = down.second;
                    ++downlinkInd;
                    down = nextElem(downlink, downlinkInd);
                }
            }
        }
    }

    return segments;

}

double Simulation::capacity(double uprate, double downrate) const {
    auto segments = generateSegments(sensing, downlink);
    double totalVolume = 0;
    double cap = 0;
    for (const auto& seg : segments) {
        switch (seg.type)
        {
        case ShootingType::SENSING:
            totalVolume += (seg.right - seg.left) * uprate;
            break;
        case ShootingType::DOWNLOAD: {
            if (totalVolume <= 0) break;
            double diff = (seg.right - seg.left) * downrate;
            if (totalVolume - diff >= 0) {
                cap += diff;
                totalVolume -= diff;
            }
            else {
                cap += totalVolume;
                totalVolume = 0;
            }
            break;
        }
        case ShootingType::BOTH: {
            if (downrate <= uprate) {
                totalVolume += (seg.right - seg.left) * (uprate - downrate);
                cap += (seg.right - seg.left) * downrate;
            }
            else {
                totalVolume += (seg.right - seg.left) * (uprate);
                if (totalVolume <= 0) break;
                double diff = (seg.right - seg.left) * downrate;
                if (totalVolume - diff >= 0) {
                    cap += diff;
                    totalVolume -= diff;
                }
                else {
                    cap += totalVolume;
                    totalVolume = 0;
                }
                break;
            }
        }
        }
    }
    return cap;
}

int main()
{
    auto sensing = std::vector<std::pair<double, double>>{ std::make_pair(1.0, 4.0) };
    auto downlink = std::vector<std::pair<double, double>>{ std::make_pair(0.0, 2.0) };

    auto downlink2 = std::vector<std::pair<double, double>>{ std::make_pair(1.0, 4.0) };
    auto sensing2 = std::vector<std::pair<double, double>>{ std::make_pair(0.0, 2.0) };

    Simulation s(sensing2, downlink2);
    //auto segments = s.generateSegments(sensing, downlink);
    //for (const auto& s : segments) {
    //    std::cout << s << endl;
    //}
    std::cout << s.capacity(1, 2);
    return 0;
}
