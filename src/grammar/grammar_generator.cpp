#include "grammar_generator.h"

USE_LEXER_NAMESPACE

struct AssignToken final : public Token
{
    AssignToken(size_t line, size_t column) : Token(line, column) {}

    [[nodiscard]]
    type_id type() const override
    {
        return TypeId<AssignToken>;
    }

    [[nodiscard]]
    std::string toString() const override
    {
        return "::=";
    }
};

class AssignTokenGenerator final : public TokenGenerator
{
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& /*value*/) override
    {
        return std::make_unique<AssignToken>(line, column);
    }

    std::unique_ptr<Token> generate(size_t line, size_t column, std::string&& /*value*/) override
    {
        return std::make_unique<AssignToken>(line, column);
    }
};

GrammarGenerator::GrammarGenerator()
{
    lexer_.addRule({ std::make_unique<IdRegex>(), std::make_unique<IdTokenGenerator>() });
    lexer_.addRule({ std::make_unique<KeywordRegex>("::="), std::make_unique<AssignTokenGenerator>() });
    lexer_.addRule({ std::make_unique<WhitespaceRegex>(), nullptr });
    lexer_.addRule({std::make_unique<KeywordRegex>(";"),  std::make_unique<SemiColonTokenGenerator>() });
    lexer_.addRule({ std::make_unique<KeywordRegex>("|"), std::make_unique<PipeTokenGenerator>() });
}

void GrammarGenerator::readSpec(const std::string& specFileName)
{
    auto const tokens = lexer_.lex(specFileName);
}
