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

    [[nodiscard]]
    std::string toPlaneString() const override
    {
        return toString();
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
    const auto tokens = lexer_.lex(specFileName);
    auto onLhs = true ;
    ProductionRule currentRule;

    for(auto const & token : tokens)
    {
        if(token->type() == TypeId<AssignToken>)
        {
            onLhs = false;
        }
        else if(token->toPlaneString() == "End")
        {
            onLhs = true;
        }
        else if(token->toPlaneString() == "|")
        {
            //Add new rule to production
        }

       if(onLhs)
       {
           //1. if the token is an assign token, switch onLhs to false, move to the else clause
           //2. get the string from the token, use that to get a type id from the id table
           //3. create a new production rule (after creating the idea of production rules
       }
       else
       {
           //1. if the previous token and this token were id's switch onLhs to true, move to the if clause in some way
           //2. verify that a production rule has been created (from the else branch)
           //3. get the id of the type represented by the current string (from the id table)
           //4. add that id to the current production rule
       }
    }
}
