
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