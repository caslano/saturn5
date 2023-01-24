
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

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
9hm2/2FGLvX+8tEUx8gB6mxZXF9Vu9U+dux0/qj37Mw+PgMx2DC6pyQ4y4m3uxPQ4ddBfR+YYXgEIZ9gPjm+1Bo7KoQ3KkLG1+pQRWHHn48uX8hW4L7qJqI4UDGLvZJNMqMN/9r7eCF9f4hG1QVQAAe6KX3RrgRqgkt/bky6BCVgHj+qRyJSvry8ue86qs95AwCMBAgAPY6qAJIbHTDWg3WB2r/GxG2OhSyVU9OLF9orjlD14+dNA35WgxBYZDiEMGbgH5m/X+XYNO9/jouz/Mdx8f9GUTsajbjxJJZ8jIEU0BpuU6p/l1VMZ7xOeMeUDflwOc7w+fuX5DJaZYz70QBqYFC35fZmVpGOwMiw2t5gHK2A0rokKn1I2t/mxaPXy75YCIbchpZIfn5nh1siOa8Lnaf1Kias1GLpnfoN7uIgl0jgW0MZZT/qgWbmZeXl5a22+wDuM6qD71aX+WFv3pVYaqBcllabK6qRMuNWEqLJLG0rl8+reUCWT/WYoSmSxV6fi5caw7a6j9KQdJAWkZTR7dHS37Iy6Es1aGaHEO+XCFdJaM88nN/BRfJCGQ8FT3Yi0XqcMhk9kT3KWjWSV28diTgW2PEvXMbAkhQ366YugSIPYqzHsPumSkR/KoTi71j9L0iKbhG0TXLKZKzMCkc7INQWUWAzblYAuj+vAfjP4CvfivOCcr6OHabjUusCqkv0LRrMQxfck50r
*/