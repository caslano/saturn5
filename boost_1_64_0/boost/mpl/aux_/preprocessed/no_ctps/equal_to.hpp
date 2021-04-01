
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
rFE5AYS63htlFdihOGjApZS19f8Nwz54W/QWRlyQdCH1yxN3pjp0SrKBDPlxP1EzeF6HOFy6k2r4AXJS8NzD2TG/hBpUhAbjNhbF71PIsU/WaA8NRKglcx0trx4e9rM8g5NsgMpYHMs+PLakDDR0i6OGX0LoH8rEp7aj6t48Pt4taMKOocJyz5YUpPHkQly5QGK2xp4IRghe19nMwFyTnB1MD4XzG7taPbG0BLWGh5QgAGc9zA3qcm+5HdaObpktRLOwKce1whC76vfK7woBTUZFmLT9DIiv/3VmR+ywECJIzxY75Ufhg+ouE66SrIzLB+C0bzVjgy6NVG6qnbllJDkbudgQE2Vkj20hos2J9Y8J/pYCkn60KtC2zx4WJmj9DB5jaHDGJO6xsLT6RR5J5xthXHD7oFkIWSHu1wuW+3jP0MgAwDu8nW19F8x0AEJfTKG1kNplfulXMpXYIC8ma30Ju3PC/zuPsA1BylT7Ci/PzXTgWf/DPHR3IRviiAlBMF+W5wzuZ8ZW3b6QzjG7VOYYHZsVb1e6sdNCdtysi6XrlQK1H/5/geHv8w==
*/