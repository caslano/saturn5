
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
KNvo+avG/Egtl9I5r7VGuweUnt9uzDHtwLgTdeSPnjLNH5V7CEqe/oey7O/iLcrSPas9j85pyetfbiU39rG9tXNjg4jlSdk55H1K/qGWl5iaqM1dz63+eggzyMjNLojLLchK0p8F6PxctE6MD5R5JeXnsjtRQo7MUP49SP5df/CfXp7x3nqJSQnq2nO+Z5vztjDen45pHHLheO6ROpwkmhPHiFspKfo5ye2UstkeCZmJSQ3KNe77vNM92GR5UjNq36vReK883i/OS2YZDXnGjGMZGaffd435MAr1+0WZ9a24fx8pd+/n5LoPqPHyz0z6zkzy4Uz7yBrt/k+Ndf/6plcq4xf+UBb6QffDzS8rumX7yo1/GeX+c+ps+Vly/JPjYhlhzM+6RvIl1mIArsOeuAEH4Ea0YglG4XU4E0txLt6Iy3AT5uPNuBL/hDfhLXg/bsFH8FZ8DW/DN/AOrMQ78SjehSdwG57Cu/Fn3KHd10SOaXKsK3O6r0m4LM9YbI3jMBAjsBtOxN44CUdjJE7AaTgPozETp2MuxuA6nIXX4Wz8M87B+3AuvoDzsBzny3Jdhn/DhViFcfgjLsJfcDG2lOfltcck7IfJOBiX4CRMwcm4FKdhGi7BdEzFDCzETFyDy/AWzMEHMRcfwuX4GBbgK3glvo0r8F0s1PJr5PiGJ+V+Gm2x3Om+Jh0wEAOxG3bC3tgZB2MQDsduOAGDcT52x3jsgcuxJ+ZjH7wB++LN2A8fwP64CwfhyzgYD+AQfBMvxg9wKH6CofgPHI7HcARu9bJ47v3hufeH594ff6B7fxTSH76NKPf0i3sGz/Bv9u4EvIkyDeB4gCItFCjQch/lEuQsUE4rlEsOCxQpcoiU0qa00CM0KSCgVkRARcUDRbm6HoACUgQUWY+quKKCFkHtKiooKipKxaqsx7r/mbxJJpMZmgC6PruZ5/n4MWnmu2Yyk5l8x19q+WPv/xWyMqdfgLn/lPv/SzT9/wvkO+BUuV+bTChU+ukWOe//r5yUmDQmmS51qdm2QO771xEHU2SlaPuCymt8jTMbK1vux+Tvv7NE8/95mucBDxHHdFkvl/UU3X39USlTVUIVCSdJLGK7WqYxiUNHjxuXkJxqy+fWmynB8m3+tUvoLvHfW9l3zISHyUe0d/xpmX70a66ruZ/lrt6eMsNq1D9enpFIn8XMHF5z9u/vv136C9R3ro+Q9RdbeNdJiHTWnCjfTYeh0lZjmneemQbOmjcnM9XdT68h+i6V9PO2u/fH6ljnPMutaEvyCP9vf41SR8lG8bv7Vs4O0Tz3keOglRwXyhgMqyo7Gxn0seB273HQq7Btdm6aUla1/Ivk7z9FOOvjQVn/WdZflPWPZX2/rG+Ida5/J+uPyfovsr4u0rk+4Unvv98p65tjvev7uPQP70/+GohbeU/EDq/6tmfkzk1PcaS4+3fGV/a3vsOd+/VpqQ9ZP/mUuq72hy3cpf6/TcLo7r0s8toyz2s9Xa/ZPK/Ful6b6Hmth+u1yzyvdbfojt30bAcfQ9kvvzn7vKbYZK6F35z7KUP+fpT1yeo2Mh8A60+QMg9r1P0dynsLqvIBUe4Zd3j2dzHva2XxzJFQ+pvXHA7ubU+y7Zds9LW6rRxnv3nGj49xHWfymnuOCdY5FpV8zXU9iyuRNGZZrbYZuTLmvCatxIuc5Zqg1Ltsc8RV3qFzeISXkMs26vvLyFfCRQTW7U958rZP6sOWbZ8hzyjdx/MlUoYDLeTzLetFcvztlfUdsp6007m+TY7XqZLOLvn7all/Rta3yPrfZf0ZWb+4g3P9oKw/H+s9jkuWwVj7xcr5ZLfy/oHJPPFNTcmi3VdaZm6yjcY=
*/