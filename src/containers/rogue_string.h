#ifndef ROGUE_STRING_H
#define ROGUE_STRING_H

#include <stddef.h>

// 4 bytes 

class String
{
public:
    String();
    String(const char* text);
    String(const String& rhs);
    String(String&& rhs) noexcept;
    ~String() = default;

    String& operator=(const char* text);
    String& operator=(const String& rhs);
    String& operator=(String&& rhs);

    char operator[](size_t index) const;
    char& operator[](size_t index);

    void push_back(char c);
    void pop_back();

    size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool full() const noexcept;
    const char* c_str();

private:
    bool isSmall() const noexcept;
    void reserve(size_t size);
    void increaseSize();
    void decreaseSize();

private:

    struct LargeRep
    {
        char* buffer;
        size_t size;
        size_t capacity;
    };

    struct SmallRep
    {
        static constexpr auto capacity = sizeof(LargeRep) - sizeof(unsigned char);
        char buffer[capacity];
        unsigned char size;
    };

    union Representation
    {
        static_assert(sizeof(LargeRep) == sizeof(SmallRep), "mismatched string sizes");
        LargeRep largeRep;
        SmallRep smallRep;
    };

    static constexpr auto smallStringCapacity_ = SmallRep::capacity;

    Representation representation_;
};

String& operator+(const String& lhs, const String& rhs);
String& operator+(const char* lhs, const String& rhs);
String& operator+(const String& lhs, const char* rhs);

#endif //ROGUE_STRING_H
