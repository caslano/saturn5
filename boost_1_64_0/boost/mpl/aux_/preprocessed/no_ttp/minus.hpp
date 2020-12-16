
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct minus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 - n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::minus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* minus.hpp
/Bo34Gncgd/gLizCA/gP/BK/x+/wLJ7BH/A8nsOL+BNWqcnnJ/rib1gXL2FD/B2b4B/YBv+J/dFUlXLCqjgcq+MUrIHX45WYi764AOvgZqyLeVgft+JV+CI2wFexIb6GZtyPjfAL9MPT2BTPYTOsyed1ALbE5hiCLTASW+IYDEQLtsIbsDUuwjZ4KwbhFmyLD2A7fB7b427sgEexI36EXbAan8NdsQZ2Q3/sjk0xGPthDwzHEByOPTEGQ/Fa7IXTsA9mYhjOwn44D8NxGQ7AdTgQH8RBuBMH46s4BN/DoViIw/F7HIHVa/N5ii0xEjviKOyGozEUozAcx+AQHItXYzTG4zhMwfF4E07ApRiDa3EibsFr8QmchM/jZHwZp2BMOZ/1a4xxMMY4lDXGYdgc5kskrCcYi7EYi7EYi7H8VZfql6P/n16ryuj/b0HfgW9P2rSaKeP97VO42JhULydjuszJxP87s21rgPr/WZaE7MwMVrCPH3jGbHL2e3Ndbl+GEqoRBhMGNiJ+8fiB4ePHx6VlJiTFyZbIS9nzBEo/Bu0jnvsx9Nv7PbW7V167uH6/h/f9DJ76QybZ2/vPbOhWtOOWvGt65DcP7bXm6e6e+z2K72OV8pbjcJYg97G6PcthBLbAkdgVIzEcR+NgjMIOSpvSAh9TEcH9t7z8jq+E+cDLMxd4GfOA/8fnAPe9yfjtaizGYizGYizGYizGYizG8v+4XJbr/ySLNauSnv+/02xyjs89Idfvmwh1CBsIdZXxuStKG/9vKscc8TWuClupmV9aZ+y/LwZWdx8/W9/D2H+zh3Gx/u7jYp1jcGOCWDchLS0xYfpMR3qBWE3ZRmIcUwS75pZ9wew+F62MqS3Xffv6YxU9t13otyFU3thDb+/n129b8DQm8X/3fv7l9raXHa90r/v8XW+uLdhz589tW22I9jSm1fu2o+I57aRuSZ0rrCJz2mnmZuuCzbArtsRu2B67Y1cMxu4YgkMxFGdib5yDfXA+9sVl2B/XYzhuwAEYVsH71v+T/bn/rr7civbj/jf04V7u/ttgo+3LWIzFWIzFWIzFWP7Pl8ty/Z+QndGjEq7/lf79cO6DjL6Xewft/fsTRo3k1t1ZcTabo///R24iWO/4fzST4HHxP9oyNy4hJ9f+/MAz/H9/yf87t9JUthFxn6xjbzjIVuLbt1+b/012/5/EdaWf7/h/dE5iWup0R/L29Jc2Jf0S/5dNyBiFXcochzLPYC2ZZ7A2oZrymnC2IeEWaeNQ70SqrczxCX7koTVluN1eBmmZtDEQTZ73I2nO95Cm6VZJ05Vx4pb9XBpHmv73a9N0PYvmlKQ5QNLsT6jfkyBpysFWnvFXZnqO+6MLKMfs1GS3dNLkGX7tJJ0ggpl04t3SsT/HrtzpNOhpT8f9GXZZ7s+ws2bL/koZn6imX8Zr3fNBMZW/fHPv9Vy+w6q7xrrUIQwiNCLfee7p8Ry28j2/SWln0ivfgxIxUvZrBKEx6Zhuc0sn25vylXTcniOWherniGWj+vlPeTVKPrOqiXKcXflgkxll7qur7Y8w12pxtv3JvfNJyXIvuartL0l137xZ2ghJzNnel1P8mrWK1wlwzfHpVrba5zUdlXuljsk+HSY0Y5/OuvZptiUrdcZcU/nmGt24zNHGWf79dLVxFr9nb+OUdc2yLvumTPXg2F/WLX1/z2qep3VB7iVPsmRpy8M556mSjlXSvSjxWZ803J9dxj0i9qWxnI+NCAHK+bhcyszxIc4TUk3lqGuaOVnd6nR+Tf06HahJy5vP6fX3lazT/Rz7Jo3YLSW95oRLfL8EF6eXFJIa5/b94M3+/cp2EtBR506xH6kZrjo=
*/