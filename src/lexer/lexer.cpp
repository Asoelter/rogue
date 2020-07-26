#include "lexer.h"

#include <util/file_io.h>

#include "token.h"

LEXER_NAMESPACE_BEGIN

void Lexer::addRule(Rule&& rule)
{
    rules_.emplace_back(std::move(rule));
}

#ifdef USE_CUSTOM_REGEX
std::vector<std::unique_ptr<Token>> Lexer::lex(const std::string& fileName)
{
    
    auto contents = FileIO::readFile(fileName);
    const char* chunkStart = &contents[0];
    const char* chunkStop = &contents[0];
    auto rval = std::vector<std::unique_ptr<Token>>();

    for(auto & rule : rules_)
    {
        activeRules_.insert(&rule);
    }

    while (*chunkStop != '\0')
    {
        ++chunkStop;

        for(auto it = activeRules_.begin(); it != activeRules_.end();)
        {
            auto oldIt = it;
            ++it;

            const auto status = (*oldIt)->pattern->on(*chunkStop);

           if(status == RegexStatus::Rejected)
           {
               rejectedRules_.push(*oldIt);
               activeRules_.erase(oldIt);
           }
        }

        if(activeRules_.empty())
        {
            auto lastActiveRule = rejectedRules_.top();
            rval.push_back(lastActiveRule->generator->generate(0, 0, std::string(chunkStart, chunkStop)));
            chunkStart = chunkStop;

            for(auto & rule : rules_)
            {
                rule.pattern->reset();
                activeRules_.insert(&rule);
            }
        }
    }

    return rval;
}
#else
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
            matches_.clear();
        }
    }

    return rval;
}
#endif

LEXER_NAMESPACE_END