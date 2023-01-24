
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {
template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl< aux::has_type< F<U1> >::value >
            ::template result_< F<U1> >

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

        : quote_impl< aux::has_type< F< U1,U2 > >::value >
            ::template result_< F< U1,U2 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3 > >::value >
            ::template result_< F< U1,U2,U3 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3,U4 > >::value >
            ::template result_< F< U1,U2,U3,U4 > >

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

        : quote_impl< aux::has_type< F< U1,U2,U3,U4,U5 > >::value >
            ::template result_< F< U1,U2,U3,U4,U5 > >

    {
    };
};

}}


/* quote.hpp
49ifr8RwSl330ztITrOLWRT57xcd39NyfAyZshLzDTc9nvxLimMEKDnl2/7A7Bp9KEWzJSpo6VXB3ldECFNacAmMaoj5apGtlvbG+p7bLT7iS7Jbs/6h+nsh7OKfBwnioLKkYAu+ajfFSUvIpjdL1oSUii6tPf9uaJPaGtSBXIi+bWpiZBFbdBI8gF6emVw2uchScgr+dHQo+GhAMk01MGmRJJPkqbZs35uYwC9a0OJrhkHla8EdYcl+uYg5j+puHiO0uxzmtM6dEn3A4Ap1YzTynBn2jj9O3ytiBmdnYVizdyaoJL8D7eZ4dtmnGexEqIirYclLrL+x+kiVYNTjmDQxvrqrg9NYx2hWW/yeuWTCAHNYHJDX2BhfjP9CEJ1lQcAhk0ArxH11f+b7Eg/AJfbgCX85kvpWkDOc5TNLZ+Kk1U/M616EPvz+yzcdZkcP1Ny4DKnkF6I/pyhvQ2KZHPjdyt/86CGsKioRQAUMpG3pnTA0uVN0KWeVhenZvlJ6j/9w5bf7+ahPzOdb3Mw73Ok/eo4l3Ld8ilGatvVNoC51gb8LeNF+qAv38E2mLnq1qCwuy0WNjIlo53bPCCQ17jMurI14C4+KSPD58oQLfwW3PxHgMJd5QL2NWviiAOcm8OvSvfhwcJlUGXEPPWYNNGMN3HaZHdSg9FDtZ8/TtIYTe9QgNfpVKzVEGhX7JVE9cqnVLudUiWX6NSlv
*/