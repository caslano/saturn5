#ifndef BOOST_CORE_LIGHTWEIGHT_TEST_HPP
#define BOOST_CORE_LIGHTWEIGHT_TEST_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER)
# pragma once
#endif

//
//  boost/core/lightweight_test.hpp - lightweight test library
//
//  Copyright (c) 2002, 2009, 2014 Peter Dimov
//  Copyright (2) Beman Dawes 2010, 2011
//  Copyright (3) Ion Gaztanaga 2013
//
//  Copyright 2018 Glen Joseph Fernandes
//  (glenjofe@gmail.com)
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/current_function.hpp>
#include <boost/config.hpp>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cctype>
#include <cstdio>

#if defined(_MSC_VER) && defined(_CPPLIB_VER) && defined(_DEBUG)
# include <crtdbg.h>
#endif

//  IDE's like Visual Studio perform better if output goes to std::cout or
//  some other stream, so allow user to configure output stream:
#ifndef BOOST_LIGHTWEIGHT_TEST_OSTREAM
# define BOOST_LIGHTWEIGHT_TEST_OSTREAM std::cerr
#endif

namespace boost
{

namespace detail
{

class test_result {
public:
    test_result()
        : report_(false)
        , errors_(0) {
#if defined(_MSC_VER) && (_MSC_VER > 1310)
        // disable message boxes on assert(), abort()
        ::_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
#if defined(_MSC_VER) && defined(_CPPLIB_VER) && defined(_DEBUG)
        // disable message boxes on iterator debugging violations
        _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
        _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
#endif
    }

    ~test_result() {
        if (!report_) {
            BOOST_LIGHTWEIGHT_TEST_OSTREAM << "main() should return report_errors()" << std::endl;
            std::abort();
        }
    }

    int& errors() {
        return errors_;
    }

    void done() {
        report_ = true;
    }

private:
    bool report_;
    int errors_;
};

inline test_result& test_results()
{
    static test_result instance;
    return instance;
}

inline int& test_errors()
{
    return test_results().errors();
}

inline bool test_impl(char const * expr, char const * file, int line, char const * function, bool v)
{
    if( v )
    {
        test_results();
        return true;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
          << file << "(" << line << "): test '" << expr << "' failed in function '"
          << function << "'" << std::endl;
        ++test_results().errors();
        return false;
    }
}

inline void error_impl(char const * msg, char const * file, int line, char const * function)
{
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
      << file << "(" << line << "): " << msg << " in function '"
      << function << "'" << std::endl;
    ++test_results().errors();
}

inline void throw_failed_impl(const char* expr, char const * excep, char const * file, int line, char const * function)
{
   BOOST_LIGHTWEIGHT_TEST_OSTREAM
    << file << "(" << line << "): expression '" << expr << "' did not throw exception '" << excep << "' in function '"
    << function << "'" << std::endl;
   ++test_results().errors();
}

inline void no_throw_failed_impl(const char* expr, const char* file, int line, const char* function)
{
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
        << file << "(" << line << "): expression '" << expr << "' threw an exception in function '"
        << function << "'" << std::endl;
   ++test_results().errors();
}

inline void no_throw_failed_impl(const char* expr, const char* what, const char* file, int line, const char* function)
{
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
        << file << "(" << line << "): expression '" << expr << "' threw an exception in function '"
        << function << "': " << what << std::endl;
   ++test_results().errors();
}

// In the comparisons below, it is possible that T and U are signed and unsigned integer types, which generates warnings in some compilers.
// A cleaner fix would require common_type trait or some meta-programming, which would introduce a dependency on Boost.TypeTraits. To avoid
// the dependency we just disable the warnings.
#if defined(__clang__) && defined(__has_warning)
# if __has_warning("-Wsign-compare")
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wsign-compare"
# endif
#elif defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable: 4389)
#elif defined(__GNUC__) && !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 406
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// specialize test output for char pointers to avoid printing as cstring
template <class T> inline const T& test_output_impl(const T& v) { return v; }
inline const void* test_output_impl(const char* v) { return v; }
inline const void* test_output_impl(const unsigned char* v) { return v; }
inline const void* test_output_impl(const signed char* v) { return v; }
inline const void* test_output_impl(char* v) { return v; }
inline const void* test_output_impl(unsigned char* v) { return v; }
inline const void* test_output_impl(signed char* v) { return v; }
template<class T> inline const void* test_output_impl(T volatile* v) { return const_cast<T*>(v); }

#if !defined( BOOST_NO_CXX11_NULLPTR )
inline const void* test_output_impl(std::nullptr_t) { return nullptr; }
#endif

// print chars as numeric

inline int test_output_impl( signed char const& v ) { return v; }
inline unsigned test_output_impl( unsigned char const& v ) { return v; }

// Whether wchar_t is signed is implementation-defined

template<bool Signed> struct lwt_long_type {};
template<> struct lwt_long_type<true> { typedef long type; };
template<> struct lwt_long_type<false> { typedef unsigned long type; };

inline lwt_long_type<(static_cast<wchar_t>(-1) < static_cast<wchar_t>(0))>::type test_output_impl( wchar_t const& v ) { return v; }

#if !defined( BOOST_NO_CXX11_CHAR16_T )
inline unsigned long test_output_impl( char16_t const& v ) { return v; }
#endif

#if !defined( BOOST_NO_CXX11_CHAR32_T )
inline unsigned long test_output_impl( char32_t const& v ) { return v; }
#endif

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

inline std::string test_output_impl( char const& v )
{
    if( std::isprint( static_cast<unsigned char>( v ) ) )
    {
        return std::string( 1, v );
    }
    else
    {
        char buffer[ 8 ];
        std::sprintf( buffer, "\\x%02X", static_cast<unsigned char>( v ) );

        return buffer;
    }
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

// predicates

struct lw_test_eq
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t == u; }
};

struct lw_test_ne
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t != u; }
};

struct lw_test_lt
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t < u; }
};

struct lw_test_le
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t <= u; }
};

struct lw_test_gt
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t > u; }
};

struct lw_test_ge
{
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t >= u; }
};

// lwt_predicate_name

template<class T> char const * lwt_predicate_name( T const& )
{
    return "~=";
}

inline char const * lwt_predicate_name( lw_test_eq const& )
{
    return "==";
}

inline char const * lwt_predicate_name( lw_test_ne const& )
{
    return "!=";
}

inline char const * lwt_predicate_name( lw_test_lt const& )
{
    return "<";
}

inline char const * lwt_predicate_name( lw_test_le const& )
{
    return "<=";
}

inline char const * lwt_predicate_name( lw_test_gt const& )
{
    return ">";
}

inline char const * lwt_predicate_name( lw_test_ge const& )
{
    return ">=";
}

//

template<class BinaryPredicate, class T, class U>
inline bool test_with_impl(BinaryPredicate pred, char const * expr1, char const * expr2,
                           char const * file, int line, char const * function,
                           T const & t, U const & u)
{
    if( pred(t, u) )
    {
        test_results();
        return true;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " " << lwt_predicate_name(pred) << " " << expr2
            << "' ('" << test_output_impl(t) << "' " << lwt_predicate_name(pred) << " '" << test_output_impl(u)
            << "') failed in function '" << function << "'" << std::endl;
        ++test_results().errors();
        return false;
    }
}

inline bool test_cstr_eq_impl( char const * expr1, char const * expr2,
  char const * file, int line, char const * function, char const * const t, char const * const u )
{
    if( std::strcmp(t, u) == 0 )
    {
        test_results();
        return true;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " == " << expr2 << "' ('" << t
            << "' == '" << u << "') failed in function '" << function << "'" << std::endl;
        ++test_results().errors();
        return false;
    }
}

inline bool test_cstr_ne_impl( char const * expr1, char const * expr2,
  char const * file, int line, char const * function, char const * const t, char const * const u )
{
    if( std::strcmp(t, u) != 0 )
    {
        test_results();
        return true;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " != " << expr2 << "' ('" << t
            << "' != '" << u << "') failed in function '" << function << "'" << std::endl;
        ++test_results().errors();
        return false;
    }
}

template<class FormattedOutputFunction, class InputIterator1, class InputIterator2>
bool test_all_eq_impl(FormattedOutputFunction& output,
                      char const * file, int line, char const * function,
                      InputIterator1 first_begin, InputIterator1 first_end,
                      InputIterator2 second_begin, InputIterator2 second_end)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && (*first_it == *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "] '" << test_output_impl(*first_it) << "' != '" << test_output_impl(*second_it) << "'";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        test_results();
        return true;
    }
    else
    {
        output << std::endl;
        ++test_results().errors();
        return false;
    }
}

template<class FormattedOutputFunction, class InputIterator1, class InputIterator2, typename BinaryPredicate>
bool test_all_with_impl(FormattedOutputFunction& output,
                        char const * file, int line, char const * function,
                        InputIterator1 first_begin, InputIterator1 first_end,
                        InputIterator2 second_begin, InputIterator2 second_end,
                        BinaryPredicate predicate)
{
    InputIterator1 first_it = first_begin;
    InputIterator2 second_it = second_begin;
    typename std::iterator_traits<InputIterator1>::difference_type first_index = 0;
    typename std::iterator_traits<InputIterator2>::difference_type second_index = 0;
    std::size_t error_count = 0;
    const std::size_t max_count = 8;
    do
    {
        while ((first_it != first_end) && (second_it != second_end) && predicate(*first_it, *second_it))
        {
            ++first_it;
            ++second_it;
            ++first_index;
            ++second_index;
        }
        if ((first_it == first_end) || (second_it == second_end))
        {
            break; // do-while
        }
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container contents differ in function '" << function << "':";
        }
        else if (error_count >= max_count)
        {
            output << " ...";
            break;
        }
        output << " [" << first_index << "]";
        ++first_it;
        ++second_it;
        ++first_index;
        ++second_index;
        ++error_count;
    } while (first_it != first_end);

    first_index += std::distance(first_it, first_end);
    second_index += std::distance(second_it, second_end);
    if (first_index != second_index)
    {
        if (error_count == 0)
        {
            output << file << "(" << line << "): Container sizes differ in function '" << function << "': size(" << first_index << ") != size(" << second_index << ")";
        }
        else
        {
            output << " [*] size(" << first_index << ") != size(" << second_index << ")";
        }
        ++error_count;
    }

    if (error_count == 0)
    {
        test_results();
        return true;
    }
    else
    {
        output << std::endl;
        ++test_results().errors();
        return false;
    }
}

#if defined(__clang__) && defined(__has_warning)
# if __has_warning("-Wsign-compare")
#  pragma clang diagnostic pop
# endif
#elif defined(_MSC_VER)
# pragma warning(pop)
#elif defined(__GNUC__) && !(defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 406
# pragma GCC diagnostic pop
#endif

} // namespace detail

inline int report_errors()
{
    boost::detail::test_result& result = boost::detail::test_results();
    result.done();

    int errors = result.errors();

    if( errors == 0 )
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
          << "No errors detected." << std::endl;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
          << errors << " error" << (errors == 1? "": "s") << " detected." << std::endl;
    }

    // `return report_errors();` from main only supports 8 bit exit codes
    return errors < 256? errors: 255;
}

} // namespace boost

#define BOOST_TEST(expr) ( ::boost::detail::test_impl(#expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, (expr)? true: false) )
#define BOOST_TEST_NOT(expr) BOOST_TEST(!(expr))

#define BOOST_ERROR(msg) ( ::boost::detail::error_impl(msg, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )

#define BOOST_TEST_WITH(expr1,expr2,predicate) ( ::boost::detail::test_with_impl(predicate, #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#define BOOST_TEST_EQ(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_eq(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )
#define BOOST_TEST_NE(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_ne(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#define BOOST_TEST_LT(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_lt(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )
#define BOOST_TEST_LE(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_le(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )
#define BOOST_TEST_GT(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_gt(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )
#define BOOST_TEST_GE(expr1,expr2) ( ::boost::detail::test_with_impl(::boost::detail::lw_test_ge(), #expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#define BOOST_TEST_CSTR_EQ(expr1,expr2) ( ::boost::detail::test_cstr_eq_impl(#expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )
#define BOOST_TEST_CSTR_NE(expr1,expr2) ( ::boost::detail::test_cstr_ne_impl(#expr1, #expr2, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, expr1, expr2) )

#define BOOST_TEST_ALL_EQ(begin1, end1, begin2, end2) ( ::boost::detail::test_all_eq_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, begin1, end1, begin2, end2) )
#define BOOST_TEST_ALL_WITH(begin1, end1, begin2, end2, predicate) ( ::boost::detail::test_all_with_impl(BOOST_LIGHTWEIGHT_TEST_OSTREAM, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, begin1, end1, begin2, end2, predicate) )

#ifndef BOOST_NO_EXCEPTIONS
   #define BOOST_TEST_THROWS( EXPR, EXCEP )                           \
      try {                                                           \
         EXPR;                                                        \
         ::boost::detail::throw_failed_impl                           \
         (#EXPR, #EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
      }                                                               \
      catch(EXCEP const&) {                                           \
         ::boost::detail::test_results();                             \
      }                                                               \
      catch(...) {                                                    \
         ::boost::detail::throw_failed_impl                           \
         (#EXPR, #EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
      }                                                               \
   //
#else
   #define BOOST_TEST_THROWS( EXPR, EXCEP )
#endif

#ifndef BOOST_NO_EXCEPTIONS
#  define BOOST_TEST_NO_THROW(EXPR)                                    \
    try {                                                              \
        EXPR;                                                          \
    } catch (const std::exception& e) {                                \
        ::boost::detail::no_throw_failed_impl                          \
        (#EXPR, e.what(), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
    } catch (...) {                                                    \
        ::boost::detail::no_throw_failed_impl                          \
        (#EXPR, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION);           \
    }
    //
#else
#  define BOOST_TEST_NO_THROW(EXPR) { EXPR; }
#endif

#endif // #ifndef BOOST_CORE_LIGHTWEIGHT_TEST_HPP

/* lightweight_test.hpp
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
*/