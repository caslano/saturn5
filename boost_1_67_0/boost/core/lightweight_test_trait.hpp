#ifndef BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP
#define BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER)
# pragma once
#endif

// boost/core/lightweight_test_trait.hpp
//
// BOOST_TEST_TRAIT_TRUE, BOOST_TEST_TRAIT_FALSE, BOOST_TEST_TRAIT_SAME
//
// Copyright 2014 Peter Dimov
//
// Copyright 2019 Glen Joseph Fernandes
// (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/lightweight_test.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/is_same.hpp>
#include <boost/config.hpp>

namespace boost
{

namespace detail
{

template<class, int = 0> struct test_print { };

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<T, 2>)
{
    return o << boost::core::demangled_name(BOOST_CORE_TYPEID(T));
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<T, 1>)
{
    return o << test_print<T, 2>();
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<const T, 1>)
{
    return o << test_print<T, 2>() << " const";
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<volatile T, 1>)
{
    return o << test_print<T, 2>() << " volatile";
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<const volatile T, 1>)
{
    return o << test_print<T, 2>() << " const volatile";
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<T>)
{
    return o << test_print<T, 1>();
}

template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<T&>)
{
    return o << test_print<T, 1>() << " &";
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T> inline std::ostream& operator<<(std::ostream& o, test_print<T&&>)
{
    return o << test_print<T, 1>() << " &&";
}
#endif

template< class T > inline void test_trait_impl( char const * trait, void (*)( T ),
  bool expected, char const * file, int line, char const * function )
{
    if( T::value == expected )
    {
        test_results();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): predicate '" << trait << "' ["
            << boost::core::demangled_name( BOOST_CORE_TYPEID(T) ) << "]"
            << " test failed in function '" << function
            << "' (should have been " << ( expected? "true": "false" ) << ")"
            << std::endl;

        ++test_results().errors();
    }
}

template<class T> inline bool test_trait_same_impl_( T )
{
    return T::value;
}

template<class T1, class T2> inline void test_trait_same_impl( char const * types,
  boost::core::is_same<T1, T2> same, char const * file, int line, char const * function )
{
    if( test_trait_same_impl_( same ) )
    {
        test_results();
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test 'is_same<" << types << ">'"
            << " failed in function '" << function
            << "' ('" << test_print<T1>()
            << "' != '" << test_print<T2>() << "')"
            << std::endl;

        ++test_results().errors();
    }
}

} // namespace detail

} // namespace boost

#define BOOST_TEST_TRAIT_TRUE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, true, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )
#define BOOST_TEST_TRAIT_FALSE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, false, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )
#define BOOST_TEST_TRAIT_SAME(...) ( ::boost::detail::test_trait_same_impl(#__VA_ARGS__, ::boost::core::is_same<__VA_ARGS__>(), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )

#endif // #ifndef BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP

/* lightweight_test_trait.hpp
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
*/