
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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