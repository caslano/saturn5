
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
y/z7hmtsMGM0tnbG/rlVDoyYuo0oZ7CFQOe/JYY5r3GaXnNMhT4jv7Hig232dIr3dpMu68D7SsDgyu2lFKnVBZ58G+N2/wC1ZejE9hictAA28MChmf0K1nMLbeogarl5I54pkmAyrwSovUjVpE4vxhEi4dkTPQYvIy/mmJW4unb4XwRnTSEeGiDFUQULFVyXUCVrI9NY1mAQ/fc+YnAOYsWl+UCI9RqDGTpW+ZE3qAaIBaJI1Zo5awJT7z78AYI9iunobYLzsKtZX+GrUWxRJUyOWX+EqC3EUSAcZWm9iGPjUvsMxT1l4p8mgRwmbb0CYrt8gtrQfYXm1jHSvbn4F27RGmtvulfFB9OGFIqxVhfbhHp5rHOB0RkQyEPdnZn0iKIFmVasxuH6aAN2bNgXwrbWg22WfJd9/7eA0fWsXPQ6Y7X0zebcJHTmoymMrekOXpuhRMZjAoCB69Ez1SBUm7k9rK/nyLwmj8uaTVeMS1nYbGxKHg/9CiZjGlzhiuOXP8PCtu9mwkiZx5VORM6P+NrK7JPHEnp0hCeBAjaIWKV6Xn/i7JJGMBY8sg==
*/