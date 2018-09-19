#include <cstdio>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

struct MyString {
    char* data;
    size_t size;
};

size_t GetFileSize(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        printf("Invalid filename\n");
        exit(1);
    }
    return st.st_size;
}

MyString readText(const char* filename) {
    size_t file_size = GetFileSize(filename);
    char* data = static_cast<char*>(malloc(file_size));
    read(open(filename, O_RDONLY), data, file_size);
    return {data, file_size};
}

std::vector<MyString> BuildLinesVector(MyString* text) {
    std::vector<MyString> lines;
    char* last = text->data;
    for (char* ptr = text->data; ptr != text->data + text->size; ++ptr) {
        if (*ptr == '\n') {
            *ptr = 0;
            lines.push_back({last, static_cast<size_t>(ptr - last)});
            last = ptr + 1;
        }
    }
    return lines;
}

const int LINES_IN_VERSUS = 14;
const std::set<int> FEMININE_LINES_NUMBERS = {0, 2, 4, 5, 8, 11};
const std::map<int, int> RHYMES = {{0, 2}, {4, 5}, {8, 11}, {1, 3}, {6, 7}, {9, 10}, {12, 13}};

std::pair<std::vector<MyString>, std::vector<MyString>> SeparateToFeminineAndMasculineLines(const std::vector<MyString>& lines) {
    std::vector<MyString> feminine_lines;
    std::vector<MyString> masculine_lines;
    feminine_lines.reserve(lines.size() * FEMININE_LINES_NUMBERS.size() / LINES_IN_VERSUS);
    masculine_lines.reserve(lines.size() - feminine_lines.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        if (FEMININE_LINES_NUMBERS.count(i % LINES_IN_VERSUS)) {
            feminine_lines.push_back(lines[i]);
        } else {
            masculine_lines.push_back(lines[i]);
        }
    }
    return {feminine_lines, masculine_lines};
}

std::vector<MyString> BuildVersus(const std::vector<MyString>& feminine_lines, const std::vector<MyString>& masculine_lines) {
    std::vector<MyString> versus(feminine_lines.size() + masculine_lines.size(), {nullptr, 0});
    for (int i = 0; i < versus.size(); ++i) {
        if (!RHYMES.count(i % LINES_IN_VERSUS)) {
            continue;
        }
        const auto& lines = FEMININE_LINES_NUMBERS.count(i % LINES_IN_VERSUS) ? feminine_lines : masculine_lines;
        int line = (rand() % (lines.size() / 2)) * 2;
        versus[i] = lines[line];
        versus[RHYMES.at(i % LINES_IN_VERSUS) + i - i % LINES_IN_VERSUS] = lines[line + 1];
    }
    return versus;
}

struct {
    bool operator()(const MyString& first, const MyString& second) const {
        const char MIN_LETTER = 192, MAX_LETTER = 255;
        size_t pos1 = first.size - 1;
        size_t pos2 = second.size - 1;
        while (pos1 + 1 != 0 || pos2 + 1 != 0) {
            if (first.data[pos1] < MIN_LETTER || first.data[pos1] > MAX_LETTER) {
                --pos1;
                continue;
            }
            if (second.data[pos2] < MIN_LETTER || second.data[pos2] > MAX_LETTER) {
                --pos2;
                continue;
            }
            if (first.data[pos1] < second.data[pos2]) {
                return true;
            }
            if (first.data[pos1] > second.data[pos2]) {
                return false;
            }
            --pos1, --pos2;
        }
        return first.size < second.size;
    }
} compareFromEnd;

std::vector<MyString> GenerateRubbish(MyString* text) {
    std::vector<MyString> lines = BuildLinesVector(text);
    auto [feminine_lines, masculine_lines] = SeparateToFeminineAndMasculineLines(lines);
    
    std::sort(feminine_lines.begin(), feminine_lines.end(), compareFromEnd);
    std::sort(masculine_lines.begin(), masculine_lines.end(), compareFromEnd);
    
    std::vector<MyString> rubbish = BuildVersus(feminine_lines, masculine_lines);
    return rubbish;
}

int main() {
    MyString text = readText("text.txt");
    std::vector<MyString> rubbish = GenerateRubbish(&text);
    for (const MyString& str : rubbish) {
        printf("%s\n", str.data);
    }
    return 0;
}
