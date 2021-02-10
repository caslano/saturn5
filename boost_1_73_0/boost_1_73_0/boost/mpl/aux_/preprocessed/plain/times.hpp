
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
og8eAgH0wUAgpX9jIpDav3EQCKAPBgLR/q2xVriUwvg3FgIx9MFCIMq/+aUVu5Si8m88BFLRBw+BQPqgE0jp35gIBPg3BgIB9MFAINq/eaUVu5TC+DcWAjH0wUIgyr/5pRW7lKLybzwEUtEHD4FA+qATSOHfuAgE+DcGArHSYyKBaP/mlVbsUgrj31gIBKXHZAJR/s0vrdilFJV/4yEQmB7TCQTQBwOBlP6NiUBq/8ZBIFZ6TCQQ7d+80opdSmH8GwuBoPSYTCDKv/mlFbuUovJvPAQC02M6gUD6oBNI6d+YCAT4NwYCwekxlUC0f/NKK3YphfFvLASC0mMygSj/5n+91FaKyr/xEAhMj+kEAumDTiClf2MiEODfGAjESo+JBKL9m/f1UlspjH9jIRCUHpMJRPk3/+ultlJU/o2HQGB6TCcQSB90Ain9GxOB1P6Ng0Cs9JhIINq/eV8vtZXC+DcWAkHpMZlAlH/zv15qK0Xl33gIBKbHdAJB966QCaT0b0wEAvwbA4Hg9JhKINq/eV8vtZXC+DcWAkHpMZlAlH/zv15qK0Xl33gIBKbHdAJB966QCaTwb1wEAvwbA4FY6TGRQLR/875eaiuF8W8sBILSYzKBKP9Gu2MTKkXl33gIBKbHdAJB966QCaT0
*/