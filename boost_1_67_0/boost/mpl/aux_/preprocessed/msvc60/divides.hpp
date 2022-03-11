
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