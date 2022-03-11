
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct times_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : aux::msvc_eti_base< typename apply_wrap2<
          times_impl<
              typename times_tag<N1>::type
            , typename times_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
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

/* times.hpp
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
*/