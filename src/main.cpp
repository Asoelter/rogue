#include <cassert>
#include <iostream>

#include <lexer/lexer.h>
#include <lexer/token_generator.h>

#include <util/file_io.h>

struct newlineGenerator : public lexer::TokenGenerator
{
    std::unique_ptr<lexer::Token> generate(size_t line, size_t column, const std::string& /*value*/) override
    {
        return std::make_unique<lexer::IdentifierToken>(line, column, "newline");
    }
};

int main(int argc, char** argv)
{
    const auto contents = FileIO::readFile("../../../../test.rogue");
    std::cout << contents[0] << std::endl;
    std::cin.get();
#if 0
    auto const idPattern = "[a-z]([a-z]|[0-9])*";
    auto const intPattern = "0|([1-9][0-9]*)";
    auto const newlinePattern = "\n";

    auto lexer = lexer::Lexer();

    assert(std::regex_match("hello", std::regex(idPattern)));

    lexer.addRule({ idPattern, std::make_unique<lexer::IdTokenGenerator>() });
    lexer.addRule({ intPattern, std::make_unique<lexer::IntLitTokenGenerator>() });
    lexer.addRule({ newlinePattern, std::make_unique<newlineGenerator>() });

    auto const tokens = lexer.lex("../../../../test.rogue");

    for(auto const & token : tokens)
    {
        std::cout << token->toString();
    }

    std::cin.get();
#endif
    return 0;
}