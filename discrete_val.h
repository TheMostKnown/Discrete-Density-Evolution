#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>


class discrete_value {
private:
std::map<double, double> distrib;

public:
    discrete_value() : distrib({}) {}

    discrete_value(std::map<double, double> distr) : distrib(distr) {}

    void print() {
        for (auto it = distrib.begin(); it != distrib.end(); ++it) {
            std::cout << it->first << " " << it->second << "\n";
        }
        if (distrib.empty()) {
            std::cout << "\n";
        }
    }

    discrete_value sum_distrib(discrete_value other) {
        std::map<double, double> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = it1->first + it2->first;
                double val = it1->second * it2->second;
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
        std::map<double, double> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = std::max(it1->first, it2->first);
                double val = it1->second * it2->second;
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
        std::map<double, double> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = std::min(it1->first, it2->first);
                double val = it1->second * it2->second;
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
        std::map<double, double> help;
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double sign;
                if (it1->first == 0 || it2->first == 0) {
                    sign = 0;
                } else if ((it1->first > 0 && it2->first > 0) || (it1->first < 0 && it2->first < 0)) {
                    sign = 1;
                } else {
                    sign = -1;
                }
                double key = sign * std::min(std::fabs(it1->first), std::fabs(it2->first));
                double val = it1->second * it2->second;
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

    double get_val() {
        if (distrib.empty())
            return 0;
        auto ans = distrib.begin();
        for (auto it = distrib.begin(); it != distrib.end(); ++it){
            if (it->second > ans->second) ans = it;
        }
        return ans->first;
    }
};
