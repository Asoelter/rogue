#include <cassert>
#include <iostream>

#include <lexer/lexer.h>
#include <lexer/token_generator.h>

#include <util/file_io.h>

int main(int argc, char** argv)
{
    auto const idPattern = "[a-z]([a-z]|[0-9])*";
    auto const intPattern = "0|([1-9][0-9]*)";
    auto const newlinePattern = "\r\n";
    auto const whitespacePattern = " |\t|\n|\r\n";

    auto const LParenPattern = "\\(";
    auto const RParenPattern = "\\)";
    auto const LCurlyPattern = "\\{";
    auto const RCurlyPattern = "\\}";
    auto const CommaPattern = ",";
    auto const DotPattern = "\\.";
    auto const SemiColonPattern = ";";
    auto const PlusPattern = "\\+";
    auto const PlusEqPattern = "\\+=";
    auto const MinusPattern = "-";
    auto const MinusEqPattern = "-=";
    auto const TimesPattern = "\\*";
    auto const TimesEqPattern = "\\*=";
    auto const DivPattern = "/";
    auto const DivEqPattern = "/=";
    auto const EqualsPattern = "=";
    auto const LessPattern = "<";
    auto const LessEqPattern = "<=";
    auto const GreaterPattern = ">";
    auto const GreaterEqPattern = ">=";

    auto lexer = lexer::Lexer();

    assert(std::regex_match("hello", std::regex(idPattern)));

    try
    {
        lexer.addRule({ idPattern, std::make_unique<lexer::IdTokenGenerator>() });
        lexer.addRule({ intPattern, std::make_unique<lexer::IntLitTokenGenerator>() });
        lexer.addRule({ whitespacePattern, nullptr });
        lexer.addRule({ newlinePattern, std::make_unique<lexer::StringLitTokenGenerator>() });
        lexer.addRule({ LParenPattern, std::make_unique<lexer::LParenTokenGenerator>() });
        lexer.addRule({ RParenPattern, std::make_unique<lexer::RParenTokenGenerator>() });
        lexer.addRule({ LCurlyPattern, std::make_unique<lexer::LCurlyTokenGenerator>() });
        lexer.addRule({ RCurlyPattern, std::make_unique<lexer::RCurlyTokenGenerator>() });
        lexer.addRule({ CommaPattern, std::make_unique<lexer::CommaTokenGenerator>() });
        lexer.addRule({ DotPattern , std::make_unique<lexer::DotTokenGenerator>() });
        lexer.addRule({ SemiColonPattern , std::make_unique<lexer::SemiColonTokenGenerator>() });
        lexer.addRule({ PlusPattern , std::make_unique<lexer::PlusTokenGenerator>() });
        lexer.addRule({ PlusEqPattern , std::make_unique<lexer::PlusEqTokenGenerator>() });
        lexer.addRule({ MinusPattern , std::make_unique<lexer::MinusTokenGenerator>() });
        lexer.addRule({ MinusEqPattern , std::make_unique<lexer::MinusEqTokenGenerator>() });
        lexer.addRule({ TimesPattern , std::make_unique<lexer::TimesTokenGenerator>() });
        lexer.addRule({ TimesEqPattern , std::make_unique<lexer::TimesEqTokenGenerator>() });
        lexer.addRule({ DivPattern , std::make_unique<lexer::DivTokenGenerator>() });
        lexer.addRule({ DivEqPattern , std::make_unique<lexer::DivEqTokenGenerator>() });
        lexer.addRule({ EqualsPattern , std::make_unique<lexer::EqualsTokenGenerator>() });
        lexer.addRule({ LessPattern , std::make_unique<lexer::LessTokenGenerator>() });
        lexer.addRule({ LessEqPattern , std::make_unique<lexer::LessEqTokenGenerator>() });
        lexer.addRule({ GreaterPattern , std::make_unique<lexer::GreaterTokenGenerator>() });
        lexer.addRule({ GreaterEqPattern , std::make_unique<lexer::GreaterEqTokenGenerator>() });
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }

    auto const tokens = lexer.lex("../../../../test.rogue");

    for (auto const& token : tokens)
    {
        std::cout << token->toString() << ' ';
    }

    std::cin.get();
    return 0;
}