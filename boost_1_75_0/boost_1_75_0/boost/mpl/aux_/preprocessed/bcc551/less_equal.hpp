
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
1P9IgyYS8qd8lBztl6NJOsM+8PiUVrOKP58iZz4iBpODAFhLuEkoZWQOcjzA7EbRwwchwX9MgwfNWuPq6L2J6hiZzqwxtaTKkkYfveMA2PYwB6aphhgdY52unV5DoePxhO1mON/jzX/2bLD2h9ZAB0UndUxY8wFwuWRZhfw+sOpNGGNU0JioWd+MWQLFJCSacbjwFhXYfcJvy9/ln12Z79m5PjnHNzHp3Al8Y3dke+nmUuf6uvVkzWdUbmjK34Y+QaYGvWjGk9ucGZi6KWygdjmyhdkcj6L8eavxXIh7xn0JVFFj2tLQVM//h5gLWdNxyl/SIJNHqRBCM5wHRTNWOlhgfNeB2CVQu0EhswbN5w44Edohagb58+0PtpUv45M8drqDXyzWO6v3hWbkCnKyyDuObRfn+ZDA6u4sxObXzLIm8+UrrqXzy55LYzqhrZltZtS25FYagWGFWw4M5lJM7nBrtlsZ4moZZTrjb+1O0Ouk0qvuHnhqWvVV5E3wwpIvFAoB3jQX/AYCyPnW5jRYrpo+eAP+YDsy0Rf8hSUkmRiNEnC3HQQdKFlUXazZUIM6WLM23AzNCTB6ulmvB5T7rDSn6XINzxnwVC2Wt2FDby70KDeaBKjU4+zy4mVdc5NRV8JCd8xbHp+HVOwqHZ1sePyAgMF6WMKFulPxhQ/2gPnvO8+ke90Zteadx5ULT6tnJ6s2lXYZFvV291f3
*/