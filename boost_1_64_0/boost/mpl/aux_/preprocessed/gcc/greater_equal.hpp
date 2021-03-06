
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
h8VOVCRwhq9XyGQ32rtQJ24L/kZEwZcsuDaMhFDpPwK37w9ZmR9aIOlCBSZQj5zr2NyiQ0eqd9CJpvfsZvwKkonV7m77aZJ3uyNwl09lD8nFKW8LfLPLNU+K7SZ5UwMprgi9XSnZlCFhN0pRoRd4RfIZFG4fvOHbfxKJJTAMwHN84mT/FV5m3XI40Ziq4Ap9tlncKnWnmG6uoURY+fA7IecFVqktSwf+LBqfio5z94/2vuNvNCg/3d0hqTJYG58CsHxAuZaNEBaDw/b5hiM1gL8FvWKG+cRa5WJfbfLNyrJnU75Soncvq8DHHp2VVd0eKTYf5jO/8QN4IFHR2ebW6/zulfK5n3VF23ljbQb+OeC/SFlytruUNZCxi86F9JHeH4RlulbU7ILPeDFsh/1SxzqeIzy3ECqe0nNf2R1Byv7ZV9IFpfDcvP97F6s3mEXsHAerejCYnZOBjrCk203BArCZOeDWnXEdZFTjnw/Q+UXUzpd93T9wSxZ0HOZk3JhPxlFJghrKLuZRrUots9+VAJmgsp4+FTmxUZZ3JgjUK2kdGLm3E33aWc2B+Q==
*/