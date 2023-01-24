
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
T/tK8yqw0Zt5D4zCmgy0z3l5pJRNuPrWHBQ9otdUNFNzLC1n9IyMqtnkfvnTaf8Re9XG9F0NCY/5qyejWn8eLlcHEde6akeHgeykDHSvliapG51Sq6WbT7d1Q8Ija9yrBQe3iqzvQOFRQpXkeN/1yyqKK1eaS58m6vM1ln67pnHhqUtWN0xllPSnElX0L4BaSxk+ui2rEb1UjNyTf7P8e9+kEIfd1CMFYq6ygPPh8VABJ0yuwxylEpNcEv9aw8BmsfFWuumboL7nLwp2yJzEnndbZOVF/Gito7YUS6XbAGES0i6et3se6FK1h8n3bRDTp71m7ApvqVS46AjvPLnFMrOGJzP3/ap4+24mW1qpGlupQdtA4lE2LWme6sfyo9TFbXz9Un3XjJwEZSOsFYu95uCtraSiHwVF5swJQqIVPqzg3upVvxWlkZQtWPf+WANrMh6I1yy9R/uPlX/sqxoGtdn2X6Ac2ji9FB52FDQvl3V4KbRv56PfBDpv62VKusZgTDZI5ygC/1RmPC3p/JRZbiJPSabuTRRls/3T0cjzgfDczsNbf6dsODCsJHruqXM8/I6PZn3yiU5xm4pdH6RhAxtxO56LbukZkcjxVh/DxHxQgIGwHbW31n7cQTNHb7v/eN+vb8PHk1yuf5Dy0MnJvx9bYrSqf3xpd/ldL/qZh3bSYzak/ejbhN0P1lTVUMJAcSwOAOY8+nFN/kLT
*/