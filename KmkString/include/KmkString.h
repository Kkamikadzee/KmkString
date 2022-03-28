#ifndef __STRING_H__
#define __STRING_H__

#include <ostream>
#include <istream>

namespace Kmk
{
    using std::size_t;

    class String final
    {
    public:
        friend std::ostream &operator<<(std::ostream &, const String &);

        String();
        String(const size_t, const char);
        String(const char *);
        String(std::initializer_list<char>);
        String(const String &);
        String(String &&) noexcept;
        ~String() noexcept;

        explicit operator bool() const;

        String &operator=(const String &);
        String &operator=(String &&) noexcept;

        String &operator+=(const char);
        String &operator+=(const char *);
        String &operator+=(std::initializer_list<char>);
        String &operator+=(const String &);

        const char &operator[](const size_t) const;
        char &operator[](const size_t);

        const char &At(const size_t) const;
        char &At(const size_t);

        String ToLower() const;
        String ToUpper() const;

        const size_t GetSize() const;
        const size_t GetCapacity() const;

        const char *const Begin() const noexcept;
        char *const Begin() noexcept;
        const char *const End() const noexcept;
        char *const End() noexcept;

        String &Concat(const char);
        String &Concat(const char *);
        String &Concat(std::initializer_list<char>);
        String &Concat(const String &);

        void Swap(String &str) noexcept;

    private:
        static const size_t minCapacity = 16;

        char *chars, *capacity, *firstFree;
        const bool HasFreePlaces(const size_t) const;
        void Free();
        const size_t CalcNewCapacity(const size_t) const;
        void Reallocate(const size_t);
    };

    bool operator==(const String &, const String &);
    bool operator!=(const String &, const String &);
    String operator+(const String &, const String &);
    std::ostream &operator<<(std::ostream &, const String &);
    std::istream &operator>>(std::istream &, String &);

    void swap(String &lhs, String &rhs);

    void CopyRange(const char *, const char *, char *&);

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

    inline const bool String::HasFreePlaces(const size_t countChars) const
    {
        // Всегда должно оставаться последнее место под символ конца строки
        return GetCapacity() ? capacity - firstFree - 1 > countChars : false;
    }

    inline void String::Free()
    {
        delete[] chars;
    }

    inline void CopyRange(const char *begin, const char *end, char *&insertPtr)
    {
        for (auto c = begin; c != end; ++c)
        {
            *(insertPtr++) = *c;
        }
    }
} // namespace Kmk

namespace std
{
    using Kmk::String;
    template <>
    void swap<String>(String &lhs, String &rhs);
} // namespace std

#endif // __STRING_H__