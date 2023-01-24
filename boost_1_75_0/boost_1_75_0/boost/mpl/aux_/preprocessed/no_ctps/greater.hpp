
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

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
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
obvjO+NsZURbjomIedelFsab05ESDzA5zzCNZnanvBcWtqYZBRfNZs+PBqK839b8L+Zk1IWYeM1zuTqbbvPoZY1hfT7tudO17/M+8wkDdaO4o3gcj8qqvlR9gnb6Lu69MzKswmPYdZTeS5TO5y4ylre1Ta+U3y0K6bSqDqnqhswJuVZrm0Zke6huGVUNrSgt6iqW3yml2JIsGii0huGf16Qo4dzoS4uJ5oe+ZODX0OpzJZoQ5egSnPRqniixZKnRaXebUkdrK68xyyXoYPiUPmVDttX59pR/Q4t0fsCOlRZbhHV+wkpUdTj60vmZc/msoquH/ilOYzOTmsprZ2hOu5sXVyMFobwLmvP2A4hcpFkkjvVCq1Tb9NAhjscq1jnvM0TSHx/HcrmwoRaix8d6ui09MUcDl2JI5+5rGVUPkej8By31tBDlweD0wGVMpqrTv4nT4yekpDwatUteTK31BbM5Fb1SrS7aECtyXmbTfljpp6vZk3WyU1Jy5C281m8531lFdIDN4l0L3UuYcCo/zjutXtob65SQZjWhpFTKHDqgZicDwyPRL/5DIm2YWLJpxHT069Kb55GsV1PkZ+M0rkq68ZTX76U3VnLuiiad3AZpNWrsqku0GdZrxwOTpceuo+5jI1Nt7x6sGfsef+l6fqG68Nv9xFwf+kFUTZil3GtV7rzt891lROqM6kX5L+alqEd811ylF0UH293c
*/