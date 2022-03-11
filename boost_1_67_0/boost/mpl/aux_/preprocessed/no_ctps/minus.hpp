
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
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
*/