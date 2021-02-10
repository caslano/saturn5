
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
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
i1UtHN9bG5Z2WR0CLxmW0Y5lo+nBwSihce8rAoMe6RF9tWbhw3dMeCn41f+3qv9ZCdd1w9NaOjinbyrpHLyieHfAKvv0J6S0tkbzzTErBLMt6mlCXsznsxPCzaq2mnhlZ+H9Y8gUWwrfI6+RZVtZWTNj4UbaEt7e1oLbFEoUDWq1bZwu/VpYrwB45Yv8GsFCjwYZ10ssdj4h9BYcuTQMt44R/mSWbrlYs7PzxeaBEUttRakbm46Gg34c3ojwhikb9kcJ0HfgMMc5U1JU7mi1rsa8Nd2hkJUY/1jpy9CNAzrs2lsL9CO0bYvVSOu6Zk3j9hM82lxAjyHYZIdDSzn2RKpWBFigO/ov4RcBOC84TLhLZNMFxN1RaOOXy9oS8JFU1/pK5LhNOqOOdvCIWjAhhdaULBwW/jBYuuMFM64t6Oa26Ka9GP2TMLJYgZsKYIXFDrig9ovlFzSltsj6urN1U2GNrCfk11dfzuRdZ0Nkv6QO8/B32r1e72678fF+GdbJaq6rCfFb82+0aaOVHjl2BvDYuEc+Yjvo9BLppOC6F259ens+Pzn70CNTzkWNX2+H2721ipG5ws5IrVJ4L0RNp5W8Fj3yVMO+ltMwSh4L8qnk4UK3KmdmNabfeO3zvcEgH/H+PhdOpt+yfWy9
*/