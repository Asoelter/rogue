#ifndef REGEX_H
#define REGEX_H

#include <string>

enum class RegexStatus : uint8_t
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
    Regex(const Regex&) = default;
    Regex(Regex&&) = default;
    virtual ~Regex() = default;

    Regex& operator=(const Regex&) = default;
    Regex& operator=(Regex&&) = default;

    virtual RegexStatus on(char value) = 0;
    [[nodiscard]] RegexStatus status() const noexcept;
    virtual void reset() noexcept;

protected:
    RegexStatus status_;
};

class IdRegex final : public Regex
{
public:
    IdRegex();

    RegexStatus on(char value) override;
};

class IntRegex final : public Regex
{
public:
    IntRegex();

    RegexStatus on(char value) override;
};

class WhitespaceRegex final : public Regex
{
public:
    WhitespaceRegex();

    RegexStatus on(char value) override;
};

class KeywordRegex final : public Regex
{
public: 
    KeywordRegex(std::string value);

    RegexStatus on(char value) override;
    void reset() noexcept override;

private:
    std::string value_;
    unsigned expectedIndex_;
};

class StringRegex final : public Regex
{
public:
    StringRegex();

    RegexStatus on(char value) override;
    void reset() noexcept override;

private:
    static bool validateCharacter(char c);
};

#endif //REGEX_H
