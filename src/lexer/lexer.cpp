#include "lexer.h"

#include <iostream>
#include <fstream>
#include <string_view>

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
    const char* chunkStart = &contents[0];
    const char* chunkStop = &contents[0];
    auto rval = std::vector<std::unique_ptr<Token>>();

    while (*chunkStop != '\0')
    {
        int numMatches = 0;
        ++chunkStop;
        bool first = true;

        for (auto& rule : rules_)
        {
            if (std::regex_match(chunkStart, chunkStop, rule.pattern))
            {
                if (first)
                {
                    //only clear matches when we
                    //know more are coming
                    matches_.clear();
                }

                matches_.push_back(&rule);
                ++numMatches;
            }
        }

        if (numMatches == 0 && !matches_.empty())
        {
            auto lastMatch = matches_.front();

            if (lastMatch->generator)
            {
                rval.push_back(lastMatch->generator->generate(0, 0, std::string(chunkStart, chunkStop - 1)));
            }

            chunkStop -= 1; //rewind to include first non-match in the next chunk
            chunkStart = chunkStop;
            numMatches = 0;
            matches_.clear();
        }
    }

    return rval;
}

LEXER_NAMESPACE_END