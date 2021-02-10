
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
hVz2nqdPy4f5rCPangr6st8RHe537qPliaE8X5Z/UEsDBAoAAAAIAC1nSlK6tSIxogIAAAcFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzI5VVQFAAG2SCRgrVRNT9tAED1nJf+HkRFCQjjrhKgUx4mEaCCoQBAxHHpb7HW8jb1reTcf7q/vrA0JtBx6qGTF3pnxm/fejBMark3MNB+TUMhU4W3J642qEj0m0yh6aH7gehKRWKml4JqEdF8R0valA5jzas0rT4uEk7DiZV5jNmGGtTC01+1B3/dh9t0h35jhAUQrfgL+OdyrNWZ6PvQGweA8wJrru8ghLWAAlqCnmwNN2ZI75FJJw6XxorrkNr81NDNF7pCrlZS1l3GWBFBzjZeFMd5lw7yFGmF0CCUz2YhuON0waegQElUwIUfdTGnTTZXqxqoYwh3behcLPvKH+6a3XC5MFsDAIQ55UQotaFU2YvufqP2M1adoxQ6tb519NRG9vcyFLW69jZsDFqQi5yBZwUdurhb0J6tO++ddszUuFCrBqHXGHZMPojrR49Oks1Peubq4nU86/d7gbPD19MvgrGM96khLxOJjm9b6McmMKTH6doTQtm7lQrsasBEm25uGJbStOYDJtsxFLExeg+YG
*/