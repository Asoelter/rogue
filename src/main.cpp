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
    auto const DotToken = "\\.";
    auto const SemiColonToken = ";";
    auto const PlusToken = "\\+";
    auto const MinusToken = "-";
    auto const EqualsToken = "=";

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
        lexer.addRule({ DotToken, std::make_unique<lexer::DotTokenGenerator>() });
        lexer.addRule({ SemiColonToken, std::make_unique<lexer::SemiColonTokenGenerator>() });
        lexer.addRule({ PlusToken, std::make_unique<lexer::PlusTokenGenerator>() });
        lexer.addRule({ MinusToken, std::make_unique<lexer::MinusTokenGenerator>() });
        lexer.addRule({ EqualsToken, std::make_unique<lexer::EqualsTokenGenerator>() });
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }

    auto const tokens = lexer.lex("../../../../test.rogue");

    for(auto const & token : tokens)
    {
        std::cout << token->toString() << ' ';
    }

    std::cin.get();
    return 0;
}