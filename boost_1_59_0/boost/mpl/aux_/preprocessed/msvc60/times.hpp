
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
{
    typedef typename T::tag type;
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

    : if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

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