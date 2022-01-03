#include <list>
#include <unordered_map>
#include <cassert>

template <class KEY_T, class VAL_T>
class LRUCache {
    typedef typename std::unordered_map<KEY_T, typename std::list<std::pair<KEY_T, VAL_T>>::iterator>::iterator MapIter;
public:
    explicit LRUCache(size_t _capacity) : capacity{ _capacity } {
        assert(capacity > 0);
    }

    VAL_T get(KEY_T key) {
        auto it = m.find(key);
        if (it != m.end()) {
            updatePosition(it, it->second->second);
            return it->second->second;
        }
        // throw std::runtime_error("No such key");
        return -1;
    }

    void add(KEY_T key, VAL_T value) {
        auto it = m.find(key);
        if (it != m.end()) {
            updatePosition(it, value);
        }
        else {
            if (m.size() >= capacity) {
                m.erase(cache.back().first);
                cache.pop_back();
            }
            cache.push_front(std::make_pair(key, value));
            m[key] = cache.begin();
        }
    }

private:
    void updatePosition(MapIter it, VAL_T value) {
        cache.erase(it->second);
        cache.push_front(std::make_pair(it->first, value));
        it->second = cache.begin();
    }

private:
    size_t capacity;
    std::list<std::pair<KEY_T, VAL_T>> cache;
    std::unordered_map<KEY_T, decltype(cache.end())> m;
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
