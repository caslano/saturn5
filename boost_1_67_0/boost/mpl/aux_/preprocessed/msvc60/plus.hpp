
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