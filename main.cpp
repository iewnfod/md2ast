#include <iostream>
#include "markdownparser.h"

int main() {
    auto markdown = "# Hello World\n## World 1\n`int a = 1;`\n```python\nprint('Hello World')\n```";
    auto root = MarkdownParser::toAST(markdown);
    std::cout << root->toHTML() << std::endl;
    return 0;
}
