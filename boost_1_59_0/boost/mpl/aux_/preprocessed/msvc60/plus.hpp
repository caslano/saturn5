
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