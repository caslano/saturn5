
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
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
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
*/