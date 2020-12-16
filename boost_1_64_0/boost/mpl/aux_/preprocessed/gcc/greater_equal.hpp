
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

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
auaej6trXX5UXevyX2v+I803q2fdX3pWmB/pmW+m46bCs/2T1P4+lvAq68Q18O0/9GnksLncbe5hwe033n2EjZ6d63sPz5wz3W3wRp5SG1jLUMS88mg5H0Xo2fsNdD6qR9jBOiWePKYFew5150nv+bDUwyalkax0LiVsNtKo4b6PMj/bmaEDKej3rwQ8f1DWr2pYj/9j5uNb/QeO6lV//rX986kDPx/c/rnqgZ+fbv987cDPJbfvPwjcP2HfLxK432Krq1+hYcd7etxe75NqK86Nrp7V7wnqoU9d4/OIvvcOPi/3jLQ9z2/77J77n3wg8PPc7fs/qv7c9qr231T1Hk/7/p7Az1Wv1sH4/PDd088/P2fsVdUWPLbv+gVRxwL302g8Lb/Hzc9htY6n/YvG05ZibXwTPc/VidZ6l2k903N1uMfTvV43jMLu2Bl7YH/siaNxIE7DWJyOg9Hz/OgSxT9M8ZufHx2m+KOxPrZXOh2UTkcchGdhHHbxxctv3sDxvl3NHe93WB8PYxQewc74PQ7CoxiHx/AgFofp9ytuU7wN0Kl4f6N4l2ATvAJb49U4GK/BcbgcM3AFFuJKXIDX4pW4Cv+I1+Ej+BY+iX9FbRf93mS72mwXh+otH9tgAZ6PTpyIhTgb5+MyXIB34kpU/PptyPFoE/8wxT8e2+MEvAATcAZOxMtxEt6Gk/EJnKv4iVO/44zfd+74I43vLsX/ifoH92MkfobD8AtMxgO4CL/Ea/Er9fMdxDfwG9yHh0zP3T4Lv8fz8Cim4jHMxJ9wFf4b1+v52w9VA3wUa+FWrK3631NNv8f0O83Iv7G/79K1cGs9byoa22MH7IYdcTJ2xhl4Fs7CLjgPu+J8PAeLsTveij1wLfZEV/8m7sY++A88F49gfzTKOQin4GDMwiG4AONwEw7Dt/BC3Icj8CCOwsM4BjtTpnhMxHE4E8fjPEzAO3EibsbJ+ABegqV4Kb6D03EfzsCDeBkexmSsxw6Ugg0wFXviTOyHaTgY03ESZmAiZmIezsKFOBuX4hxchTl4C87FTZiLL2Mevonz8F3Mxw9wAX6DRfg9LtT25Zyl30s6FsjzGRgbpt8t2r5NsCc2xT4YiSOwGY7FKNT5V79tWNfm/HudjqfrsR7egMqHfq9QZzb52KPj5B31l+/FUfg+TsUP8VL8J8ay7uokns1K2EHYQygn1OYLLpoQS+AZzZU+0zmJZRyE5YT1hMcIsSy3e0x1v75w83ObHyOUEsoIhwh6DrP3Gcw5fn3m1ucs9yMkEvRMZcvzlHcTjIcCRBAqPjd5J/m7zZCg5yHzHGTKtJyyECr2w6/CDYTHCC8QygitqfT6Ns81XkXwPMt4O6GMtMx9+JtWst5Q1if0J4wmJBGWEdLHep83rGcMW/v7++ER4jM/W3gxYT3B/PzgQ/7jArzPCWZ8gOXZwFsJewifEo4Qoi9h2xGSCE7CzYQSwk5CGeEoofWljDMgJFwaGmMQmkJTaApNoSk0habQFJp++elnGP+fkz3z5Pv+jXf/39WO6zVX3396RmYqvQvJdI3PzXBmqU891fSMgAS1I3RU+3h7wiesX/pxlPrUjdfzu7pv3E3YQfXdWduwm5je0e/MKHJqnLs3D7vt88D/zHnIzs3Mc2ehKu31weahVGMAeigP3Qifsm5MhTw4CnmfeR49yam5J5UHz30CUeb3x6c5s/Nyk9MzCtK8fV58Tn9Vcho7T4F7vAT3TOjztNTctIwc39+M+Fujk5CZkzqrQH1k0egIVx8W2S/MtJZ9k/ryu6nsXQmfk2eHf9lPyT5gvkciwia/kX75td4rMjc71+jTs5RX/XyW5+0P16XkWWoL6UA=
*/