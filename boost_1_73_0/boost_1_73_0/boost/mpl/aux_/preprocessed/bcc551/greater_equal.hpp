
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
ci90ZXN0cy9kYXRhL3Rlc3QyMzFVVAUAAbZIJGBtUVFLwzAQfs+vOCo+1qybTpCsoFVB8EEQ3KNk6dWGtclIbpv99yZt14n4lLvvvvs+vosg9KSkx5wJbSobni12R+tKn7Pnl9cnJvgZEHzgsAt4R3dAl3pdIhMOd02XBzRbwqYLkkAWVI1qy0QpSfZlzh5m2XxxfbO8ZcVUCf6LIPioFKSKRqOh0UD1TSD43jZnlW4CzE8tCCNbHOA7zuGoqQaHft9imPFhKJRtW2lKsDvS1qwSY1NtVLMvMZlWG6tkU1tPlzH959v6MUBfPJ5pvsiu6JsgLSCbBfNRLgjHXYgmq+QPOQjfT1n/zx+XY/RTxpD9A52uOoiXAVkROqAaIcpCLT1sEA0kvraUMHHouVHgXJ0/9QdQSwMECgAAAAgALWdKUvpKp9zXDQAAsR8AAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMzJVVAUAAbZIJGDdWVlzo0qyfifC/4HbEydiznFb7Ag8ak9oAQkJhARofRgHSwmQ2MQiCT3c334LLZa67fb0zIn7ciK8UJX5fZWVWZVkFY0cZLltZuAFafjRKob/NqDcx6mTvSA9wxid/qBdwUDsOExSkGXAQRrYTamBnXF/
*/