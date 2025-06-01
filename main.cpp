#include <fstream>
#include <iostream>
#include "markdownparser.h"

int main() {
    std::ifstream ifs;
    ifs.open(R"(D:\Github\md2ast\test.md)", std::ios::in);
    if (!ifs.is_open()) {
        std::cout << "file open failed" << std::endl;
        return -1;
    }

    std::string markdown;
    char c;
    while ((c = ifs.get()) != EOF) {
        markdown += c;
    }

    const auto root = MarkdownParser::toAST(markdown);
    std::cout << root->toHTML() << std::endl;
    return 0;
}
