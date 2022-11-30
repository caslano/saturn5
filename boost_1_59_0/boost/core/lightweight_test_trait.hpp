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
// Copyright 2014, 2021 Peter Dimov
//
// Copyright 2019 Glen Joseph Fernandes
// (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/lightweight_test.hpp>
#include <boost/core/type_name.hpp>
#include <boost/core/is_same.hpp>
#include <boost/config.hpp>

namespace boost
{
namespace detail
{

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
            << boost::core::type_name<T>() << "]"
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
            << "' ('" << boost::core::type_name<T1>()
            << "' != '" << boost::core::type_name<T2>() << "')"
            << std::endl;

        ++test_results().errors();
    }
}

} // namespace detail
} // namespace boost

#define BOOST_TEST_TRAIT_TRUE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, true, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )
#define BOOST_TEST_TRAIT_FALSE(type) ( ::boost::detail::test_trait_impl(#type, (void(*)type)0, false, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )

#if defined(__GNUC__)
// ignoring -Wvariadic-macros with #pragma doesn't work under GCC
# pragma GCC system_header
#endif

#define BOOST_TEST_TRAIT_SAME(...) ( ::boost::detail::test_trait_same_impl(#__VA_ARGS__, ::boost::core::is_same<__VA_ARGS__>(), __FILE__, __LINE__, BOOST_CURRENT_FUNCTION) )

#endif // #ifndef BOOST_CORE_LIGHTWEIGHT_TEST_TRAIT_HPP

/* lightweight_test_trait.hpp
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
*/