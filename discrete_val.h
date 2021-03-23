#include <algorithm>
#include <iostream>
#include <map>


class discrete_value {
private:
std::map<float, float> distrib;

public:
    discrete_value() : distrib({}) {}

    discrete_value(std::map<float, float> distr) : distrib(distr) {}

    void print() {
        for (auto it = distrib.begin(); it != distrib.end(); ++it) {
            std::cout << it->first << " " << it->second << "\n";
        }
        if (distrib.empty()) {
            std::cout << "\n";
        }
    }

    discrete_value sum_distrib(discrete_value other) {
        std::map<float, float> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                float key = it1->first + it2->first;
                float val = it1->second * it2->second;
                if (help.find(key) != help.end()) {
                    help[key] += val;
                } else {
                    help[key] = val;
                }
            }
        }
        return discrete_value(help);
    }

    discrete_value max_distrib(discrete_value other) {
        std::map<float, float> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                float key = std::max(it1->first, it2->first);
                float val = it1->second * it2->second;
                if (help.find(key) != help.end()) {
                    help[key] += val;
                } else {
                    help[key] = val;
                }
            }
        }
        return discrete_value(help);
    }

    discrete_value min_distrib(discrete_value other) {
        std::map<float, float> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                float key = std::min(it1->first, it2->first);
                float val = it1->second * it2->second;
                if (help.find(key) != help.end()) {
                    help[key] += val;
                } else {
                    help[key] = val;
                }
            }
        }
        return discrete_value(help);
    }

    discrete_value signed_min_abs_distrib(discrete_value other) {
        std::map<float, float> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                float key = (it1->first * it2->first / (abs(it1->first) * abs(it2->first))) * std::min(abs(it1->first), abs(it2->first));
                float val = it1->second * it2->second;
                if (help.find(key) != help.end()) {
                    help[key] += val;
                } else {
                    help[key] = val;
                }
            }
        }
        return discrete_value(help);
    }

    bool is_empty() {
        return distrib.empty();
    }
};
