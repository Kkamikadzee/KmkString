cmake_minimum_required(VERSION 3.0.0)

project(StupidTest)

add_executable(${PROJECT_NAME} StupidTest.cpp)

target_link_libraries(${PROJECT_NAME} KmkString)

if(BUILD_TESTING)
    add_test(SomeTest ${PROJECT_NAME})

    set_tests_properties(SomeTest PROPERTIES TIMEOUT 1)

    set_tests_properties(SomeTest PROPERTIES
    PASS_REGULAR_EXPRESSION
    "const string[\r\n\t]+str1 --- 12345[\r\n\t]+str0 --- 12345[\r\n\t]+str1 --- [\r\n\t]+str2 --- 12345[\r\n\t]+str3 --- 139[\r\n\t]+str4 --- aaaaaaaaa[\r\n\t]+str5 --- aaCBaaaaaSkekSS12345[\r\n\t]+str5\\.ToUpper --- AACBAAAAASKEKSS12345[\r\n\t]+str5\\.ToLower --- aacbaaaaaskekss12345[\r\n\t]+str5\\.GetSize --- 20[\r\n\t]+str5\\.GetCapacity --- 32[\r\n\t]+str5 == str1 --- 0[\r\n\t]+str5 == Copy\\(str5\\) --- 1[\r\n\t]+str5\\.ToUpper == str5\\.ToLower --- 0"
    FAIL_REGULAR_EXPRESSION 
    "Error!"
    )
endif()

