
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , divides2< N1,N2 >
        , divides<
              divides2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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
+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
*/