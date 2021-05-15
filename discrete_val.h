#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>


class discrete_value {
private:
    std::vector<double> distrib;
    double min, max;

public:
    discrete_value() : distrib({}), min(0), max(0) {}

    discrete_value(std::vector<double> distr, double start, double end) : distrib(distr), min(start), max(end) {}

    discrete_value(double start, double end) {
        if (end < start) {
            std::swap(start, end);
        }
        min = start;
        max = end;
        distrib.resize(end - start + 1);
    }

    void print() {
        for (size_t i = 0; i < distrib.size(); ++i) {
            std::cout << min + i << " " << distrib[i] << "\n";
        }
        if (distrib.empty()) {
            std::cout << "\n";
        }
    }

    discrete_value sum_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(this->min + other.min, this->max + other.max);
        for (double i = 0; i < distrib.size(); ++i) {
            for (double j = 0; j < other.distrib.size(); ++j) {
                double key = (min + i) + (other.min + j);
                double val = distrib[i] * other.distrib[j];
                help.distrib[key - help.min] += val;
            }
        }
        return help;
    }

    discrete_value max_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(std::max(this->min, other.min), std::max(this->max, other.max));
        for (double i = 0; i < distrib.size(); ++i) {
            for (double j = 0; j < other.distrib.size(); ++j) {
                double key = std::max((min + i), (other.min + j));
                double val = distrib[i] * other.distrib[j];
                help.distrib[key - help.min] += val;
            }
        }
        return help;
    }

    discrete_value min_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help(std::min(this->min, other.min), std::min(this->max, other.max));
        for (double i = 0; i < distrib.size(); ++i) {
            for (double j = 0; j < other.distrib.size(); ++j) {
                double key = std::min((min + i), (other.min + j));
                double val = distrib[i] * other.distrib[j];
                help.distrib[key - help.min] += val;
            }
        }
        return help;
    }

    discrete_value signed_min_abs_distrib(discrete_value other) {
        if (distrib.empty()) return other;
        if (other.distrib.empty()) return *this;
        discrete_value help (
            -std::max({std::fabs(this->min), std::fabs(other.min), std::fabs(this->max), std::fabs(other.max)}),
            std::max({std::fabs(this->min), std::fabs(other.min), std::fabs(this->max), std::fabs(other.max)})
            );
        for (double i = 0; i < distrib.size(); ++i) {
            for (double j = 0; j < other.distrib.size(); ++j) {
                double sign;
                if ((min + i) == 0 || (other.min + j) == 0) {
                    sign = 0;
                } else if (((min + i) > 0 && (other.min + j) > 0) || ((min + i) < 0 && (other.min + j) < 0)) {
                    sign = 1;
                } else {
                    sign = -1;
                }
                double key = sign * std::min(std::fabs(min + i), std::fabs(other.min + j));
                double val = distrib[i] * other.distrib[j];
                help.distrib[key - help.min] += val;
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
        size_t ans_idx = 0;
        for (size_t i = 0; i < distrib.size(); ++i) {
            if (distrib[i] > distrib[ans_idx]) ans_idx = i;
        }
        return min + ans_idx;
    }
};
