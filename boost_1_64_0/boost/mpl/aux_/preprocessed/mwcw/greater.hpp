
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
pj0AV6s93hXuBTvBm9xzoBtbvum1BFD92ngRHMdwU35xzToWxZ5j75rTUWpT5aj9FO2+BtGy1Ma6q2th6W6e8z8b9tW0tTjHWgXujfhq1rxf3sRzTYpPO2ao2t4X6Fv9XLVjKprYpFlr69SnvWXXjpm2h6Ud4y2Hpmpv91A5dIXr0LNqD4tNWt6ofraoHNRurSkHlxqu7jx2v9K2IUv4v37hdefxBl1zkE97/bJG9nkc2dQuPaHzH5yCfuWvdU1XKd6u/K2Cq9FTbm8PzUVjVf+gbTLa2Fo7w1Dgp419VTPi1VrP7uMrmuvYd3+GJvbPZ+qeVruz8v7+53M698Q38Zx/c8+6686CCPvnc3MT+7qzMcI3zaF/PgftZf98Pq/2fWeVQweVQ8leVptYP6hevhlzOaDDUg4c1yqHonmFlnLgmGu0Lwj5t34Pz/nGLeouh4t1TYrPMzwn3I8PsEWtNIfU15Pe0r4MYuTMOwtppDbHLegpa2mxR8sDBe7f8S0D8tdaBmHBlYFRjyI9aTjYJ0/LmtrnaXqkXRpC914sj7R/L5Y103wf1evuqtcxrWzt0fpNwZdza1P9LvBsH1uTvzpH5il/rWUQbSkDfQugfCW2LwnD3lZ11/GRrVXHLf5Djpvbl0dp6x2lP3TlEtamulz+W746xye3Y5/cfMMnF37fCcN/P7HVOakrrp1d0e7BNf58nKH11S0I0/e9visqEPPc+ofVRn8E9oQbYTJ8DE6Am+BM+AQsgE/KJ/I03K65553Q+azXl6Fva3gBUuHjy7hV8d2u+O6AY2GZaQ79DHgPTIdr4Xx4L1wC18GT4H1wBVwPz4X3Q0969R0Ne9ikF1uN+DvDnrALHAu7wsmwOzwMxsLFsAcsgb2gsX8r7Ar3hUov37n+0/uC0vuS0luu9L6i9L6m9L6u9L6h9L6p9G5Wet9Set9Wet9Ret02lSv+7UpvZ/ffiv89xf8hPBB+BLPgVpgPP4cXwi/kw/oK3g+/le/xO/gO/B5+BLfBz+GP8Af4s+pBFexA3L/AbnA7HAh/hxPhH3C61lhZApvDy+Ge8GrYAt4OW8J1sBV8BbaBm2EU/BDuDT+F0fAH2B5WwQ5Q5c/3sv/6vlL5cZXK42rV91Uqj+tU369Xfa/2Pd6odN6k+r7GVN83Rvgv/zMV3wrFd7bK/1zFV6ryP1/lf4HK/0KV/0Uq/4tV/peo/C+tqe/6LqXcbdI7RPEPVfz7Kb37K/4RcDocqfpwADwWJsNf4GiV6xiz77mFfJXm9Abga02BfeFUGAePkM81Uz7XxXCAfJXxcDkcqHQnKP70MH0DwrMUfzM4XfHPlq/yMNgRHg6HwCPgSJim58A8B3M+zFB8maZ0pkf6T+d4pTNF6TxI6ZygdE5SOicrnVOUzlSl8xClc6rinaZ0Tq8pV32XkYc25Xq84l+i+Jcq/mUq1xKV60mqxyerHp8Kd0fXabA7PN2U3tLW/tM7X/HlKL6Fii9X6c1TevOVXpfSe7TSW6D0Fiq9RUpvsfvY8f06vt9d4PvdiF+3Aml8V3hYLJKCuJBSZC1SjmxDou5mjheSfnfgfmAnOMEJTnCCE5zgBCf8P8Ku7/+X+zlE/f991f+v/lAjFMB2MBNOdO/Zt7vX/32oEff4nLy5uR6//yz7bDgFnzd2DDN83G3DdjfGV//YyGg/Mry6xh8+qp36BKz9LfOKs8Ps+lw0xtqyH4Fx7jb5+helGZcZ+tdU78Gqa9Z7xsZyHzHqmg2cy2vLfdXjCtQffDwMc9ure9dyndvWIpb/r/bfl5n2xsZf7/XZrwqhz95+XW7/vnx7n/Hf5+O3Xzf+3+/7D9bHf4Xh429x33c=
*/