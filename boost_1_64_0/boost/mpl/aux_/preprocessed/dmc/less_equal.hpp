
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
K9fVao89J08Y9+JIujY+0lX5ma5W0rVUpHvMnY5xSMnPR7r4tfbxZscb9+K48vORzuEl3SfGvUwmu/bpyv1MV+Vnulo//YtY51+6+HX+2U32kV/sBXXxECc9QgwyZAtSiVQjqfwe9ih7RxBvsRJHVLBnZSH7W2LZb7Jbvcdp70LzPqdj2neE/U7KuIg5/L4EccVG3L5IFR8RWeQ9RuLpRXX7oiIWs8cIccVKzF7M78i8seQJ7eImli92x048sdi8l6rJEsqNJCCZyDakEvHcY1W7xBxbMfouia/oseeqhN8H8Nt2eBAxxlg8oekstcRaZM0HduEA6BlzMWWpOe5iBFyy1Bp38eBS0sLlFdjh73NIMd8jl9Xt6RoAXfEYlyzziMm4zB2Xce8yd2zGGv4OW66O0diT341xGrOXW/eEHYsNtcRrrK7AFmn3IOe0v6/FznL3nrGwFYZ9Y7vNMRwHa//j71TYh98d0BXPcd0KdUzHPSvccR0TdvuO7RiyknSIg3xToXEvWgnfa/leASXWo7437SC/hWv7zlYGL95jn7t9x3xMvtt3zMctd7v3tVXcXbe3rQZGrKrb49YT2sWBTFp1XkCxIAtJf/o6ygkH830PdMWFPGuIDRl7D/UEE6AqRuQSfnfALfBcKmnhCUTbPxe22ho3Mna1O3ZkfAXlWO2OIZm9Wosj6Y71umo1Nvi9HBrjSlavNseWjF6Df/SbmcgSZBuyH6lBIraFhvRBRiA5yDpkD3IMOY3EPcb/kGxkObId2Y+cRJo8zv+RwUgmsgQpQyqRaiTkCf6PDEYmIfOQdcge5ATSZDu2kWSkENmCVCInkfAnaXtIClKCbHuyca9g46fx0/hp/DR+Gj+Nn8ZP46fx0/j5//j8EPH/Mgp57/JkLQRAw+P/DY5irskdA2BoSsq4kddNSEmUXfTOPfTNKY1rT2GZzDc9JPtlHkDOj+X3Eue6K49MprD1opBhcN97frR3X8ctJA+Pd1/LfiRZfybvLi7ML7zdkVW3Vl/2+sgCL30d/uGW5vcZJ/CdNKb16BGKeAAXUBbHQkVZAowVeFgRK7BEYe8E/ylV2QswVuBhRazAszbxB8pV9gKMFVjW0T4GQaoiVuCF1Gulym49YgWeVMQKbEr+1Qv1/SlmG37k76rHJrH+71Fx+ZOtiM0XTj4Ri1z7Curvz2Fv+ypkLeTJMOtayObYT1jkWgs5dPyY/mkpE5MTA17PPtxjHWRCS1mHKusgK36AdZDq9YuBr4P8X1nv+H2vawz0/dGBrlO827lO8YkLn79pydHdz6Y9/sJtv3rp6kHBW6eoXhdrt37Rfv2oNt+1MUSuXXJNi9BswlWI9ukm88DdYSTsAWNgL4iE9IZ94aVwCOwDk2BfOAZeBrNgPzhN1q3cIetWSmTdyipZt7JR1q08AK80zlMudK+fivBct2acp/SSrpNxnlLSNVWk62h8z6aka+0jv2pJ19FrOukPYYyPdAmSrg1SjEg6/T3J20OZx98R6tc72RoSQ7Eh71izvl8tOO9WO5gcvHeq1ed9at7fo+bfO9Ts3532/b43jbk05tDq9660unmzwN+RVjdXVv93owUyF3b6Ov9iQ/r7TjR/3oc2gvMwBylFdiFHkLNI7FO8h+ypxrmgxs//1+eHiP+XkdPw+H/ac31rQ2w81hpbYlFN1AI1O5zPEGMSU8YPG8rzw/jkUSPTCqZPywvgGWYC+RTDVoY96Y6ZWbcb43f8jDS5mabnPPZwWGMH3RzL7wqfZKd8QD5lQNU++es94vd1EfudkFvQC5nttJ88atj4K9NGjh8/IXFc2tAxw9PGJ44bOZQwadOnZRX48z6DVuLLa1g=
*/