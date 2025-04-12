#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <vector>

/*
A simple implementaion of sorting Future Symbol by Settlement Day at Taifex
Encode Rules:
https://www.taifex.com.tw/file/taifex/CHINESE/11/TechDocs/4/%E6%9C%9F%E4%BA%A4%E6%89%80TCPIP_TMP_v2.18.5.pdf
Appendix 3.5
*/

template <typename T>
void PrintSet(T& set) {
  for (auto s : set) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}

int main() {
  // Test Case doesn`t reflect the real situation. Only at most 6 different
  // delivery months of a product on market simultaneously. Current month, +1,
  // +2, +5, +8 and +11

  // std::vector<std::string> future_list{"TXFG0", "TXFD0", "TXFA0", "TXFL9",
  //                                      "TXFJ9", "TXFK9", "TXFH0"};
  std::vector<std::string> future_list{"TXFG4", "TXFL3", "TXFA3",
                                       "TXFD4", "TXFH4", "TXFG3"};

  auto cmp = [](std::string lhs, std::string rhs) {
    auto lhs_size = lhs.size();
    auto rhs_size = rhs.size();

    if (lhs[lhs_size - 1] == rhs[rhs_size - 1]) {
      return lhs[lhs_size - 2] < rhs[rhs_size - 2];
    }

    if (abs(lhs[lhs_size - 1] - rhs[rhs_size - 1]) == 1) {
      return (lhs[lhs_size - 1] < rhs[rhs_size - 1]);
    }

    return lhs[lhs_size - 1] > rhs[lhs_size - 1];
  };

  std::set<std::string, decltype(cmp)> sorted_set(future_list.begin(),
                                                  future_list.end(), cmp);

  PrintSet(sorted_set);
}
