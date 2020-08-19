#include "lexer.h"

#include <iostream>

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
    auto result              = std::vector<std::unique_ptr<Token>>();
    auto aRuleHasAccepted  = false;

    resetActiveRules();

    while (chunkStart <= end)
    {
        updateLineAndColumn(*chunkStart, line, column);
        aRuleHasAccepted = updateActiveRules(*chunkStop) || aRuleHasAccepted;

        if(activeRules_.empty())
        {
            if (!aRuleHasAccepted)
            {
                std::cout << "[" << line << ", " << column 
                          << "] Unable to parse string: " 
                          << std::string(chunkStart, chunkStop) << std::endl;
                break;
            }
            auto* lastActiveRule = rejectedRules_.top();

            if (lastActiveRule && lastActiveRule->generator)
            {
                result.push_back(lastActiveRule->generator->generate(line, column, std::string(chunkStart, chunkStop)));
            }

            chunkStart = chunkStop;

            resetActiveRules();
            aRuleHasAccepted = false;
        }
        else
        {
            ++chunkStop;
        }
    }

    return result;
}

void Lexer::resetActiveRules()
{
    for(auto & rule : rules_)
    {
        rule.pattern->reset();
        activeRules_.insert(&rule);
    }
}

bool Lexer::updateActiveRules(char c)
{
    bool ruleHasAccepted = false;

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
        else if(status == RegexStatus::Accepted)
        {
            ruleHasAccepted = true;
        }
    }

    return ruleHasAccepted;
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