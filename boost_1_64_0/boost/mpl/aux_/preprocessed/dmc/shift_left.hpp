
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
1zOoYQP/djVtUHFmGjoH/2eNDuumybyqKJr9gIWemKY5edqPM8AGZ1GOY9XMqe0UPU2scv/iGaT4z0/sYxRRYgvy/mArZrNN5W4zPbNegK6nY2wjAQPoXukXQXeOUn5ZkftE1/oL+xb2oR47MpRkpKvheJlqHTy2O6wCUZdu5iG4QjuGzX498pAAZHXT2w4jtNy5zc2c5n5vV22ECONbjyC8w32vIgS0GoLDiAIHyCdU/zg6V5C+Zl27l4pbEpnLjAIHNM/+Y2z5y1ynxRKF7DvR2NmnHdwwXScikjALURiZ/o5UH6pf86zEtsq+Q3S7CHzhjfeYwftuZKLbH4qsRWHewlmZm1pkVcb8D5J6wXWcbciHpJjlwl7DtwSg5JZVUeCLcWG2L+ikx+5GpDWDeWUHYa5/MOKuxl7AgDSxQyNbkglfrLOgM9WlEmj5uCzBgQil4g0MgcqT0n8mqyWM/JWRC1ECJVHRA2/VN422y8VaOn284/ha0RWCjbdnYHI7xhRauzG8/tAR5n2Cj3UA4J0dCOfF2ohVC6U1tSLCFCSw3NIn2Cq0lPoMZg==
*/