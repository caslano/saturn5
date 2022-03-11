
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