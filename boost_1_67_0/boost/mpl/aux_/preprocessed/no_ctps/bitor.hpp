
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
+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
*/