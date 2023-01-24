
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
u0Gzwt7scHJTkmUn+T1EO4o1wK1Uc46FsIz50Jq8QO/yc6VLZlCUDwvNfe/JGxeWJZ2OTjWwFZu2mVPYSXVfuhTqMj/KzCsJbCttjExtwsOnCZ7Yy8clMzasbSqsbUqsbWqCCc8qyzuBnwB0XVv+vl7XyrfG6uB2Tfpm75uAyS/tbeo7JD9GEXKZYqiPap+rCnIVLUEbZVVbo2k4T7+92VldcWqalM9onE430vg/5JD52PPKWkU3/tyFUxJz+R4KVD9+P+EguWO9P8KyXL8BmrMs9ryeRZodrqsbuK//AuX/7mLIcCevm1jODOUPPqDbIKk4DIt+4dknOe/PzacQYTmw+6Rb//lZRatJ9w+dP+/ywi983u/kubYoL3oZUyVoVFBVnd8shTJUxcAqqvKJbslghhognRpxCgCojnnCJrMptvs1136m7UozC1dqZpWyp5WflWwjAu7iu93Szsqd9+PB91MADKc2WGYASrtxqJlyHkaJPPuT6jOmvQ5KbV3pZjMa3L/wuGM3kOZMwl70nWsktboPTRmaaRzunJBdf07uYqzvGVTfgzLr10rg2B5G3DxoLqGguLrginqf80K4AS9uK0w2m0mIUrQ6NwpnxapYei0zgC8rDgct4rCQzX7H4KNShwlfBgTe/+vZ5VceSFKYhop6cGIvRLpv4qRPAhG2XLic4zBeLUZItRwhUJZDMuzPRCJAMswrpNxX
*/