
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
onWnQ1TRSC1p3w3iqWju3tSDlH9epT4yYz1b5lpADwJ0NbtSmvCU0gJaia5X/kq19KPlYzXDtef1zsPyYPmUA5P9L6vVv9TSkTU5wKrm0Eb5muwL1rWcW4+T9jvGGZ6JLpevaqa1BumH0RpMC99Uq99mLObdrXwXZ04eLZVr65vJ0Q3buViBbaIqm/z2z1O3bmG7XAtepbjCkzT17HvXRpw7NIg1g6KbTBAiwH55Kb1qCmCIP6kfk1455BIH7j/UQOIctumhsrggVePXoCJ6Yc2wVx9Xy5FLIs32nfTTnsUwtzZqpxOZdM3M/EQu3UR2taRtbVqj2UsHZa2isjodsQu5b8PEBw1T00zwvxY7E2ILXnFL802Rq54qoYpbkkpcFFHN7x/E1R8bgwIKFPdd6GhiLDdK2bWSyjzLfskNmLXZpi3tOmdMmzQZjSV7G+nevAnAy6knpOQ8IFV/26l4269dY8G3i9Ac2+I2gBjRvhjUDCArt0mIzKFw+ijJrQeK8cFJfs81YYuu3zRwU8ukBMkSLnvl3qzCHx3MVbIpMvqhm3QNO/dMiwibzb1NWD8Pp9C7gAjT0x+0KNQbv3lmQNhg61+Bhzm1JuQGfMeT81b3s03lrZHArUnx+oy4v+j49aaR1k9EuiePZi0Zz0e6A2tWETZOelAB26SsLfVx8ZLunNqQFzvNyyVQG92RHKfJZecmG0cRqwgjr6FG
*/