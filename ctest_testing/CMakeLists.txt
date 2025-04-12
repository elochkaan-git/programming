cmake_minimum_required ( VERSION 3.14)
project ( unittests CXX)
set( CMAKE_CXX_STANDARD 17)
set( CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    # warning level 4 and all warnings as errors

    add_compile_options (/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options (-Wall -Wextra -pedantic -Werror -g)
endif ()

enable_testing ()
add_subdirectory (tests)