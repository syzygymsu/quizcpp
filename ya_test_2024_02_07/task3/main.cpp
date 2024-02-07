#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "json.hpp"

namespace {
    struct Offer {
        std::string offer_id;
        int32_t market_sku;
        int32_t price;
    };

    using namespace nlohmann;
    json offerToJson(const Offer& offer) {
        json elem;
        elem["offer_id"] = offer.offer_id;
        elem["market_sku"] = offer.market_sku;
        elem["price"] = offer.price;
        return elem;
    }
    Offer jsonToOffer(const json& elem) {
        Offer offer{ elem["offer_id"].get<std::string>(), elem["market_sku"].get<int32_t>(),
            elem["price"].get<int32_t>() };
        return offer;
    }
}

template<class ForwardIt, class BinaryPredicate>
ForwardIt unique1(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last)
        if (!p(*result, *first) && ++result != first)
            *result = std::move(*first);

    return ++result;
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    int n = std::stoi(line);
    std::vector<Offer> offer_vec;
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        auto offer_json = nlohmann::json::parse(line);
        for (const auto& o : offer_json["offers"]) {
            offer_vec.push_back(jsonToOffer(o));
        }
    }
    std::sort(offer_vec.begin(), offer_vec.end(), [](const Offer& lhs, const Offer& rhs) {
            return std::tie(lhs.price, lhs.offer_id) < std::tie(rhs.price, rhs.offer_id);
        }
    );
    auto last = unique1(offer_vec.begin(), offer_vec.end(), [](const Offer& lhs, const Offer& rhs) { return lhs.offer_id == rhs.offer_id; });
    offer_vec.erase(last, offer_vec.end());

    nlohmann::json output_json;
    for (auto x : offer_vec) {
        output_json["offers"].push_back(offerToJson(x));
    }
    std::cout << output_json.dump() << std::endl;
    return 0;
}
