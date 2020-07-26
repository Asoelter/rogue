#include "regex.h"

#include <cctype>

Regex::Regex()
    : status_(RegexStatus::NotStarted)
{
    
}

IdRegex::IdRegex()
    : Regex()
{
    
}

RegexStatus Regex::status() const noexcept
{
    return status_;
}

void Regex::reset() noexcept
{
    status_ = RegexStatus::NotStarted;
}

RegexStatus IdRegex::on(char value)
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    {
        const auto isAlpha = std::isalpha(value);
        const auto isValid = static_cast<bool>(isAlpha);
        status_ = isValid ? RegexStatus::Accepted : RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Accepted:
    case RegexStatus::Continuing:
    {
        bool isValid = std::isalpha(value) || std::isdigit(value);
        status_ = isValid ? RegexStatus::Accepted : RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Rejected:
    {
        break;
    }
    }

    return status_;
}

IntRegex::IntRegex()
    : Regex()
{
}

RegexStatus IntRegex::on(char value)
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    {
        auto isValid = std::isdigit(value) && value != 0;
        status_ = isValid ? RegexStatus::Accepted : RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Accepted:
    case RegexStatus::Continuing:
    {
        status_ = std::isdigit(value) ? RegexStatus::Accepted : RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Rejected:
    {
        break;
    }
    }

    return status_;
}

WhitespaceRegex::WhitespaceRegex()
    : Regex()
    , lastChar_('\0')
{
    
}

RegexStatus WhitespaceRegex::on(char value)
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    {
        const auto isValid = value == ' ' || value == '\\';
        status_ = isValid ? RegexStatus::Continuing : RegexStatus::Rejected;

        break;
    }
    case RegexStatus::Accepted:
    {
        status_ = RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Continuing:
    {
        auto isValid = false;
        auto isFinal = false;

        if(lastChar_ == ' ')
        {
            isValid = value == '\\' || value == ' ';
        }
        else if(lastChar_ == 'r')
        {
            isValid = value == '\\';
        }
        else if(lastChar_ == '\\')
        {
            isValid = value == 't' || value == 'n' || value == 'r';
            isFinal = isValid && value == 't' || value == 'n';
        }

        status_ = isValid ? RegexStatus::Continuing : RegexStatus::Rejected;
        status_ = isFinal ? RegexStatus::Accepted : status_;

        break;
    }
    case RegexStatus::Rejected:
    {
        break;
    }
    }

    lastChar_ = value;
    return status_;
}

StringRegex::StringRegex(std::string value)
    : Regex()
    , value_(std::move(value))
    , expectedIndex_(0)
{
    
}

RegexStatus StringRegex::on(char value)
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    {
        status_ = value == value_[0] ? RegexStatus::Continuing : RegexStatus::Rejected;
        ++expectedIndex_;
        break;
    }
    case RegexStatus::Accepted:
    {
        status_ = RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Continuing:
    {
        const auto nextState = expectedIndex_ == value_.size() - 1 ? RegexStatus::Accepted : RegexStatus::Continuing;
        status_ = value == value_[expectedIndex_] ? nextState : RegexStatus::Rejected;
        ++expectedIndex_;
        break;
    }
    case RegexStatus::Rejected:
    {
        break;
    }
    }

    return status_;
}

void StringRegex::reset() noexcept
{
    Regex::reset();
    expectedIndex_ = 0;
}
