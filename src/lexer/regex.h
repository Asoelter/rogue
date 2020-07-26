#ifndef REGEX_H
#define REGEX_H

#include <string>

enum class RegexStatus
{
    NotStarted,
    Rejected,
    Continuing,
    Accepted
};

class Regex
{
public:
    Regex();
    virtual ~Regex() = default;

    virtual RegexStatus on(char value) = 0;
    RegexStatus status() const noexcept;
    virtual void reset() noexcept;

protected:
    RegexStatus status_;
};

class IdRegex : public Regex
{
public:
    IdRegex();

    RegexStatus on(char value) override;
};

class IntRegex : public Regex
{
public:
    IntRegex();

    RegexStatus on(char value) override;
};

class WhitespaceRegex : public Regex
{
public:
    WhitespaceRegex();

    RegexStatus on(char value) override;

private:
    char lastChar_;
};

class StringRegex : public Regex
{
public: 
    StringRegex(std::string value);

    RegexStatus on(char value) override;
    void reset() noexcept override;

private:
    std::string value_;
    unsigned expectedIndex_;
};

#endif //REGEX_H
