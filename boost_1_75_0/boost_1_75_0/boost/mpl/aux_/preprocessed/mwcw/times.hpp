
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
Qxi9Xav+/NAvSMN3rEpJcI/g2nIzo89fn0cDF69itDtMRntc1u31dljfEzZEkXio5dfVkeo3+zSOkmbTNVqlt00o6jO378vHmWZb82a11ZMwqokxJtLw2iRUHj5Oep/7fKu61OczL3+fmMnZYmdUxDdZvwRpGnsCJV2NUZoSuMQITxOwrbQQiaCAO2PC97cp1Di86rvbS0/SKLvEw0/OsjINkkUCEI8eW6xMoB8elrJ7E9N5MG+SWJBisqiXk4j52ZXUKOfd51pe8y427UpVMcczyySRi0+lpRWgNddyoxT5OEawW7HCJA+ZFAWn8fbveLspVaEAzYwZbzfvRx1VJPj2t/SJ6eCxCaLvct6Lgx1U6CHWTY44Bji90V0FK86FrGCMd5X0WGQeT/25S6Uz7p2xd9piTHfPo9nu5c6ZYROG7U20Bhj8RN9TvSIJoXvdiZwKvaX0dRRjPEe69YVCDexKZcXNxz2x23z4CrRZX2AsqBw7Z/IsXrzrEuiQhQhE9NGd4U2zECXxb56D9fJzEqZSXUnh+Tppc0FNRuFe/m2OAr2zEo/xFSXYW/+0p6KU/gc7v+v5mxAtmt80O2Ee9AXxUd9rdnbrtXtkjggVh0hWjMyYPEJW/mQdE6ldscEZduTHHHA4lNXfzbrdJr2MX+11Se3JiB8cr2PAsXMVx9HvsUWIjA/WobLSzT+/xnFUH3zOju380sPH2cPF
*/