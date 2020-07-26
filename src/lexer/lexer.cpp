#include "lexer.h"

#include <iostream>
#include <fstream>

//#include "../util/file_io.h"
#include <util/file_io.h>

#include "token.h"

LEXER_NAMESPACE_BEGIN

void Lexer::addRule(Rule&& rule)
{
    rules_.emplace_back(std::move(rule));
}

std::vector<std::unique_ptr<Token>> Lexer::lex(const std::string& fileName)
{
    auto contents = FileIO::readFile(fileName);
    std::cout << contents << std::endl;
    auto fin = std::fstream(fileName);
    auto reader = std::string();
    auto rval = std::vector<std::unique_ptr<Token>>();
    size_t line = 0;
    size_t column = 0;

    while(fin >> reader)
    {
        for(auto const & rule : rules_)
        {
            if(std::regex_match(reader, rule.pattern))
            {
                rval.push_back(rule.generator->generate(line, column, reader));
            }
        }
    }

    return rval;
}

LEXER_NAMESPACE_END