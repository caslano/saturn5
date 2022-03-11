
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