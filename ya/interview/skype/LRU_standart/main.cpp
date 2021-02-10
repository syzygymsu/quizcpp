#include <iostream>

#include <list>
#include <unordered_map>
#include <assert.h>

// using namespace std;

template <class KEY_T, class VAL_T>
class LRUCache {
    int capacity;
    std::list<std::pair<KEY_T, VAL_T>> cache;
    std::unordered_map<KEY_T, decltype(cache.end())> m;

    void updatePosition(KEY_T key, VAL_T value) {
        cache.erase(m[key]);
        cache.push_front(std::make_pair(key, value));
        m[key] = cache.begin();
    }
public:
    LRUCache(int _capacity) : capacity{ _capacity } {}

    VAL_T get(KEY_T key) {
        if (m.find(key) != m.end()) {
            updatePosition(key, m[key]->second);
            return m[key]->second;
        }
        // throw std::runtime_error("No such key");
        return -1;
    }

    void add(KEY_T key, VAL_T value) {
        if (m.find(key) != m.end()) {
            updatePosition(key, value);
        }
        else {
            cache.push_front(std::make_pair(key, value));
            m[key] = cache.begin();
            if (m.size() > capacity) {
                m.erase(cache.back().first);
                cache.pop_back();
            }
        }
    }
};

int main()
{
    LRUCache<int, int> cache(4);
    cache.add(1, 1);
    cache.add(10, 15);
    cache.add(15, 10);
    cache.add(10, 16);
    cache.add(12, 15);
    cache.add(18, 10);
    cache.add(13, 16);

    assert(-1 == cache.get(1));
    assert(16 == cache.get(10));
    assert(-1 == cache.get(15));
    return 0;
}
