
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct divides_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct divides_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct divides2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct divides2
    : aux::msvc_eti_base< typename apply_wrap2<
          divides_impl<
              typename divides_tag<N1>::type
            , typename divides_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, divides2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct divides_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 / n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::divides_wknd<
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

/* divides.hpp
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
*/