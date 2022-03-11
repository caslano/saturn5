
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