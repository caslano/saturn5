
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