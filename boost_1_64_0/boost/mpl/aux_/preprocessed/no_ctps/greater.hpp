
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
5o9daW9wBMr6cUW+xG3NWc/eljpnDd1+6e4t3b2QS9BdZ9dNYyXyHq1Nd3Q9tU5ef+nKQC5H1xK7rlo/d5PEv2ctXZF72Hrk0u0ocq+tRfSB6Kgx8HzZ9KbO21eR6+nMTdE2MfhP7JxNpZB6ZBnbH4+NvmZ6M5yvmR+u43y+toyz25D4mMf47mWcWLR4MXDxYrbixbolH3PmHOsWLxYtXqxbvBi15N9Pjhcj+FbQzvufmfzJFb4+H/52ypLRr2x841fxYtHix8Y9sI71e8M7+/Y7a+qVneau/XiHnt9ddnu8mLl4sWvxYubixcDFi6WLF4uWfEzbbsXB4/jeLf1y7t3ljQ0mji2Y0/GGfsnH0iUbc6kYNj1jB5+9SdExbHWrhWKAjoGZcDYkH7Fner7Vc+9k6tzRemZXvv0UOxSAa2gdsU7wGNgFzo6sJ6XnVz3XTratJ3WyYspOgT3gqbAPXAw3gKfBLeDZcDt4DhwGzzXWaapT+WNUvrlO01yVP0/lH6vy58ON4HFwIFwAd4THw53gCXBneKKx/lyz9KCfFL3O1qjVtf4UTIO5MAuOgdvCsXAIHAcpj2cUPUvCPWT32tAbjs3qoNgsuBbsB9eDm8AN4KZwC7gZHAg3hzvCreBouDUcB7PhBLgNDNdjifSuL71mPerVH+bCVHgsXAfOh93hArgePB6G279R5Y1waP+jVI+jVY9jVI961WOu6nE8HAQXwiHwRNXnJCg9eo6j7Rz0nK71/86CA+A5cCQ8V+1xntrjfHgAvABWwCXQBy+E4eOyRHpucDgunaSnC+wNu8FM2B3mwzR4IEyH82APeDrsCZfAXvAKuD68FvaO1E/PNnCmQ/180nsI7Alr4CYwAPNgLZwCZ8AyOBNWwcNgAB4OdT7qGYPricP5+LXOl29gb/gzXAx/gUvgr/Ay6KG868Bq8Ca4OlTMoZ4ZuE+rfDPmsKP6wxqwG1wT9oGphn05ufHte0X2vSr73pF978q+92TfB/A6+BG8CX4MZR/j+/j2farr2mewG/xc14svjPxTlX9rh/xNyv8c3Bw+D7PgCzBy/in/XIfzb7nyPwj7wodhHnwEHgUfg3Pg4+Z6eho/bajyzOv7eLX3BNgX7g7D+eqUr7dDvh2UbwTsBUca+ZYoX3+HfKOULxdmwDHGcW1SvjcdjutE9e+9dF4dCO+AhfBBOBU+AYvhC9ALX4WlRr9rGRf/uE6TXeXqdxXqdwfBvh09bca4TpmR6pmFLEFuQ55DhrNfxjHO8a/Lj4mOgX3J2kbMOFgfN9t6JBwPe/lsp5hYZHb8uNhv+FtXYmOHIguHdozEyKZ+lOIp57eZyCy2F8J4MbMNc1bGzb47Jzp2NrWeOiI5iBcZmk8e2IjY12JpqY+Ope01Nzaeto7fBrN9OXwcMWNr37X2nxcbY5s+D51wMLTH2hbMi423rZ8XG3P7OL8VwHfhz8hM/p1+bCgGdzA043Dr2Q7H4i7l38uRcEzup/w7Zf7K2NzM+Svjc8vnJxaju5T9ls2HbH8Kw7G6KcfFxusOt36Dk2EWv/lhM9uLYd8c9rPF7y47LhzDiz4YL3bXupFnIDnIZMQew1vHby38dhsMx/E+bv17Eu23IPl43qzjW4/pzefvxPXGjek99/hwXC828e8m5FOk68LQ+jaZ0Cm2N29hcvG9gYXo59+L4XC2l8HJsBmuQMIxv31PoJ1gTpy433p+98Nz4c+T2Re+i/Tal+N8YnQscF+2b4Oj4WD+Xg5fYnshnMJ2AzTjg5vZDscIT52QQpww5Z5E3bgmpR7KenNIHuJD6pGlyHLkXSR1JjHwyDikHFmENCAvISuQXoeleoYik5GZyOI=
*/