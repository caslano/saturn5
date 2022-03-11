
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