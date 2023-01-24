
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
588tXo6iwlGtkKgDMePkiqk0fuJU6aWum3jEPBuZ2JiyqMZ8xbp3zu6V8Yg/+4qX7J6ihR/lvi/t02ylxj2f7tMiBG4+dlva2C3lkg24uoLGbu9I7nrt4z4Ng+re/J1/1pv5plj4y2Kpho64/zpsHg2cM7CIgGxtMr/qOieVDZU+uT15zNDPGnrXtZeXmPnaDpxjpy/anI/Gag18clSFKBQ4HzR4XDLQnGbe2Vo27TDbeUumb4S8e1S61wlMzX+2yAu0fVRx/uka1amq5VmvdJEQDVEkssHi+pUdUvgbr0VsCVBUO30883FhnGry/ZD8oagb82Uz9rKqkxLB7V/pAmADmtEx53KtKVzjxjS93Ke7q3q7R23sHl662ToXOVgqAdSs95VUM19VMSy7x8IqVZ48FVcL6S4TbUsxOy6ful/rmHN7/XT8z6Qy6hJ6BSHZ2VwZ6IYaUoCHgVVD38MFbqYeF+9mPWL/vFk1ICB+JJgyHzY6WZTZ+3JZVbbcRKrH6wp+HMY2mHbdFYCPgNsmwjsSFxXwRi/83zStK+jObi5Rz5fRmWHS/m+c1anVNo8lwvJvEqMFv/k2hziGY+zYxeyDq/aGZHK141hcJsD189wlSArZC9+WIRYFOrkWlISaus8VTWjOeKmXi84tUZCifQJ5IcrgVW5ubFV9RnVrYNxIRPU7qVMs4o9dxrN8pBQUFfnJ7IGeeEixLIaR
*/