#include <chrono>
#include <iostream>

#include <lexer/lexer.h>
#include <lexer/token_generator.h>

#include <parser/ast_node.h>
#include <parser/production.h>
#include <parser/production_rule.h>

void endProgram();
std::string fromTestDir(const std::string& fileName);

int main(int argc, char** argv)
{
    using namespace lexer;
    using namespace parser;

    auto lexer = Lexer();

    lexer.addRule({ std::make_unique<IdRegex>(), std::make_unique<IdTokenGenerator>() });
    lexer.addRule({ std::make_unique<IntRegex>(), std::make_unique<IntLitTokenGenerator>() });
    lexer.addRule({ std::make_unique<StringRegex>(), std::make_unique<StringLitTokenGenerator>() });
    lexer.addRule({ std::make_unique<WhitespaceRegex>(), nullptr });

    lexer.addRule({ std::make_unique<KeywordRegex>("("), std::make_unique<LParenTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>(")"),  std::make_unique<RParenTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("{"),  std::make_unique<LCurlyTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("}"),  std::make_unique<RCurlyTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>(","),  std::make_unique<CommaTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("."),  std::make_unique<DotTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>(";"),  std::make_unique<SemiColonTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("+"),  std::make_unique<PlusTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("+="), std::make_unique<PlusEqTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("-"),  std::make_unique<MinusTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("-="), std::make_unique<MinusEqTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("*"),  std::make_unique<TimesTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("*="), std::make_unique<TimesEqTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("/"),  std::make_unique<DivTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("/="), std::make_unique<DivEqTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("="),  std::make_unique<EqualsTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("<"),  std::make_unique<LessTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("<="), std::make_unique<LessEqTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>(">"),  std::make_unique<GreaterTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>(">="), std::make_unique<GreaterEqTokenGenerator>() });
    lexer.addRule({ std::make_unique<KeywordRegex>("|"), std::make_unique<PipeTokenGenerator>() });
    lexer.addRule({ std::make_unique<KeywordRegex>("&"), std::make_unique<AmpersandTokenGenerator>() });
    lexer.addRule({ std::make_unique<KeywordRegex>("||"), std::make_unique<OrTokenGenerator>() });
    lexer.addRule({ std::make_unique<KeywordRegex>("&&"), std::make_unique<AndTokenGenerator>() });

    lexer.addRule({ std::make_unique<KeywordRegex>("if"),    std::make_unique<IfTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("else"),   std::make_unique<ElseTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("while"),  std::make_unique<WhileTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("for"),    std::make_unique<ForTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("int"),    std::make_unique<IntTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("char"),   std::make_unique<CharTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("bool"),   std::make_unique<BoolTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("true"),   std::make_unique<TrueTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("false"),  std::make_unique<FalseTokenGenerator>() });
    lexer.addRule({std::make_unique<KeywordRegex>("return"), std::make_unique<ReturnTokenGenerator>() });

    auto const startTime = std::chrono::system_clock::now();

    auto const tokens = lexer.lex(fromTestDir("small_test.rogue"));

    auto const endTime = std::chrono::system_clock::now();
    auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    auto const newType = makeRule<IntToken>(std::function([](const std::unique_ptr<IntToken>& t)
    {
        return std::make_unique<AstNode>();
    }));

#if 0
    auto const type = makeRule<IntToken, BoolToken, CharToken>();
    auto const varDecl = makeRule<TypeNode, IdentifierToken>();
#endif

    for (auto const& token : tokens)
    {
        std::cout << token->toString() << '\n';
    }

    printf("lexing took %ld ms", duration);

    endProgram();

    return 0;
}

void endProgram()
{
#ifdef ROGUE_PLATFORM_WINDOWS
    std::cin.get();
#endif
}

std::string fromTestDir(const std::string& fileName)
{
#ifdef ROGUE_PLATFORM_WINDOWS
    return "../../../../../" + fileName;
#elif defined(ROGUE_PLATFORM_LINUX)
    return "../" + fileName;
#endif
}
