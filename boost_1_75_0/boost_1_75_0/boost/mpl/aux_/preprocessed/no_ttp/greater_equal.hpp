
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
KxOW1YwG3zhpS6gebY/OPFd/dD/Nmv74UVrrwt8JvLt22uENa91bqV+5WklzAUhcFoWpmzxIUicJa9N3xnEXf6PNnHqtzRQs7Q+JUysRgCMYZk51UURdUhDd/YCxwYy7jucaWKw4iU+UMKzSrTt0/ENRwMJH0L41wVuFoXeU2GfEmo/wok89gmEX9e7Zg4OSSVZkwMJfUHc7hs6tF4cBtAFqi7cWxT072rhyZZRLHFYuoRR3eZofzd9uy4jxBt9bWUbquzMXXPp2KckkGa2ers38bloGT0jaJSgU8vNjTb7IZkhIcsEdK4m85+KqlkjPKjGeTQZa3VVjCtocw+p2gkZPO/wvLSZ+z559YDraE7Jgv7DBUIPKD7u0wtu8fC9KHIEl7XUXwHXjZfAyOugh0b3S/wOUhHa0uLCfdnHSgak6ISEJ8p21vdp6e9J75aQDLg5PT/fIP7BbhKUy5ty40BN0pNQrVzWgUzDZnwh8pMfYFtwVgigdSAtmLLLIumNcPtHDqMIxlrEf43nCicX59G+cnVVQG1AWhnEKFNhCKQ4t7u4OLV6kBYoWLe7uBIoWd3ctGtwhtLgGh+JOcEgCwbPysLsz+7CzO/fx3rnv3/zn/05m8GAwRR9RX0tnrUF3BhHYsXg/+ASVHYUd1TObidRguI9XAB2E6oJeiFn/qv7HrcP7ZnlYc9zOEzK91d+/Nm8jMMjesJ79uC1X
*/