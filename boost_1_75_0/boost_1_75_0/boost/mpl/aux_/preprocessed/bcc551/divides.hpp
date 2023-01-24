
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
Yq8sGdKPPD/8iJsqT6zPEBrj3QxnR0oupPigfA7jj1gtjrppb953x2+o0oijZl3e4DqxiOGxiGEIiSmo9jVYIol3p4rj55PhKXI8c0yHNld7Guc+dCv3eHYPXFWsYFPIPa43gUnLrMefM3q/lIP7CdVdsceqnofd2yIpdFm629WLRb5gn6cB5tIUHmEWWiWhT6SPQLiW95+S0NSdBJKAR7ruiLVa4pGvaCloUUCJ42zrEQPyna9Nv4prZdk9Y9dUcVqoA7T44o/e+iMMP5C/OFoGrYKWQOuFhBsHqupv/mwv8+HaXcOuphma1lAUe75NfrO+y2yykYb4JlwqUoqrdxYDMHgmfW3fzp3wY/RPG1sCwkaPVRPvGpKauITjd7DG5dY0Q7pclMUVlAtIRUZtr5PslzuER7TLcip3rlO+xVVSNmmlES2dHmXsCAb+VmnG8Rke8Ey0++MF2ErzSIleY/S+rZgulJI+l2WXklL3dUeLhJgny2oqy64p19dkDwVaqQXKKzzZhma9RJCq1c9musTTrUS4XOCOxpL2KOV0EdecSWFuSE+7WqdWDKlvXWEC9rAwNovLJUEZvv3CVnmOzQ5PI8Gnn5PNQHVhI0OVAm0H88DW3C3vGpKk9tsvkolBueoeNXdGQgdkiyqzwe6X9PCpAogLkcCrNkcXFbCAv8PElbGE3t2bdE66OTIbLojEOBCVnPyUuEf3BSy3
*/