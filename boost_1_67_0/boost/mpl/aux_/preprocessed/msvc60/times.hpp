
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