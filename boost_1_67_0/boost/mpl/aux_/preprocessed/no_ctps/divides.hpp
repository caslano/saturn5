
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