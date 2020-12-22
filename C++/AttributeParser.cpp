/* https://www.hackerrank.com/challenges/attribute-parser/problem */

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
/*
 * 
 * Aman Upadhyay
 * Amity University Kolkata
 *  
*/
enum class TokenType
{
    Invalid = -1,
    LeftAngleBracket = -2,
    RightAngleBracket = -3,
    BackSlash = -4,
    EqualSign = -5,
    Quote = -6,
    Point = -7,
    Tilde = -8,
    Value = -9,
    Identifier = -10
};

struct Token
{
    TokenType type;
    string value;
};
struct ExprAST
{
    virtual ~ExprAST() {}
};

struct AttributeExprAST : public ExprAST
{
    string name;
    string value;

    AttributeExprAST(string &&name, string &&value)
        : name{move(name)}, value{move(value)} {}
};

struct TagBeginExprAst : public ExprAST
{
    string name;
    vector<unique_ptr<AttributeExprAST>> attributes;

    TagBeginExprAst(string &&name)
        : name{move(name)} {}
};

struct TagEndExprAst : public ExprAST
{
    string name;

    TagEndExprAst(string &&name)
        : name{move(name)} {}
};

struct TagExprAST : public ExprAST
{
    unique_ptr<TagBeginExprAst> begin;
    vector<unique_ptr<TagExprAST>> tags;
    unique_ptr<TagEndExprAst> end;
};

struct QueryExprAst : public ExprAST
{
    string name;
    unique_ptr<QueryExprAst> subQuery;
    string attributeName;

    bool hasName() const { return !name.empty(); }
    bool hasAttribute() const { return !attributeName.empty(); }
    bool hasSubQuery() const { return subQuery != nullptr; }

    QueryExprAst(string &&name)
        : name{move(name)}
    {}

    QueryExprAst(string &&name, string &&attributeName)
        : QueryExprAst{move(name)}
    {
        this->attributeName = move(attributeName);
    }
};
static bool isIdentifierChar(const char c)
{
    return isalpha(c) || isdigit(c) || c == '_';
}

static vector<Token> tokenizeInput(const vector<string> &inputStream)
{
    stringstream ss;

    for (const auto &line : inputStream)
        ss << line << "\n";

    const auto input = ss.str();
    const size_t size = input.size();
    size_t pos = 0;

    vector<Token> tokens;

    while (pos < size) {
        const auto lastChar = input[pos];

        if (isspace(lastChar)) {
            pos++;
            continue;
        }

        switch (lastChar) {
            case '<':
                tokens.emplace_back(Token{TokenType::LeftAngleBracket});
                break;
            case '>':
                tokens.emplace_back(Token{TokenType::RightAngleBracket});
                break;
            case '/':
                tokens.emplace_back(Token{TokenType::BackSlash});
                break;
            case '=':
                tokens.emplace_back(Token{TokenType::EqualSign});
                break;
            case '"':
            {
                tokens.emplace_back(Token{TokenType::Quote});

                auto nextPos = pos + 1;
                auto nextChar = input[nextPos];

                while (nextChar != '"')
                    nextChar = input[nextPos++];

                const auto value = input.substr(pos + 1, nextPos - pos - 2);

                if (!value.empty())
                    tokens.emplace_back(Token{TokenType::Value, value});

                tokens.emplace_back(Token{TokenType::Quote});

                pos = nextPos;
                continue;
            }
            case '.':
                tokens.emplace_back(Token{TokenType::Point});
                break;
            case '~':
                tokens.emplace_back(Token{TokenType::Tilde});
                break;
            default:
            {
                if (isIdentifierChar(lastChar)) {
                    auto nextPos = pos;
                    auto nextChar = lastChar;

                    while (isIdentifierChar(nextChar))
                        nextChar = input[nextPos++];

                    const auto identifier = input.substr(pos, nextPos - pos - 1);

                    if (!identifier.empty())
                        tokens.emplace_back(Token{TokenType::Identifier, identifier});

                    pos = nextPos - 1;
                    continue;
                }
            }
        }

        pos++;
    }

    return tokens;
}
static vector<Token> tokenizeQueries(const vector<string> &inputQueryStream)
{
    stringstream ss;

    for (const auto &line : inputQueryStream)
        ss << line << "\n";

    const auto input = ss.str();
    const size_t size = input.size();
    size_t pos = 0;

    vector<Token> tokens;

    while (pos < size) {
        const auto lastChar = input[pos];

        if (isspace(lastChar)) {
            pos++;
            continue;
        }

        switch (lastChar) {
            case '.':
                tokens.emplace_back(Token{TokenType::Point});
                break;
            case '~':
                tokens.emplace_back(Token{TokenType::Tilde});
                break;
            default:
            {
                if (isIdentifierChar(lastChar)) {
                    auto nextPos = pos;
                    auto nextChar = lastChar;

                    while (isIdentifierChar(nextChar))
                        nextChar = input[nextPos++];

                    const auto identifier = input.substr(pos, nextPos - pos - 1);

                    if (!identifier.empty())
                        tokens.emplace_back(Token{TokenType::Identifier, identifier});

                    pos = nextPos - 1;
                    continue;
                }
            }
        }

        pos++;
    }

    return tokens;
}
static vector<Token> tokens;
static size_t currentTokenIndex = 0;
static Token* currentToken;

static vector<unique_ptr<TagExprAST>> tagExpressions;
static vector<unique_ptr<QueryExprAst>> queryExpressions;

static void resetTokens()
{
    tokens.clear();
    currentTokenIndex = 0;
    currentToken = nullptr;
}
static Token* nextToken()
{
    if (currentTokenIndex >= 0 && currentTokenIndex < tokens.size())
        return currentToken = &(tokens[currentTokenIndex++]);

    return nullptr;
}
static Token* peekToken(size_t index)
{
    if (index >= 0 && index < tokens.size())
        return &(tokens[index]);

    return nullptr;
}
static bool isTokenOfType(Token *token, TokenType type)
{
    return token != nullptr && token->type == type;
}
static unique_ptr<AttributeExprAST> parseAttributeExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::Identifier))
        return nullptr;

    auto attributeName = currentToken->value;
    auto token = nextToken();

    if (!isTokenOfType(token, TokenType::EqualSign))
        return nullptr;

    token = nextToken();

    if (!isTokenOfType(token, TokenType::Quote))
        return nullptr;

    token = nextToken();

    if (!isTokenOfType(token, TokenType::Value))
        return nullptr;

    auto attributeValue = token->value;
    token = nextToken();

    if (!isTokenOfType(token, TokenType::Quote))
        return nullptr;

    return make_unique<AttributeExprAST>(move(attributeName), move(attributeValue));
}
static unique_ptr<TagBeginExprAst> parseTagBeginExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::Identifier))
        return nullptr;

    auto tagName = currentToken->value;
    vector<unique_ptr<AttributeExprAST>> attributes;
    auto token = nextToken();
    if (isTokenOfType(token, TokenType::Identifier)) {
        do {
            auto attributeExpr = parseAttributeExpression();

            if (attributeExpr)
                attributes.push_back(move(attributeExpr));

            token = nextToken();
        } while (isTokenOfType(token, TokenType::Identifier));
    }

    if (!isTokenOfType(token, TokenType::RightAngleBracket))
        return nullptr;

    auto tagBeginExpr = make_unique<TagBeginExprAst>(move(tagName));
    tagBeginExpr->attributes = move(attributes);

    return tagBeginExpr;
}
static unique_ptr<TagEndExprAst> parseTagEndExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::Identifier))
        return nullptr;

    auto tagName = currentToken->value;
    auto token = nextToken();

    if (!isTokenOfType(token, TokenType::RightAngleBracket))
        return nullptr;

    return make_unique<TagEndExprAst>(move(tagName));
}
static unique_ptr<TagExprAST> parseTagExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::LeftAngleBracket))
        return nullptr;

    unique_ptr<TagBeginExprAst> begin = nullptr;
    vector<unique_ptr<TagExprAST>> tags;
    unique_ptr<TagEndExprAst> end = nullptr;

    auto token = nextToken();

    if (isTokenOfType(token, TokenType::BackSlash)) {
        nextToken();
        end = parseTagEndExpression();

        if (!end)
            return nullptr;
    } else if (isTokenOfType(token, TokenType::Identifier)) {
        begin = parseTagBeginExpression();

        if (!begin)
            return nullptr;

        token = nextToken();
        auto tokenAfterCurrent = peekToken(currentTokenIndex);
        
        auto tokenAfterCurrentIsNotBackSlash =
            tokenAfterCurrent != nullptr && !isTokenOfType(tokenAfterCurrent, TokenType::BackSlash);

        if (isTokenOfType(token, TokenType::LeftAngleBracket) && tokenAfterCurrentIsNotBackSlash) {
            do {
                auto childTagExpr = parseTagExpression();

                if (childTagExpr)
                    tags.push_back(move(childTagExpr));

                token = nextToken();
                tokenAfterCurrent = peekToken(currentTokenIndex);

                tokenAfterCurrentIsNotBackSlash =
                    tokenAfterCurrent != nullptr && !isTokenOfType(tokenAfterCurrent, TokenType::BackSlash);
            } while (isTokenOfType(token, TokenType::LeftAngleBracket) && tokenAfterCurrentIsNotBackSlash);
        }
        nextToken();
        nextToken();
        end = parseTagEndExpression();

        if (!end)
            return nullptr;
    } else
        return nullptr;

    auto tagExpr = make_unique<TagExprAST>();

    tagExpr->begin = move(begin);
    tagExpr->tags = move(tags);
    tagExpr->end = move(end);

    return tagExpr;
}
static unique_ptr<QueryExprAst> parseSubQueryExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::Identifier))
        return nullptr;

    auto tagName = currentToken->value;
    auto token = peekToken(currentTokenIndex);

    if (isTokenOfType(token, TokenType::Identifier))
        return make_unique<QueryExprAst>(move(tagName));

    token = nextToken();

    string attributeName;
    unique_ptr<QueryExprAst> subQuery;

    if (isTokenOfType(token, TokenType::Tilde)) {
        token = nextToken();

        if (!isTokenOfType(token, TokenType::Identifier))
            return nullptr;

        attributeName = token->value;
        return make_unique<QueryExprAst>(move(tagName), move(attributeName));
    } else if (isTokenOfType(token, TokenType::Point)) {
        nextToken();
        subQuery = parseSubQueryExpression();

        auto queryExpr = make_unique<QueryExprAst>(move(tagName));

        if (subQuery)
            queryExpr->subQuery = move(subQuery);

        return queryExpr;
    }

    return nullptr;
}
static unique_ptr<QueryExprAst> parseQueryExpression()
{
    if (!currentToken)
        return nullptr;

    if (!isTokenOfType(currentToken, TokenType::Identifier))
        return nullptr;

    auto tagName = currentToken->value;
    auto token = nextToken();

    string attributeName;
    unique_ptr<QueryExprAst> subQuery;

    if (isTokenOfType(token, TokenType::Tilde)) {
        token = nextToken();

        if (!isTokenOfType(token, TokenType::Identifier))
            return nullptr;

        attributeName = token->value;
        return make_unique<QueryExprAst>(move(tagName), move(attributeName));
    } else if (isTokenOfType(token, TokenType::Point)) {
        nextToken();
        subQuery = parseSubQueryExpression();
        
        auto queryExpr = make_unique<QueryExprAst>(move(tagName));

        if (subQuery)
            queryExpr->subQuery = move(subQuery);

        return queryExpr;
    }

    return make_unique<QueryExprAst>(move(tagName));
}
static void parseLines(const vector<string> &lines)
{
    if (lines.empty())
        return;

    tokens = tokenizeInput(lines);

    do {
        nextToken();
        auto tagExpr = parseTagExpression();

        if (tagExpr)
            tagExpressions.push_back(move(tagExpr));
    } while (currentTokenIndex < tokens.size());

    resetTokens();
}
static void parseQueries(const vector<string> &queries)
{
    if (queries.empty())
        return;

    tokens = tokenizeQueries(queries);

    do {
        nextToken();
        auto queryExpr = parseQueryExpression();

        if (queryExpr)
            queryExpressions.push_back(move(queryExpr));
    } while (currentTokenIndex < tokens.size());

    resetTokens();
}
static vector<string> buildSearchPath(const unique_ptr<QueryExprAst> &queryExpr)
{
    if (tagExpressions.empty() || queryExpr == nullptr || !queryExpr->hasName())
        return {};

    vector<string> path;
    path.push_back(queryExpr->name);

    if (queryExpr->hasSubQuery()) {
        auto subQuery = queryExpr->subQuery.get();

        while (subQuery && subQuery->hasName()) {
            path.push_back(subQuery->name);

            if (!subQuery->hasSubQuery())
                break;

            subQuery = subQuery->subQuery.get();
        }

        if (subQuery && !subQuery->hasAttribute())
            return {};

        path.push_back(subQuery->attributeName);
    } else if (queryExpr->hasAttribute())
        path.push_back(queryExpr->attributeName);

    return path;
}
static void lookupQuery(const unique_ptr<QueryExprAst> &queryExpr)
{
    auto outputNotFound = [] { cout << "Not Found!\n"; };
    const auto path = buildSearchPath(queryExpr);

    if (path.empty() || path.size() == 1) {
        outputNotFound();
        return;
    }
    const auto it = find_if(cbegin(tagExpressions), cend(tagExpressions),
                            [&path](const auto &tagExpr) {
                                return tagExpr && tagExpr->begin->name == path[0];
                            });

    if (it != cend(tagExpressions)) {
        auto tag = it->get();

        if (tag->tags.empty() && tag->begin->attributes.empty())
            outputNotFound();

        for (size_t i = 1; i < path.size(); i++) {
            if (i == path.size() - 1) {
                const auto &attributes = tag->begin->attributes;
                
                if (attributes.empty()) {
                    outputNotFound();
                    break;
                }
                const auto &subPath = path[i];

                const auto attrIt = find_if(cbegin(attributes), cend(attributes),
                                            [&subPath](const auto &attrExpr) {
                                                return attrExpr && attrExpr->name == subPath;
                                            });

                if (attrIt != cend(attributes))
                    cout << (*attrIt)->value << "\n";
                else
                    outputNotFound();

                break;
            }
            const auto &childTags = tag->tags;
            const auto &subPath = path[i];

            const auto tagIt = find_if(cbegin(childTags), cend(childTags),
                                       [&subPath](const auto &tagExpr) {
                                           return tagExpr && tagExpr->begin->name == subPath;
                                       });

            if (tagIt != cend(childTags)) {
                tag = tagIt->get();
                continue;
            } else {
                outputNotFound();
                break;
            }
        }
    } else
        outputNotFound();
}
static void search()
{
    if (queryExpressions.empty())
        return;

    for (const auto &queryExpr : queryExpressions) {
        lookupQuery(queryExpr);
    }
}
int main()
{
    int n{}, q{};
    cin >> n >> q;

    vector<string> lines;
    vector<string> queries;

    for (int i = 0; i <= n; i++) {
        string line;
        getline(cin, line);
        lines.push_back(line);
    }
    for (int j = 0; j <= q; j++) {
        string query;
        getline(cin, query);
        queries.push_back(query);
    }
    parseLines(lines);
    parseQueries(queries);
    search();
    return 0;
}
