
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

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

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
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
*/