
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
mecK/mmF+rHOz9Gjc8v1zNXTxkPnEw+Byzn4nRnPYc+pO3BrASXE3Kdl6OFy9VIIMFtKhhajQgwdkCmlMswqC3inSjjTD8+A627RlmtZf2v9e4ZOXA9Lgb/gsC/WQNeVLShSPOLVr6oYPoqtuTO66aI5C6BpDURlDoXBGQKTIjT7ew4KuUOPKx3AlvdWon77zhD2+i++7g1cq6UEpxmgMmA8FLwkoMb/RL1FCecIJE4GySNR1gwhtEeipiA1Kq1HYkkN7ukY+Nd763vSeYE5ULFwJqz2tqowo9RpsyTj6CHRNSlIBqmAVEfKSpciJ34QG4dqZG+n4V7WBed2FV2HwrWW7/lji8w21Yz4tKzG3rRRt1CrMcdaWNHFnaq3MFmIVKq+3EEdchFF6OeoMGsLxfPGg69fH/qU8ArTKQvRJdukGnlwu/NZ2hcLDTagt6e0cGioHrTTE8fND1meuljdX8XHWsY3q/hzJQRq5igR7vgaaw2vX3nMflPFnlNWkshaPBMamvu89AWC7cxokHLE4KCgbUH16dVrEWxH9PMPnnI7Wg1hrV7TecviZJQf3dewVmeveq70jO7sl1OmhUUd2oJKMIm9SrWiitR/RzN0h65FC9ldCcS38FnTEbewmp7xM3Idzlb+jHf86H7iuuielTqxoopviePH9md0zXm31LFPRA6x+PtvX4UYq3YusJhuMvBLZly52yf7YzZf
*/