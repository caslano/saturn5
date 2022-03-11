
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