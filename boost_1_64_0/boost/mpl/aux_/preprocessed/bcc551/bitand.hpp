
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
7JS6IH2Z4JIflXyM54mPPfFzq76bfD7BvYqQ9knKQOgmjBOWCHnHLdXDNgtfsFTJO5ifEWreR9qnqef3M3d5O2PDh3nfQnkmSDPQ9vD5aug4+3+KstxF+hDtTtoI4QTr5zBKSP/B+apwnLb4vKWq+dw5Qb6fsdSxSc6HvGbId5jjDWHej9NVHaGfkH3/Ex9PpM7Xnoqcf67q+RLHIxAjffW67WXdMOlH4+tIX11nWeeqCdJnVtbZ4iG+H+tOSvqX4+sSV9fxRvBclUR69so68/RxhXXFpJevrKOPrr5yyTxXVZFet7LOcdp+U6zzkR5dWeeMr48/2pFnF+kDX37i9bO6rI5Lo/fH540Tp9Uzv4/IjH5V7oOuzG7k/UzmCPJ+JnMKua9mLiH31UzHlL7vZqYh84rMPK0zswR5D5RZgdyPM33IfCWzA7lfZ/Yh84rMYWSekDmp1zsyZ5D5QOY8ct/PXEbmLZmpD+jnxsxsZD6UWYjMOzIrkBrNrEHmD5kx5Pccmd3IfT5zUMftmWPIfTtzSm9P/si8KHNZ7+fKTP2anldl5iPznsxyMUy5kflUZofWkdmv083MIR23Z47r/eyZJ5D3VZkL4gLlRp57M9XXJX/Kjcw3MsuQ+VpmDfI8nBkVq6hnZN6TOYDMvzKPIvOszOPIPC1zVm9vZi7quCNTTYvki8xbMkuQeUxmlY6bmU3IfCyzC5nXZQ7ouCNzVFxZ2vn92QTxvXgCfTiPflzG2zD9G1zvmI+vwwq8DuuwFzuwEwfwDTiGb5LftWErzmEDGt9kvoJpGMUyvANrsB9j+A7JB9+Jo9gk5cNmnMV3ST7f4v2n5INvx0LchZW4G+V7qoDkS7wFo9iD8vfybsQe4kEcxBtwHK/HaXwzLuItkv8JxiI5b3w9luLNWIWH0IcdKH8X7yapB+Ldki/uw6N4reSLb8STeCc6vs1zK8rf9ziIJcT7JF+8FQN4F3biAA7jW6Sc+DbJB2/H7AeZb0m58IC0B4ZkPzyMQ3gEj2EM5Xc0bdLOxN+D8nc5unDhwX9+/HjKL4WMwg/p8cJIQ65vIxu5no1i5PnDqEKuZ8OHjB9GFLnejC7k+jMGkOvOGEOer4xxZNwxZpDry1hErjfDMaOfcwwLZYQvQcYHowIZH4wdyPVthEVmKd3iyrJTfudK3CdzAPTL2I8NMs5jo7xDwCb5Xe13uB5Qvn/bhSXEd2M1HsQwHsJuDMj8AltwEoPyXIohuY98l+tW7ncYxmLcg1XYIeVYR/9CH/GIHA9bJR0PSPkwKve/78lzAr9XxnYsxb2SD8akPLhPyoPXyv0GT79fjxOfJPzltOWJzmf+2eVZ0jWOct8lhAm9hFHCFGGBoO49VxUSqgjhe1l/L+vvZf29rL+X9fexnlBFCN/H+vtYfx/r72P9faz/OOs/fu7jXlcffPanyq/8UdnHT8Xb+h+9Xuphja6ns8vZ5X9vufxnWUbnT7OMfsIwYZzwTcI84SbWdRCaCNtF0ooxk5BM+CPxf3b5DPtPE35NUCezjCLCh/hcdfLJ5/nwL8iH8CGC45eUj/BCwlWE/YRbCMOEMcJnCFOEBwknCUkLWcZ6Qj6hgtBA2E+4ifA+wicJU4Tj5L3M9v14hBAh1P2CdZR3Xsr8c86DsJ6QT7iUcCWhgdBOuJ5wO2GIMEr4POFBwknC2l+wL2E9wUu4lFD9iydfD09k+ShlvZPQ+STruelXnA+hnPBCQiEhl5BOeDrBQfgz9bS48OTyPe09T+caQpTQSnAS7IQEgotw5U+pF0IhIUT8IkIxIYWQRLARPIRnEs4hPIugCM8ghOWVMSGVYBKMf3G5k3N9N2GUcB9hgnA=
*/