
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
pzLkFJKA9anOY1pUJV9Tm2rV9G+zdcRHSsPl8uLK4NBoxcTGshMDRnNBwE7SbGh4aEz9pntrxMwN8fvkbRHDaZETjcli6bzut52svYsX4vXO7O0ha1XdnKZ3pJh510wi3Hf6nLd1BXtXwPTYwbt9hi3zTmjS6ASuf0/gaZhSa+O383t95p7Fp4R6q841Lcc+0j05VTY+lzrl6ebVSRsS8v/Unj4J0Y3rht7uNC0ud3tLB7ydddqNbI3Lrw8FPE/k14d9DyKLsd0UU+3roxFvr6rmq4h9TLNqXuvrNhv2efhxj3WytfiN8gmtm01kiwMKTZjEPqkYf/bPXT39VMRkH5LTFEM1J/3TWq83Muv/jNYnpzsNvBtOj3XzJjuO8umzMTNBTkzYcvyc5iZNZq5ou68hexR8XnNOc59JPsXnDM0asr/ZF0K9QjMTWjbML3o8N41gTaOWMTszZJ2u+Y6Ns6I10wc1YYFOjnw6S/vML3/bz/iy1vPV5pmRzVC3CPE6O+B4pvAa0ySrzNj1WV8NeXeGwvyar/MLFvf7eoLZfcW+ETD9G+scn+E5wvE8N2S5vy/WeT53z5nzY93Oe+Rx45B3p0n/VqDPtDivL4h1Lw3fDnk3X2XvdWHATCXgtZ+xXvQh6WgHG+53Q8+qxkQH7Hs+o4yx110UsG6TriR2ccAwaYvYJQE7MWu7ev59j5kVt7Wqu9+lEZP95i4LWHNK1rX/QDHZlLzl+uA/1Nw81/qqucuby0PW7UzMBfuRZoVOD0UujyuIjZltN+2kPtZ/7Okynnqlp8t46k88Xb4Z/ZR0Pky9wqfku/RelWBU+RDm1YYX+zL1jfSP9i+ROFzj6RKHaz1dxnSvgy7BsH49dAmG9RugSzAYA2bdHLagYoRrbgwZ3i03ia6D47FfYqUlfMxHUdx8n19EOr386JqbPXZCu4Ex1Vti3c2n+CUY1knKukqt63WVWufpNDz2C52PQaAPUxRp2uc4Yi7i1L5vi7lEEvl7u/WMF/vBu+uJ3WFZPTOLkUy/brxaW4343ilsNf0shX6X01v4yIz9iqHzganL7b6zFCtbNnfDU/xIqfE6Wh4fhk6xg/de0fhMFKTnPk8fXKjXU9/vs3L/CC+mXoQzxh8IeWVk2Txasoz1lCHnwCl9v/NYaWBk0Yheak3hPxR45PYc/sMBx+2pL/l7zXpMmLH5+Ih47RkgpD8a6XOpH/BYrFdGRoeWV8zNuYCw1lL7XN5gfNlnkjLwxz0+GuX9nyJOC9kLTPyJkOP+Ns1Pak4VHusuI73Sv2wFs6diZgY3mf0lZmYwAXsJa6b6yM+EOtVLjv+zIXN1E2clx1znEXn+lvIE5fD3lIdvRGX9j5DHdZXu9c+ET6LD9/pXwmOjs7fh/454ut669Zmhn+suseeSbC61jQ02j1hch5E/z4u8iDDS/fyIx3mzYeyRnIFno8gzGpXnxrFH13vybBJ7oufSpqGH6iund7OYoQ0w3zzmaAfMt4g52gI/m7cE5zcLt4+tPI0aAcVza093DYDu84KQrQVEfm4TcC8zUbbbRh5kFPh2Effvsb3Hg4aBMF4YeoLn2A4hlyhQXX2Rz9MNAuW6o+dFYwB7cczm2nTslGAqmvQc2Hm9HppxRb5dAl/csDg+uwY+ne+7BUyigjFmn4+myvaloUcaCvHdI4444P3wMo9TJaZ4vzzQ0TiI7REwNAxirwgYGgXFZc80M4V9BMVlL3DpjXE+vDLS3WF0WXWa8/lVsce0L77+1UmGy5GPr4k8rh1SGK+NuG6LXCdeF3mi9khhvT7pQ7nA84akx7/f3pEnaps8Pp3yBc/cfVIeiRK9t2bFnnQ7RZ72RX4=
*/