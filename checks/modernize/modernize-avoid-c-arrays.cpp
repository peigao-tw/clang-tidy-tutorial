int a[] = {1, 2}; // warning: do not declare C-style arrays, use std::array<> instead

int b[1]; // warning: do not declare C-style arrays, use std::array<> instead

void foo() {
  int c[b[0]]; // warning: do not declare C VLA arrays, use std::vector<> instead
}

template <typename T, int Size>
class array {
  T d[Size]; // warning: do not declare C-style arrays, use std::array<> instead

  int e[1]; // warning: do not declare C-style arrays, use std::array<> instead
};

array<int[4], 2> d; // warning: do not declare C-style arrays, use std::array<> instead

using k = int[4]; // warning: do not declare C-style arrays, use std::array<> instead
