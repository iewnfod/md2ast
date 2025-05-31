#ifndef ASTNODE_H
#define ASTNODE_H
#include <sstream>
#include <string>
#include <vector>

enum ASTNodeType {
	DOCUMENT,
	H1_TITLE,
	H2_TITLE,
	H3_TITLE,
	H4_TITLE,
	H5_TITLE,
	H6_TITLE,
	PARAGRAPH,
	BOLD,
	ITALIC,
	BOLDITALIC,
	QUOTE,
	LIST,
	ORDERED_LIST,
	UNORDERED_LIST,
	CODEBLOCK,
	INLINECODE,
	IMAGE,
	BR,
	LINK,
	LATEX,
	TEXT,
	UNKNOWN_NODE
};

class ASTNode {
public:
	ASTNode();
	~ASTNode() = default;
	[[nodiscard]] ASTNodeType getASTNodeType() const;
	void setNodeType(ASTNodeType nodeType);
	void setContent(const char* content);
	void setContent(const std::string& content);
	void addChild(ASTNode* child);
	void setLevel(int level);
	void setLang(const char* lang);
	void setLang(const std::string &lang);
	[[nodiscard]] ASTNode* getParent() const;

	std::string toHTML() const;

private:
	ASTNodeType nodeType;
	std::string content{};
	std::string lang{};
	int level{};
	struct ASTNode* parent{};

	[[nodiscard]] std::string children2HTML() const;

	std::vector<ASTNode*> children{};
};

#endif
