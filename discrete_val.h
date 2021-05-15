#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>


class discrete_value {
private:
    std::vector<std::pair<double, double>> distrib;
    double min, max;

public:
    discrete_value() : distrib({}), min(0), max(0) {}

    discrete_value(std::vector<std::pair<double, double>> distr) : distrib(distr), min(distr[0].first), max(distr[distr.size()-1].first) {}

    discrete_value(double start, double end) {
        if (end < start) {
            std::swap(start, end);
        }
        min = start;
        max = end;
        for (double i = start; i <= end; i++) {
            distrib.push_back(std::make_pair(i, 0));
        }
    }

    void print() {
        for (auto it = distrib.begin(); it != distrib.end(); ++it) {
            std::cout << it->first << " " << it->second << "\n";
        }
        if (distrib.empty()) {
            std::cout << "\n";
        }
    }

    discrete_value sum_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(this->min + other.min, this->max + other.max);
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = it1->first + it2->first;
                double val = it1->second * it2->second;
                help.distrib[key - help.min].second += val;
            }
        }
        return help;
    }

    discrete_value max_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(std::max(this->min, other.min), std::max(this->max, other.max));
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = std::max(it1->first, it2->first);
                double val = it1->second * it2->second;
                help.distrib[key - help.min].second += val;
            }
        }
        return help;
    }

    discrete_value min_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(std::min(this->min, other.min), std::min(this->max, other.max));
        for (auto it1 = distrib.begin(); it1 != distrib.end(); ++it1) {
            for (auto it2 = other.distrib.begin(); it2 != other.distrib.end(); ++it2) {
                double key = std::min(it1->first, it2->first);
                double val = it1->second * it2->second;
                help.distrib[key - help.min].second += val;
            }
        }
        return help;
    }

    discrete_value signed_min_abs_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(
            -std::max({std::fabs(this->min), std::fabs(other.min), std::fabs(this->max), std::fabs(other.max)}),
            std::max({std::fabs(this->min), std::fabs(other.min), std::fabs(this->max), std::fabs(other.max)})
            );
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
                help.distrib[key - help.min].second += val;
            }
        }
        return help;
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
