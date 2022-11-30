
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
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
*/