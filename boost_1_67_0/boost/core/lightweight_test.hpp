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
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <cstddef>

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

inline void throw_failed_impl(char const * excep, char const * file, int line, char const * function)
{
   BOOST_LIGHTWEIGHT_TEST_OSTREAM
    << file << "(" << line << "): Exception '" << excep << "' not thrown in function '"
    << function << "'" << std::endl;
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

struct lw_test_eq {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t == u; }
    static const char* op() { return "=="; }
};

struct lw_test_ne {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t != u; }
    static const char* op() { return "!="; }
};

struct lw_test_lt {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t < u; }
    static const char* op() { return "<"; }
};

struct lw_test_le {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t <= u; }
    static const char* op() { return "<="; }
};

struct lw_test_gt {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t > u; }
    static const char* op() { return ">"; }
};

struct lw_test_ge {
    template <typename T, typename U>
    bool operator()(const T& t, const U& u) const { return t >= u; }
    static const char* op() { return ">="; }
};

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
            << file << "(" << line << "): test '" << expr1 << " " << pred.op() << " " << expr2
            << "' ('" << test_output_impl(t) << "' " << pred.op() << " '" << test_output_impl(u)
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
   #define BOOST_TEST_THROWS( EXPR, EXCEP )                    \
      try {                                                    \
         EXPR;                                                 \
         ::boost::detail::throw_failed_impl                    \
         (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
      }                                                        \
      catch(EXCEP const&) {                                    \
         ::boost::detail::test_results();                      \
      }                                                        \
      catch(...) {                                             \
         ::boost::detail::throw_failed_impl                    \
         (#EXCEP, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION); \
      }                                                        \
   //
#else
   #define BOOST_TEST_THROWS( EXPR, EXCEP )
#endif

#endif // #ifndef BOOST_CORE_LIGHTWEIGHT_TEST_HPP

/* lightweight_test.hpp
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
*/