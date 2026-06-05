#ifndef SLIDING_WINDOW_H
#define SLIDING_WINDOW_H
#include <set>
class SlidingWindow {
private:
    std::multiset<long long> left_set;
    std::multiset<long long> right_set;
    long long left_sum;
    long long right_sum;
    void balance();
public:
    SlidingWindow();
    void add_val(long long val);
    void remove_val(long long val);
    long long get_cost();
};
#endif