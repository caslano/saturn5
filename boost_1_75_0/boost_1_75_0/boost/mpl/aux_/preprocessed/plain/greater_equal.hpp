
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
1bh1+BVPia3HmiqCq8lzb3GOjJFieeuI3AJbrh+WRbWujuwFP2TWiSutf7KolgG/y9r5XDsQh0hbOn4oT1v+M1e3K7QxPHGj67Nl2+POfj2KG4+tCbpSe7uucX3sdAGTUtLLOwnI2Os4+i7THSsidsVys5uIZafSXdEtd+XgwZkErUBPBxnHfnkYXOnbyzz5KwlaTqvQXZJtfgX/iYsF680xuYLfatI/9UQpZeJpC7Xn77ht+qQQFbcw6Z5/2YW3Xh6dbaDF7j0JBhgLm9InTqdtnH18UpTHJaVlt4sBDBxfAcu9YNikfaqykE0HTfYAFgHKgQH5Tq39so+UAU/CtnfLWr/JnG+0xqjq9piTy2HFs1oWmSi3HBO3jQTTaQkR9DLztxVLvjnFyMsQXza1pmfJ8pQemfkrkrKV3yRlmInZPYi7C7tvPRrvM/iS/iKZ7v72uy7cRZWiFy3BWACTLfSKaWQzo83wdvEO1i9yicYT3OBO1xW9MpA+DplFncr7ODmlmqyhJhwrOiYA5sPpymSd6uITZP7aQOmT7cZOcq9rWNZtN5XjRe97+cTewtWe4x/un6J2I5rRS9EhIXzjdvPXmXiHHDDNn4pln/QF71FyvIsLnigjLEddZFxsLPokK+AzCBOPik8S7ZFCuXkLBE8GLtYU2NP5RWXnlkiUZ4so/q0HGz/8Mw1xEm3ZLIZMc/J5+Kdmi0+ICqBC
*/