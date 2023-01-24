
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
UE7dCD3riyfAukj+AcUu6a/CyuE8PIS2wC3OKFd0gR/4OK2jciY2kF8UloBHETwTmwx6IYoFKk7WVSat/HZPJUS0Ctor5UypVGaoQksfRAwfwumHvDh0Etsku40My41rvs2vONYOMwKYCSyuE+dXI6N6rbjOYEMEzoTf7UoPCQlLR+buHT9fmnzTqv2J7R3tk+eDr5Lx+Pzc6nIJbzadzFSdf/6OuIYfwBFFbF6iULcbZD64GB4C8QdQzgZxdOK0YaRSjgB2CL1oHqb6/w3Dg+CID8ghrkwIbOYe0VZqq8iTkX6kF/+r6UixWv/hj/DCqzWiIHtyBJLFKyRXXaVlFUjolj0K1HioTRV/RDH2pOgeBM7Armm+mzDCIXfCmQ5kiAN/AUN4oMI3rjhEzV4y1W5Mj+go4rUj9nqfOzfv1eAB714Pcn110/0HDpqa7Iwc+bvnE8rxtwm722o2k/3hS0ArxaeGC1HCddyNeRE9dn1RnGdTmbN+MVfdXGYEn1Bv5hPiz39DdIYQpha1/5li/i/W7n+5xf62UGXj+k9Md3QiXfUW9ZWPw9EguGtkORegolVsHRrV/MgYWyJ9FW6iSCXjaK/IKdMgu4UrcOURXZCDL1OtmBW7fRgdCZA1ao18UxO6TSAfM2IPKLNz6BCPQ3MObWNYaLULq/gGkxqrdY9fUSBt2Q2+8BjK7ojYHBG/GuZ7mAku8JwVOdnK
*/