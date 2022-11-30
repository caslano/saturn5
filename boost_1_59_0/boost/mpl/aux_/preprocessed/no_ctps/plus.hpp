
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct plus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus

    : if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct plus2
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, plus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
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
*/