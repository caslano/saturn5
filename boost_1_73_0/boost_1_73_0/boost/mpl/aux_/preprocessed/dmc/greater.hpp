
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
hznMMSFzIuPbKieQhrr6wvu5ciqAQ61wGlwy5qSYNFy6qitq3VSaDQsW2MEwAIZg9e8KZasaGkiRIfFcuRL/kuKVFKUYtSgz3TSqzQP4V4mcWwqxeN0kaRQvF+wdb7apKCpjHZ+c6TYXrqxMLu4fHxjmasfhhMtt7MhUxQX7/lAVjgy6krC/biyVxQNRizNbajcDeRq0bNAZ7XSm6wDek3CLqtXtpdFH6/XvkPRkT/Stmq6mOz6Vs/u1178ODnBjOBKO8YDpQRgnOw/SjzjEyIMk+gyR0T3Yhul2jN7eo9TjBm4AUlypxO2T/ABQSwMECgAAAAgALWdKUu5sjMZNAQAAKQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyOTdVVAUAAbZIJGBtkk1PwzAMhu+W+h+sTTuOSFwQU1SBtiJ2Wmm7TXDLWpdWtMmUhI39e9x1rEhwiBI7r18/+ZCenM+VoxBkrUvD0wedjsYWLoSnLIb4Md3AfLuA6bT0+2lLvjIFuFq/N5QfC5Bi0EvRW4xhjCnZA9mpqwsCaWnfnHi/UF6FsGsUXgaX9DkpLhounTc1aX8pzc8BC9zZMASmYPVPhFKrls6oyJR4rH2Fv1FxQEUpejHK3LSt0kUI/0uRkzMh
*/