
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