#include <iostream>
#include "KmkString.h"

using Kmk::String;

void StupidTest();

int main(int argc, char *argv[])
{
    StupidTest();

    return 0;
}

void StupidTest()
{
    const String cstr("const string");
    for (auto pc = cstr.Begin(); pc != cstr.End(); ++pc)
    {
        std::cout << *pc;
    }
    std::cout << std::endl;

    String str0("12345");
    String str1("12345");
    std::cout << "str1 --- " << str1 << std::endl;

    String str2(std::move(str1));
    str1.~String();

    String str3 = {'1', '3', '9'};
    String str4(10, 'a');

    String str5;
    str5 = str4;
    str5 += 'S';
    str5 += "kek";
    str5 += {'S', 'S'};
    str5 += str0;

    str5[2] = 'C';
    str5.At(3) = 'B';

    std::cout << "str0 --- " << str0 << std::endl;
    std::cout << "str1 --- " << str1 << std::endl;
    std::cout << "str2 --- " << str2 << std::endl;
    std::cout << "str3 --- " << str3 << std::endl;
    std::cout << "str4 --- " << str4 << std::endl;
    std::cout << "str5 --- " << str5 << std::endl;
    std::cout << "str5.ToUpper --- " << str5.ToUpper() << std::endl;
    std::cout << "str5.ToLower --- " << str5.ToLower() << std::endl;
    std::cout << "str5.GetSize --- " << str5.GetSize() << std::endl;
    std::cout << "str5.GetCapacity --- " << str5.GetCapacity() << std::endl;
    std::cout << "str5 == str1 --- " << (str5 == str1) << std::endl;
    std::cout << "str5 == Copy(str5) --- " << (str5 == String(str5)) << std::endl;
    std::cout << "str5.ToUpper == str5.ToLower --- " << (str5.ToUpper() == str5.ToLower()) << std::endl;
}