#ifndef __STRING_H__
#define __STRING_H__

#include <ostream>
#include <istream>

using std::initializer_list;
using std::istream;
using std::ostream;
using std::size_t;

namespace Kmk
{
    class String final
    {
    public:
        friend ostream &operator<<(ostream &, const String &);

        String();
        String(const size_t, const char);
        String(const char *);
        String(initializer_list<char>);
        String(const String &);
        String(String &&) noexcept;
        ~String() noexcept;

        explicit operator bool() const;

        String &operator=(const String &);
        String &operator=(String &&) noexcept;

        String &operator+=(const char);
        String &operator+=(const char *);
        String &operator+=(initializer_list<char>);
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
        String &Concat(initializer_list<char>);
        String &Concat(const String &);

    private:
        static const int minCapacity = 16;

        char *chars, *capacity, *firstFree;
        const bool HasFreePlaces(const size_t) const;
        void Free();
        const size_t CalcNewCapacity(const size_t) const;
        void Reallocate(const size_t);
        void CopyRange(const char *, const char *, char *&);
    };

    bool operator==(const String &, const String &);
    bool operator!=(const String &, const String &);
    String operator+(const String &, const String &);
    ostream &operator<<(ostream &, const String &);
    istream &operator>>(istream &, String &);
} // namespace Kmk

#endif // __STRING_H__