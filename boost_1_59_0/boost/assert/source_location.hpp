#ifndef BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED
#define BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED

// http://www.boost.org/libs/assert
//
// Copyright 2019, 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/current_function.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/cstdint.hpp>
#include <iosfwd>
#include <string>
#include <cstdio>
#include <cstring>

#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L
# include <source_location>
#endif

namespace boost
{

struct source_location
{
private:

    char const * file_;
    char const * function_;
    boost::uint_least32_t line_;
    boost::uint_least32_t column_;

public:

    BOOST_CONSTEXPR source_location() BOOST_NOEXCEPT: file_( "" ), function_( "" ), line_( 0 ), column_( 0 )
    {
    }

    BOOST_CONSTEXPR source_location( char const * file, boost::uint_least32_t ln, char const * function, boost::uint_least32_t col = 0 ) BOOST_NOEXCEPT: file_( file ), function_( function ), line_( ln ), column_( col )
    {
    }

#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L

    BOOST_CONSTEXPR source_location( std::source_location const& loc ) BOOST_NOEXCEPT: file_( loc.file_name() ), function_( loc.function_name() ), line_( loc.line() ), column_( loc.column() )
    {
    }

#endif

    BOOST_CONSTEXPR char const * file_name() const BOOST_NOEXCEPT
    {
        return file_;
    }

    BOOST_CONSTEXPR char const * function_name() const BOOST_NOEXCEPT
    {
        return function_;
    }

    BOOST_CONSTEXPR boost::uint_least32_t line() const BOOST_NOEXCEPT
    {
        return line_;
    }

    BOOST_CONSTEXPR boost::uint_least32_t column() const BOOST_NOEXCEPT
    {
        return column_;
    }

#if defined(BOOST_MSVC)
# pragma warning( push )
# pragma warning( disable: 4996 )
#endif

    std::string to_string() const
    {
        unsigned long ln = line();

        if( ln == 0 )
        {
            return "(unknown source location)";
        }

        std::string r = file_name();

        char buffer[ 16 ];

        std::sprintf( buffer, ":%lu", ln );
        r += buffer;

        unsigned long co = column();

        if( co )
        {
            std::sprintf( buffer, ":%lu", co );
            r += buffer;
        }

        char const* fn = function_name();

        if( *fn != 0 )
        {
            r += " in function '";
            r += fn;
            r += '\'';
        }

        return r;
    }

#if defined(BOOST_MSVC)
# pragma warning( pop )
#endif

};

template<class E, class T> std::basic_ostream<E, T> & operator<<( std::basic_ostream<E, T> & os, source_location const & loc )
{
    os << loc.to_string();
    return os;
}

} // namespace boost

#if defined(BOOST_DISABLE_CURRENT_LOCATION)

# define BOOST_CURRENT_LOCATION ::boost::source_location()

#elif defined(BOOST_MSVC) && BOOST_MSVC >= 1926

// std::source_location::current() is available in -std:c++20, but fails with consteval errors before 19.31, and doesn't produce
// the correct result under 19.31, so prefer the built-ins
# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(), __builtin_COLUMN())

#elif defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L

# define BOOST_CURRENT_LOCATION ::boost::source_location(::std::source_location::current())

#elif defined(BOOST_CLANG) && BOOST_CLANG_VERSION >= 90000

# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(), __builtin_COLUMN())

#elif defined(BOOST_GCC) && BOOST_GCC >= 70000

// The built-ins are available in 4.8+, but are not constant expressions until 7
# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION())

#elif defined(BOOST_GCC) && BOOST_GCC >= 50000

// __PRETTY_FUNCTION__ is allowed outside functions under GCC, but 4.x suffers from codegen bugs
# define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, __LINE__, __PRETTY_FUNCTION__)

#else

// __func__ macros aren't allowed outside functions, but BOOST_CURRENT_LOCATION is
# define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, __LINE__, "")

#endif

#endif // #ifndef BOOST_ASSERT_SOURCE_LOCATION_HPP_INCLUDED

/* source_location.hpp
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
*/