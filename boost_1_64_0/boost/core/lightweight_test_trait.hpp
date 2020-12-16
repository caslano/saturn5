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
l2MZuJwqc/N2BNPQYrje7x6xvZVy4vvJL4G9Wb2/I9QDpc/EdoFrbNQHe7wnVMm6kz2r137me1CFPP1ZquTpVisNn3FG+N3za/x0o+PU6IUgDdrKW8Myx+XNUMlR9rUoe2Jh2VAPT3Z6ber9nhe3S0TShHHg2+Le7ERtU1gO3prYNnm3X1Zvvv5YiNMRvsWvC3Ea0OGbqyE+XiyoQ+Simp9r85FRI99X0/iiSyvYbs8J+SYqpdmyvl1PuUe5SnGamoBMdFPi105JwwdU7Ba0ZXlyGj/30dZaclliMl5ckcan7C5eFeLYIvNiv0ryf1wKL/v6jMxjaXyRyd/Y1gd8XlizGR7sO9OjkwXuPDj/fCiQ488UENNS5C3NcNmYTywb5m7msxeljAFp7X1lKj+3dy25LLEbxhaRTx5nTHu+IC0dt2c3jIsiXyTLz8A8KqYL51Sjy5tS0kSoel4HnUzj0jStg3YuohPxRsa/1PeTfxN94qfE49+QuTjgvnsjbsLpHIBM1DhSzfx5L8IQwPXDYoPxMTN8sDnJ+94uj+5I0DdOBdwL2mt4ljg88b44O16qOHGUl1oeSpsZm4V46sucOhyJQXEuJhMoVPRNqCTv5Vp3O33t+W83C7ng7SbR0t9urmiFfIkL1wdXcFrvWp5Jex9MS2e3uCZcaerqvondq+vJXnpuBrxHBXqAM1+o38JvNJ+veZy3k6vt+1DC3JeqEo4vSLFsZ9o6qfUUx53EsoVvB1vs+1bCwxeuOJe+Hnj8V64oa3Wrx0fPnbQ2bHmaYx7KII4DmdEoyGhp9c9LdM2c90+mrdz4gmtZNltFRuUAssN1pbpEFnuHm0QeO58qh5PNp7VV39fCMcO/P8flwFufBu/k+3Np6Y956QszbvrIxYMzp3mDw+09wCF/cyUO87/MSR++d13njjeEs4sddL3B8kQ+j6BHLEdYT7gtinY/Y3G+MWqxj8Gawh8/xjEdqwfxScSFe7cR4lwsc9aLYw+NMBRvE03I6Od+yBc5thi83S3kwre7TKerm5b+w7jO5kZncJ+T+NEg0N4Q5xprv28XlfOVhD9D7ad5Xt7CtBcB7QKmPQloD2HaY4G2jWmHgHYh00pAG2RaVtEam/tT3hg/4L7SeeRQq9YZ3Lw12F7G4MYu3I0EzLtPOozpvO+g7newiGTadjig59KevT10etS/d5jnGcjTw4vWx3DQS+t/O/nhPE/70uGOrI8790seAekhh/Rxk9y1xUgN8nDvF2yed5gUW8euxy/WOB+dkRDesvE4bvgeBXL0CJTDOdeUaYz42CD0hJ6J5Tmx4fMBj94kmLuAXl7tya3IUsXsB8c9HrPan+Fod3o1ZvI8DD4czauWXBYv+nnqhReXScApq/HRHBXJ6nJS0NGk1ZLZS04HZacozaMzpeni6JRuQ7uXLPm8dLyMnLhfi4DXfvoBGwrWKGg7vKfC73rNerJ4QFV7iNo8ZbuPO4o8Ue12egfMIeCpMvY178kD0zB5XibpwWsM7KdPZNvYO3ARRec0Sxy4y+7jRWet+CQ/PY8/GyE9PSjvzmR7L6Su3Es9mQLZUqzVfQf2kEdnDNvw8tZ0XvOtl3rkUhETmU9ZQCb4M32Z+/de1E9iSA8Btn2gnyKz9sWFv30BvOjszZ5qykHRVPf1DO7ZPdCzC78rjTKQx5PzNEmON+Y/o1Wvt8y4D+V8tsFwbLX1fB7iQt95ocGhzfHd9TnO3kDN7zQeh75fqd9d4Y3p2Kdq8mSm7TeLeZ0n1f+lBpPr/zLApfq/0uBQf5D/Vqij8dzWGZ9LryfS4nnMieuJ54A+dFI7JiMm+RfNN02gzOi5wr7xapxD2Pep1k0=
*/