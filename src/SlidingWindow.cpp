#include <iterator>
#include "SlidingWindow.h"
SlidingWindow::SlidingWindow() {
    left_sum = 0;
    right_sum = 0;
}

void SlidingWindow::balance() {
    if (left_set.size() > right_set.size() + 1) {
        auto it = std::prev(left_set.end());
        right_set.insert(*it);
        right_sum += *it;
        left_sum -= *it;
        left_set.erase(it);
    } else if (left_set.size() < right_set.size()) {
        auto it = right_set.begin();
        left_set.insert(*it);
        left_sum += *it;
        right_sum -= *it;
        right_set.erase(it);
    }
}

void SlidingWindow::add_val(long long val) {
    if (left_set.empty() || val <= *left_set.rbegin()) {
        left_set.insert(val);
        left_sum += val;
    } else {
        right_set.insert(val);
        right_sum += val;
    }
    balance();
}

void SlidingWindow::remove_val(long long val) {
    auto it_left = left_set.find(val);
    if (it_left != left_set.end()) {
        left_sum -= val;
        left_set.erase(it_left);
    } else {
        auto it_right = right_set.find(val);
        right_sum -= val;
        right_set.erase(it_right);
    }
    balance();
}

long long SlidingWindow::get_cost() {
    long long median = *left_set.rbegin();
    long long cost = 0;
    cost += right_sum - (long long)right_set.size() * median;
    cost += (long long)left_set.size() * median - left_sum;
    return cost;
}