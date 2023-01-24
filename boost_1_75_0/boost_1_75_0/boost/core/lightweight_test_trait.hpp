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
sgvrw5x7bu5qJn7eo7105E2+z1r1Q8Qf7IhtL90fb1CDRuIsYISbArE+T98EvSJWhXLci3omAOfS24zEPMUyg7hctv668yth9iERnGmEL2D9IaYtCkcawBEWy+Qu6k5moiU27mktheAivbkRqhIaky3NyhFugvg+kg09oJ7iqk35vF2bPwEMX4bHuUlfiV9+E3xMVEZiLO6JvQFt5iGVn7batwB5s7spAecqnXsAV7gEBMLxHhYnMmOgTDR3j/entCGqt/WyNBbnINOvGffYygG/4ITxsjshfEqSvjhGoeXhGB/vLfEhV7aj71IBLgurPJG9h/viHMndl0Cfg3fJpcH9cq7E7hpn5WTodPy609ogtN/8fjDg4kQadhgY3bRFKplGZ8J0c7DMpPgM9BtcRWJjvJH3P/bhfkjSo7QERkr0q/B+Tk0XbNtrb/FLzrKEuLiMtKhxcYhjtojXgB3KKpm6BsqCsGzUv179a3nXjMESYMx38XJ/WMo6o5b1UYTj3R1uXiN/qxLGCxAOhN8DOW/n5fKZ0oyw5I/34bh4LeqsF40xCPfC9vJ6OFJfrI3VlEBTF3FwvI/C0WvuMDC/DLg2i7CCIKR7swDimueShfK4eb25W18E3iq/4I9wvJ/J1evFI8oqrDUYM5VcPtUOWNaSq6VVWiUQZe3i68320D0LbSmYiijenD3fHm2EH7dxbWOZUzzZDceVg1K9
*/