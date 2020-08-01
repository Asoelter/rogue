#include "lexer.h"

#include <util/file_io.h>

#include "token.h"

LEXER_NAMESPACE_BEGIN

void Lexer::addRule(Rule&& rule)
{
    rules_.emplace_back(std::move(rule));
}

std::vector<std::unique_ptr<Token>> Lexer::lex(const std::string& fileName)
{
    auto contents          = FileIO::readFile(fileName);
    const char* chunkStart = &contents[0];
    const char* chunkStop  = &contents[0];
    auto const lastIndex   = contents.size() - 1;
    const char* end        = &contents[lastIndex];
    size_t line            = 0;
    size_t column          = 0;
    auto rval              = std::vector<std::unique_ptr<Token>>();

    resetActiveRules();

    while (chunkStart <= end)
    {
        updateLineAndColumn(*chunkStart, line, column);
        updateActiveRules(*chunkStop);

        if(activeRules_.empty())
        {
            auto* lastActiveRule = rejectedRules_.top();

            if (lastActiveRule && lastActiveRule->generator)
            {
                rval.push_back(lastActiveRule->generator->generate(line, column, std::string(chunkStart, chunkStop)));
            }

            chunkStart = chunkStop;

            resetActiveRules();
        }
        else
        {
            ++chunkStop;
        }
    }

    return rval;
}

void Lexer::resetActiveRules()
{
    for(auto & rule : rules_)
    {
        rule.pattern->reset();
        activeRules_.insert(&rule);
    }
}

void Lexer::updateActiveRules(char c)
{
    for(auto it = activeRules_.begin(); it != activeRules_.end();)
    {
        auto oldIt = it;
        ++it;

        const auto status = (*oldIt)->pattern->on(c);

        if(status == RegexStatus::Rejected)
        {
            rejectedRules_.push(*oldIt);
            activeRules_.erase(oldIt);
        }
    }
}

void Lexer::updateLineAndColumn(char c, size_t& line, size_t& column)
{
    switch (c)
    {
    case '\t': 
    {
        column += 8;
    } break;
    case '\n':
    {
        line += 1;
        column = 0;
    } break;
    default:
    {
        column += 1;
    } break;
    }
}

LEXER_NAMESPACE_END