class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) {
            return 0;
        }
        int max = height[0];
        int max_index = 0;
        for (size_t i = 0; i < height.size(); ++i) {
            if (height[i] > max) {
                max = height[i];
                max_index = i;
            }
        }
        int summ = 0;
        int curr_max = height[0];
        for (size_t i = 1; i < max_index; ++i) {
            if (height[i] < curr_max) {
                summ += curr_max - height[i];
            } else {
                curr_max = height[i];
            }
        }
        curr_max = height[height.size() - 1];
        for (size_t i = height.size() - 2; i > max_index; --i) {
            if (height[i] < curr_max) {
                summ += curr_max - height[i];
            } else {
                curr_max = height[i];
            }
        }
        return summ;
    }
};
