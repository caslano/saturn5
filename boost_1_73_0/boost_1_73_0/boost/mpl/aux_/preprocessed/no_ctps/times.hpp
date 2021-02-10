
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

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

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
fcDmUXw7YMm3aA6XA/ZpESdH2GLQbQZI88Kq1/uuA/Tmd+jtEYRFFZp1pkkTzcNRVweG7THobYGWpskF3Ia+txXL/wYjX1YLEvVPrV1vWfDD1hU+KFtTfSS59l0eoBKojaKa2CBU6Artvbalh/F4/AzWZDJ5Bms6nfYselJLtV8GsFkfM9y7GbKYLMD3unyAd6MXcEirLHoobQCHktYDcEvH4Nl/D3+IB7ohdrtK8KeTlB+uuR9QSwMECgAAAAgALWdKUkP4SPBzAwAAuRQAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NzZVVAUAAbZIJGDdWG1v4jgQ/u5fMWq10u5J2SQQoBtlkSi3bLl2Ayrhbr8hNxkWq0kc2aaQ+/XnJNB2Ax9OLVTsWpYS2+Px+Hk84xdPoVQhldglHkvnXH/uMV9xEckuGQRjsmJxFFIRJVSFCzJXWcykyqiQKIhnPsl6ZtWdnMMExQMKQ7IIiScwi3PdHFFFC6ntd1Ovxfsxw1RtxMOyoAVkqaRbjKiltyVPcR53SczuWp22rq+K4KU0wdJe2NoLEV+lMacRGCDvWWZWNs9CLgSGKkUpzf709mY0DmYD/1sv6F/NBlO/HwxHPryfpmz9Qes1K8XghTxJaBqV
*/