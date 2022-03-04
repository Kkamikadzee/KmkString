#include <ostream>
#include <cctype>
#include "KmkString.h"

namespace Kmk
{
    String::String() : chars(nullptr), capacity(nullptr), firstFree(nullptr)
    {
    }

    String::String(const size_t count, const char c) : String()
    {
        // Дополнительная ячейка для символа конца строки
        Reallocate(count + 1);

        auto end = firstFree + count;
        for (firstFree = chars; firstFree != end - 1; ++firstFree)
        {
            *firstFree = c;
        }
    }

    String::String(const char *str) : String()
    {
        Concat(str);
    }

    String::String(std::initializer_list<char> il) : String()
    {
        // Дополнительная ячейка для символа конца строки
        Reallocate(il.size() + 1);
        CopyRange(il.begin(), il.end(), firstFree);
    }

    String::String(const String &original) : String()
    {
        Reallocate(original.GetCapacity());
        CopyRange(original.Begin(), original.End(), firstFree);
    }

    String::String(String &&original) noexcept : chars(original.chars), capacity(original.capacity), firstFree(original.firstFree)
    {
        original.chars = original.capacity = original.firstFree = nullptr;
    }

    String::~String()
    {
        Free();
    }

    String::operator bool() const
    {
        return GetSize() != 0;
    }

    String &String::operator=(const String &str)
    {
        if (this != &str)
        {
            Reallocate(str.GetCapacity());
            CopyRange(str.Begin(), str.End(), firstFree);
        }

        return *this;
    }

    String &String::operator=(String &&str) noexcept
    {
        if (this != &str)
        {
            Free();

            chars = str.chars;
            capacity = str.capacity;
            firstFree = str.firstFree;

            str.chars = str.capacity = str.firstFree = nullptr;
        }

        return *this;
    }

    const char &String::operator[](const size_t index) const
    {
        return *(chars + index);
    }

    char &String::operator[](const size_t index)
    {
        return const_cast<char &>(static_cast<const String &>(*this)[index]);
    }

    String &String::operator+=(const char c)
    {
        return Concat(c);
    }

    String &String::operator+=(const char *str)
    {
        return Concat(str);
    }

    String &String::operator+=(std::initializer_list<char> il)
    {
        return Concat(il);
    }

    String &String::operator+=(const String &str)
    {
        return Concat(str);
    }

    const char &String::At(const size_t index) const
    {
        if (!(index < firstFree - chars))
        {
            throw std::out_of_range("Invalid char index");
        }

        return this->operator[](index);
    }

    char &String::At(const size_t index)
    {
        return const_cast<char &>(static_cast<const String &>(*this).At(index));
    }

    String String::ToLower() const
    {
        String tmp(*this);
        for (auto c = tmp.Begin(); c != tmp.End(); ++c)
        {
            *c = std::tolower(*c);
        }

        return std::move(tmp);
    }

    String String::ToUpper() const
    {
        String tmp(*this);
        for (auto c = tmp.Begin(); c != tmp.End(); ++c)
        {
            *c = std::toupper(*c);
        }

        return std::move(tmp);
    }

    inline const size_t String::GetSize() const
    {
        return firstFree - chars;
    }

    inline const size_t String::GetCapacity() const
    {
        return capacity - chars;
    }

    inline const char *const String::Begin() const noexcept
    {
        return chars;
    }

    inline char *const String::Begin() noexcept
    {
        return chars;
    }

    inline const char *const String::End() const noexcept
    {
        return firstFree;
    }

    inline char *const String::End() noexcept
    {
        return firstFree;
    }

    String &String::Concat(const char c)
    {
        if (!HasFreePlaces(1))
        {
            Reallocate(1);
        }

        *(firstFree++) = c;

        return *this;
    }

    String &String::Concat(const char *str)
    {
        const char *c = str;
        while (*c)
        {
            if (!HasFreePlaces(1))
            {
                Reallocate(1);
            }

            *(firstFree++) = *(c++);
        }

        return *this;
    }

    String &String::Concat(std::initializer_list<char> il)
    {
        if (!HasFreePlaces(il.size()))
        {
            Reallocate(il.size());
        }

        CopyRange(il.begin(), il.end(), firstFree);

        return *this;
    }

    String &String::Concat(const String &str)
    {
        if (!HasFreePlaces(str.GetSize()))
        {
            Reallocate(str.GetSize());
        }

        CopyRange(str.Begin(), str.End(), firstFree);

        return *this;
    }

    void String::Swap(String &str) noexcept
    {
        using std::swap;

        swap(chars, str.chars);
        swap(capacity, str.capacity);
        swap(firstFree, str.firstFree);
    }

    inline const bool String::HasFreePlaces(const size_t countChars) const
    {
        // Всегда должно оставаться последнее место под символ конца строки
        return GetCapacity() ? capacity - firstFree - 1 > countChars : false;
    }

    inline void String::Free()
    {
        delete[] chars;
    }

    const size_t String::CalcNewCapacity(const size_t countNewChars) const
    {
        auto currentCapacity = GetCapacity();
        auto minNewCapacity = currentCapacity + countNewChars;

        if (currentCapacity == SIZE_MAX || currentCapacity > minNewCapacity)
        {
            throw std::overflow_error("String too long");
        }

        currentCapacity = currentCapacity ? currentCapacity : minCapacity;
        // Фактически равно 2 << (floor(log2(minNewCapacity))) на множестве целых чисел
        while (currentCapacity < minNewCapacity)
        {
            currentCapacity <<= 1;
        }

        return currentCapacity;
    }

    void String::Reallocate(const size_t countNewChars)
    {
        auto newCount = CalcNewCapacity(countNewChars);
        auto newChars = new char[newCount];
        auto newCapacity = newChars + newCount;
        auto newFirstFree = newChars;
        CopyRange(Begin(), End(), newFirstFree);

        for (auto c = newFirstFree; c != newCapacity; ++c)
        {
            *c = char();
        }

        Free();

        chars = newChars;
        capacity = newCapacity;
        firstFree = newFirstFree;
    }

    inline void String::CopyRange(const char *begin, const char *end, char *&insertPtr)
    {
        for (auto c = begin; c != end; ++c)
        {
            *(insertPtr++) = *c;
        }
    }

    bool operator==(const String &lhs, const String &rhs)
    {
        if (lhs.GetSize() != rhs.GetSize())
        {
            return false;
        }

        for (auto lhsPtr = lhs.Begin(), rhsPtr = rhs.Begin();
             lhsPtr != lhs.End() && rhsPtr != rhs.End();
             ++lhsPtr, ++rhsPtr)
        {
            if (*lhsPtr != *rhsPtr)
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const String &lhs, const String &rhs)
    {
        return !(lhs == rhs);
    }

    String operator+(const String &lhs, const String &rhs)
    {
        String tmp(lhs);
        tmp.Concat(rhs);

        return std::move(tmp);
    }

    std::ostream &operator<<(std::ostream &out, const String &str)
    {
        if (str.GetSize())
        {
            out << str.chars;
        }

        return out;
    }

    std::istream &operator>>(std::istream &is, String &str)
    {
        char *buffer = new char[4096];

        is >> buffer;

        if (is)
        {
            str = std::move(String(buffer));
        }

        delete[] buffer;

        return is;
    }

    void swap(String &lhs, String &rhs)
    {
        lhs.Swap(rhs);
    }
} // namespace Kmk

namespace std
{
    template <>
    void swap<String>(String &lhs, String &rhs)
    {
        swap(lhs, rhs);
    }
} // namespace std