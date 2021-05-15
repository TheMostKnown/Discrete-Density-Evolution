#include "discrete_val.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <time.h>

// check matrix 4/6
static std::vector<std::vector<int>> H = {
  {1, 1, 0, 1, 0, 0},
  {0, 1, 1, 0, 1, 0},
  {1, 0, 0, 0, 1, 1},
  {0, 0, 1, 1, 0, 1}
  };


static std::vector<std::vector<int>> A;
// make an A vector showing the row indexes of '1' in H columns (vertical idx)
void construct_A() {
  A = {};
  for (size_t j = 0; j < H[0].size(); ++j) {
    std::vector<int> help = {};
    for (size_t i = 0; i < H.size(); ++i) {
      if (H[i][j] == 1) help.push_back(i);
    }
    A.push_back(help);
  }
}

static std::vector<std::vector<int>> B;
// make a B vector showing the column indexes of '1' in H rows (horizontal idx)
void construct_B() {
  B = {};
  for (size_t i = 0; i < H.size(); ++i) {
    std::vector<int> help = {};
    for (size_t j = 0; j < H[0].size(); ++j) {
      if (H[i][j] == 1) help.push_back(j);
    }
    B.push_back(help);
  }
}


// channel probability
static const float CHANNEL_PROB = 0.2;

// size of the input message
static const size_t MESSAGE_SIZE = 6;

// input llr
static std::vector<discrete_value> r;

// make llr out of input message
void construct_r(const std::vector<int>& input) {
  r = {};
  std::vector<double> fr = std::vector<double>(MESSAGE_SIZE, 0);
  for (size_t i = 0; i < fr.size(); ++i) {
    fr[i] = log(CHANNEL_PROB/(1 - CHANNEL_PROB));
    if (input[i] == 0) {
      fr[i] = -fr[i];
    }
  }
  for (size_t i = 0; i < MESSAGE_SIZE; ++i) {
    std::vector<double> help_vec(1);
    help_vec[0] = 1;
    discrete_value help(help_vec, fr[i], fr[i]);
    r.push_back(help);
  }
}

// define a M matrix
static std::vector<std::vector<discrete_value>> M  = std::vector<std::vector<discrete_value>>(4, std::vector<discrete_value>(6));

//make start M matrix out of input llr
void construct_M() {
  for (size_t j = 0; j < M.size(); ++j) {
    for (size_t i = 0; i < M[0].size(); ++i) {
      for (size_t k = 0; k < A[0].size(); ++k) {
        if (A[i][k] == j) {
          M[j][i] = r[i];
          break;
        }
      }
    }
  }
}

// define E matrix
static std::vector<std::vector<discrete_value>> E  = std::vector<std::vector<discrete_value>>(4, std::vector<discrete_value>(6));

// prints a given matrix of a discrete_values
void print_discrete_matrix(std::vector<std::vector<discrete_value>> matrix){
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      std::cout << i << " " << j << ":\t";
      matrix[i][j].print();
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}

void make_M() {
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[0].size(); ++j) {
      discrete_value help;
      for (size_t k = 0; k < A[0].size(); ++k) {
        if (k != j) {
          if (help.is_empty()) {
            help = E[A[i][k]][i];
          } else {
            help = help.sum_distrib(E[A[i][k]][i]);
          }
        }
      }
      M[A[i][j]][i] = help.sum_distrib(r[i]);
    }
  }
}

// makes an E matrix out of current M matrix
void make_E() {
  for (size_t i = 0; i < B.size(); ++i) {
    for (size_t j = 0; j < B[0].size(); ++j) {
      discrete_value help;
      for (size_t k = 0; k < B[0].size(); ++k) {
        if (k != j) {
          if (help.is_empty()) {
            help = M[i][B[i][k]];
          } else {
            help = help.signed_min_abs_distrib(M[i][B[i][k]]);
          }
        }
      }
      E[i][B[i][j]] = help;
    }
  }
}

void print_usual_matrix(std::vector<std::vector<int>> matrix) {
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

void init(std::vector<int> message) {
  construct_A();
  construct_B();
  construct_r(message);
  construct_M();
}

std::vector<int> get_output() {
  std::vector<int> ans;
  for (size_t j = 0; j < E[0].size(); ++j) {
    double sum = 0;
    for (size_t i = 0; i < E.size(); ++i) {
      sum += E[i][j].get_val();
    }
    if (sum + r[j].get_val() < 0) {
      ans.push_back(1);
    } else {
      ans.push_back(0);
    }
  }
  
  return ans;
}

int main() {
  clock_t start = clock();
  int ITERATIONS_NUM = 64;
  std::vector<int> input = {1, 0, 1, 0, 1, 1};
  init(input);

  for (int i = 0; i < ITERATIONS_NUM; ++i) {
    make_E();
    make_M();
  }

  make_E();

  std::vector<int> ans = get_output();
  for (size_t i = 0; i < MESSAGE_SIZE; ++i) {
    std::cout << ans[i] << " ";
  }
  std::cout << "\n";
  clock_t end = clock();
  std::cout << "Time spent on " << ITERATIONS_NUM << " iterations: " << (double) (end - start)/ CLOCKS_PER_SEC << " seconds\n";

  return 0;
}
