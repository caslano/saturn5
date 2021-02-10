
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDUxOVVUBQABtkgkYMWUUU/bMBDH3y3lO5yoEBJa5wbotESmEmMThTHalWyFvjnOZfGa2JXttOo+/Zyk0EnjbZN4iX3J/+5+dz6HObROcIsjwqTKtV+WuN1ok9kRGSfJtH3A1aeEMLr/wmgnJj3Sg3s0azR9KzMkzOCq3HpBxh3vItDwbQgngwFMPoPd2FTXSmBAPnKHMSQ1voFBBHd67TXhAMKz+CyKvfrqSxKQLnQMDWXftgbN+dK7X2rlULn+LaofrojhfUACIrqXHq9L31KEL2KIUtv/TxH9QXGywwh3HKJAsXy1lrxqC3alM7qbDj80l6VsvLqhEa3hBV3kESmcW3n5k9kDp3UJ0sKm4M4bUFsEqaxDnoHO4UjUpjwirJGNSCnTYRh5/84kwBSv/IT7KQbrd/BtdgtuIwXCRroCMpnnaDxBE9ZYr6edAzChq4qrrCOKKT0cT+6T62l82PRzOpkltMv0rPPbXTHt3fiORuZbaJoAPHdowBXYdhEKbiFFVHBgC+0OCFu3Wh9iZbTTokFviJsM8HR8ARlr62L4iyMgF7UrtJG/uJNaxfCBWykgnUe1OJ2V4ucqTCu/Vjfl4uL83MuFwJWPdEyPmxP750yP
*/