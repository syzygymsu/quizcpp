class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        size_t counts[26] = {};
        for (auto task: tasks) {
            ++counts[task - 'A'];
        }
        size_t maxVal = *max_element(counts, counts+26);
        size_t maxCount = count(counts, counts+26, maxVal);
        return max((maxVal-1) * (n+1) + maxCount, tasks.size());
    }
};
