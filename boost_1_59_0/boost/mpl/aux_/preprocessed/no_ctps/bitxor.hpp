
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
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
*/