class Test {
 public:
  Test() {}
  Test(const Test& other) = default;
};

int main() {
  Test test;
  return 0;
}