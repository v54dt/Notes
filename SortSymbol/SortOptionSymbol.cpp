#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::vector<std::string> option_list{"TXO03900A5", "TXO24400A5", "TXO19800A5",
                                       "TXO18500A5", "TXO22000A5"};

  auto cmp = [](std::string_view lhs, std::string_view rhs) {
    return lhs.substr(size_t(3), size_t(5)) < rhs.substr(size_t(3), size_t(5));
  };

  std::set<std::string, decltype(cmp)> sorted_set(option_list.begin(),
                                                  option_list.end(), cmp);

  for (auto s : sorted_set) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}