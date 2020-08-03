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
        const auto isAlpha = std::isalpha(static_cast<unsigned char>(value));
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
        auto isValid = std::isdigit(static_cast<unsigned char>(value));
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
{
    
}

RegexStatus WhitespaceRegex::on(char value)
{
    switch (status_)
    {
    case RegexStatus::NotStarted:
    {
        const auto isValid = value == ' ' || value == '\t' || value == '\n' || value == '\r';
        status_ = isValid ? RegexStatus::Accepted : RegexStatus::Rejected;
    } break;
    case RegexStatus::Accepted:
    case RegexStatus::Continuing:
    case RegexStatus::Rejected: 
    {
        status_ = RegexStatus::Rejected;
    } break;
    }

    return status_;
}

KeywordRegex::KeywordRegex(std::string value)
    : Regex()
    , value_(std::move(value))
    , expectedIndex_(0)
{
    
}

RegexStatus KeywordRegex::on(char value)
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    case RegexStatus::Continuing:
    {
        const auto nextState = expectedIndex_ == value_.size() - 1 ? RegexStatus::Accepted : RegexStatus::Continuing;
        status_ = value == value_[expectedIndex_] ? nextState : RegexStatus::Rejected;
        ++expectedIndex_;
        break;
    }
    case RegexStatus::Accepted:
    {
        status_ = RegexStatus::Rejected;
        break;
    }
    case RegexStatus::Rejected:
    {
        break;
    }
    }

    return status_;
}

void KeywordRegex::reset() noexcept
{
    Regex::reset();
    expectedIndex_ = 0;
}
StringRegex::StringRegex()
    : Regex()
{
    
}

RegexStatus StringRegex::on(char value) 
{
    switch(status_)
    {
    case RegexStatus::NotStarted:
    {
        status_ = value == '\"' ? RegexStatus::Continuing : RegexStatus::Rejected;
    } break;
    case RegexStatus::Continuing:
    {
        const auto isValid = std::isalpha(static_cast<unsigned char>(value)) 
                           || std::isdigit(static_cast<unsigned char>(value))
                           || value == '\"';
        const auto isFinal = value == '\"';
        const auto nextSucessState = isFinal ? RegexStatus::Accepted : RegexStatus::Continuing;
        status_ = isValid ? nextSucessState : RegexStatus::Rejected;
    } break;
    case RegexStatus::Accepted:
    {
        status_ = RegexStatus::Rejected;
    } break;
    case RegexStatus::Rejected: break;
    }

    return status_;
}

void StringRegex::reset() noexcept
{
    status_ = RegexStatus::NotStarted;
}

