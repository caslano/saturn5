
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitand_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_

    : if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitand_2
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitand_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
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
*/