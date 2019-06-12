#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
    std::unordered_map<char, int> letterChars;
    for (const auto &c : letter_text) {
        letterChars[c] += 1;
    }

    for (const auto &c : magazine_text) {
        // Find this character
        auto search = letterChars.find(c);
        if (search != letterChars.end()) {
            // decrement this count
            search->second--;
            // If this is equal to 0 now, remove it from the map
            if (search->second == 0) {
                letterChars.erase(c);
            }
        }

        if (letterChars.empty()) {
            return true;
        }
    }

    return letterChars.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
