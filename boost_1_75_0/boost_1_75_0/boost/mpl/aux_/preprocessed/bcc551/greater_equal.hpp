
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
+kHmmlPFIlNsuPcuAHiCPa/6ds6XBFt6nl1G4z6VscdkGT3GrHhZZYiMNwOpulElm12tSpk+c+5r3SLBV/WK4o1/MFqiO+ZdZOcfvslf0ZDp8pbputIu7lEl0Cl9w18guzR8Nz+CEJTfBIlDCCq7TyCsSVvHiY4IfAF1gVegX5hy+Kao4K/ln6p9B+YPTo0yr+Ay7UMyjRCF39pfpYkjGzDX868z+z7zwPNTZfMgipJZP+nWaC2nXbBYw/t/fbv7Y8Yd27b4jkzQIvEdVjgo+Kt7JDPqtdQRd+iRXvR61h/MGzGsqso2P3yTJAhLD+Hf23rUC4cw2IpuFaccZd1EgFlEu870KmI4FacmvEdSwMwJts3lo1qViWC5JDaMCA9OYzfz7c/9g0DTtcy4FuftN7u6Ji8U44WbBlmQpk8dZtt4NRehbAD5yQh2cIROtdmUTN+MbD1buV7pRIFFEtqLSl3akwumpbRx8XTqMWcgSmvQDacojc74K91qAXy+KnJbjUjnarI9K1T7ykDyCf87/X1UgKcngU3fEkndksETjMjlcUPnCSaIVJpD8GgjXOE6cPv4NRIgOU5Kq7GnF8oHCpzfxPHAX+vWfv6Q74vMuH31DpyETJnjxx7AcMCTQxZK28M3uNTIUECm2MvvqDj1q6yveaCXodxRSmtr7vVm+aCaCquqIlMh3yB7ZnJVXyyLnQRWD6S61wZTGV/R
*/