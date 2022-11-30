
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct minus_impl
    : if_c<
          ( tag1_ > tag2_ )
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
    : tag< T,na >
{
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

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

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
    : aux::msvc_eti_base< typename apply_wrap2<
          minus_impl<
              typename minus_tag<N1>::type
            , typename minus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
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

/* minus.hpp
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
*/