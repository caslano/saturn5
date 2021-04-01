
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
YDuDuUdjNLXyoIvazVfOXSyVCp1Q/uloAoBsTpPAG+QtF09BF9NqC2yLJpYRJkfBqRf+j/9dPAJnWwVvuPqJszIpYEsA5mIDYEObjAqAHHlKo8+vOZ8riU29OEygF0WXW5cZgieg1oqLi6OXF3GsaZEkucP4zRPtJR2KRYvWCEFXp3ydmU3JyDcxrxGm1txqLpHlIIbDar4C9qkjKk4huUTh1g5gyPdxwGMS0RizRu1Czk2LSZEFXL9tz+gLRxKHivV3dbfJJSgudWsm9ij+HkOtKvEMCll+zctxnXd1GoYApfoEhP7zfGIMRmvS65SbgG+6APlBHy6750I1kEMU+W9J3Kl2vkkSZ0w3dI9YnTUCXiZpbgF7LEK5+BBBDc95c2zxFbs3sDsXPczQ5kHIv6puWzENcNrXsJ3ir5M1D5vQcw1Vsod/6Cg67IGx3rGzSS8lORfIdvmoyHZbR/9enfY+p46LC9Ca6O6cIXAD3Kg2AO0ltkUoiSBdJeuKU2OK9gp4o8piqfNM3fevofuhr2fZlCGPzs0+UipGdXKjndoIdAgtRVcfmDo9Eg==
*/