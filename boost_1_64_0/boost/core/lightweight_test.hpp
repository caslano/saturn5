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
4R6bvrgWeDxs0sxloR6mAfP1ULIYZxqW+1Lggfpiu8G+ENYngPkyZxkDZwjp3bFNdoY0ZnMqn3DsWSna3FHOxzhD8KwLMP894qMB8xwi9lwbeMAhYmQ8FnDPIWLPvj0eP77N43yc9ZiSHr+tKuPcyZMyPt7HuYBoP0/weMxmDfJ5osejZzQr40kS7sWeeLLH438L4HLA/W/dHkMsktvraR5Ph9deT3dwub2e6fCE7fXsAMf2CtNje4V42F7PdXC5vZ7v8Mjt9UKHJ2yvFwd42F5XujzcXnXefeO+XCIo7MvnQV9210uUJlkvGbu4iulQRFwzcRo/Drmd/7gJAzqRndjYG4N8KGyNjnJufFdXE8/tS8gPRPy/a3AtXBb3zw8R5nb0FVFCdhbh2HYr4NphJPiLTCXRXwSY963nkwEzDiP0faNcttvVAgb2CN8jAJwUjNifATseGytXpLXZTtHGXsM27e8zr1lrfVp67CAu6C8R+Lx0Yr63APvY16NsL97jG3D9zrkvIDvwMbwJ05scGptXldrDvrhPnFc36vxsX2gwryOVcaFNDpzZ8J3XKP7J5sW4hofuhLzxXOjHe8Rxy5P3JI88s449yR7/G9s3ku5bTyMfj+ob7Lf7KNNOU7QGyyav4cfEsr2H8qEiqeAf1BN1eBaaRR1/xLuYx79b9HGmU55j83Twi2PHBxkrj1YPM3ibF68uWHt+ktLQ+/IjpWI+8LXcxPImClBGwD+U4FOlsdEpUnVpkkzY4p9ifHf/vgv39GVZgU32XJ9xWOebtJ9lLCrI+nmfxildZQJjc9xsZZpx83NQR4g15+vGrKPriQeatDujQttHx23nR6YjQd6slcf2+kWq1yFlr4vofI1pXyXaa4l2QxPRGsyXHjt1ZoL+Og/5gs4oH4oLZqKCmbNtonMuqsvRLf+K8cn8CNthdtrQfwz0csn68n4KdD/2388BU4Fc0AZuIYxL1oRx/+L6QeQ/pa9fsb5eo/UFts38bN1s3LGOb+U0J92F0uD8a9JcUiqSu8C1Mca8mLjvS9JoS3bOjv5usKg8VaxWCcUxhDHVM3goIY5kfPsnl/ELTVBGLAcHwqz37kZhLJcv5qT54VmBXZ5wDt23oLxfcgKdDzPtRKY9D2gnMe1qoN2Naa9TtDrtt5AbIcf0kUJm8+aOrYH9vsCWD2zk7pTPwTiBHXPuQbS5mJaNKGYe+Vem8fswMs7Hs8Wc5buXkc13HDlwFK9lTBnuTXzjBfVxyoA2moexcCnRJgqcJ2Wpw93Zsf10naYYmwDXEWRRCst7hqZVafYgl4LNdxXRc9OlI+jXvK/mjckJbQ3RCvRQYgry+dZ9Yj7y7wa0DqZBOfVKOinPWUyLjrrfFDtb05XidElBzpOoReN5vbMppHU1+flFl4L9n2N00pHp6O7uFso3U5gQZGQs7VzdHtOqkRK5HZpW7ih3kHKz5Qzk2elhnTCOnsdYJpsfQ51uZXonqdV8a8fQiBdkPCihc87mfJDplUL8URvnjGUbYdXRsThq8FQh55wd9hFGShit0ml1Mp70E+0etIYeojHvDu6rVaa1AW2eaYsXWdpjiPYAxddkaT9hvi6g3c609wHtr0z7j6LVPx4Ucpm4cwrz6IfPlOJXP1PZdS67Y3tmmiJhHDFam63GxkL6CXiPDvZsT+XdlIzhIHe6NFOdKNE4P0/THM1OMXOxPIUx5z5E/P29FJNpYDAOfDaqvBtqc121feYO1a7jJHA3WSDY2b8MPV+iccdZL/3HYHPOXZOX2fw4YGTJZIj+kM9DPfzqIg/rJeAx6zorR3+7kMcn1C2VZ8fePfuHZOXC3YpWKDv7skx8f6wX790=
*/