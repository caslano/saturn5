
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct plus_impl
    : if_c<
          ( tag1_ > tag2_ )
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
    : tag< T,na >
{
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

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

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
    : aux::msvc_eti_base< typename apply_wrap2<
          plus_impl<
              typename plus_tag<N1>::type
            , typename plus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, plus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* plus.hpp
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
*/