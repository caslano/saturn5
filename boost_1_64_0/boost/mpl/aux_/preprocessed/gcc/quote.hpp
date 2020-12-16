
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
{
    typedef typename T::type type;
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
FYjM+s8+/+fmzNSe/E//uX85Vjrmk+bKc/8nMk/pY+RJbT5pkTz32/dSY9L5sBHDJhr3D7OP9fj2DuAEmtkFzrn3ngXnZWctdO6l9wKJ8v/Umfn6PfcKsgqLcq36eWp8sF1Xif2zkL3YnzbfZN68y3yv51rpbFfn0StzwJibppuTtkVsSpHxtHHI09hU7bSJycI1bFlpbssKbKFsB9p0haHFaJdx/nAxYZ9BH59TrQutOn/FNpSz/MRfE5DnCGtZILbZ513FjxkxXlfamo1N6uCvriG29Q+GfRZVfzWXgrhI3j1dAF/ApiqnTcyLreGvcB9sCRNbXmMyAylxyzEbrdAerlpsytfiSf2T9QgGm7XPx/ncTXytpXtM/u+YZv1bmVdWX+fx+99l/XffZR22vct6smpCaJdVa/Z/Oa7w9W8OhJ6qv3dZ5u+m3L/LknO75feB+CbntYfKO6swGArbwgjYDsbA9vAiGAEHwvPgeNgBFsNI+BSMggdhDDwEO8KPYSco5wZLO6+1/8ZzgyeKHZNgJJwCY+FUOABOg+kwBc5S5kPEIdWSborJeXedZf5aV9gTdoOjYA84Dv7BNf9F2lXNBuP5w6PFvjGwAxwLJ8DxEr8MqZL4tI3Et88/3yDxe0n8fhK/P+wOB8DRcKByzmseHASXwUvhajgY3g6HwJdgHPwIxsNqeBlsit6hMAIOg9FwBLwAjoTP+t8B+t8B/k7fAfrf//2fvf8rY54GUoUE3MVeeHf53wf6r/q5zsDzf1ZBwek//2t701doz8cJ2hxPHq0KrQWp2oIYFh524H8v8r/wYcr/CrLSC7WnJS7t3cFK5cyAkfLuIAFpiMQjg1vTZ7HantuGTZyYmjs3PTPVnhJmeLG2UZ6dOLPY92cY82ct98825s8S7p9JzPv0vve5fR0n9vUZxvxZyP0zW/NO2vejF58KuXP2nRPGjPh76c9/umO1u2cw98+i9jUOUv5SL7Ib6Nc4rJK5xGthB3g97A7XwUHwRhgPS2EpAVP2MP9uT6BX52566jfq+4zG/mLz8ab9RPM+oqFfWD99QukPKn1BtR+o6wPS91P7feZ9vv2Irq9n6OcZ+3jG/p2ub0efznN/ztWXq70fN4jPUxFH320DEqH01cYkK320OvTPjH0zd/0yQ39M+mKGfpixD+ZD/6u2/la5s491+v0rT32rCETtSxn7Ufo+lNZ/2rjH31/yX/7Lf/kv/+W//Jf/OoPP/xlz82dpLwBO6/lfe4a/Ttn3r38D1x5vDZFLkZe1/YJmytir/RwzbYMba2E6m4JkWBk89fwcHyJjsHcyUKsZHiDfNYfBxJSEdPuSVIktJUgLpBjZhy1RGaot9ncK7FvDcJM349KNgnOJT9JZ+Zlil9gwC4/wp3Nvvjy+k3SdY8HTsYyhYJ2dR2V8/2wZrz4LvoKdFW7sLPRqrkSj4GWZnu2sVuwsdNopY9TKuopyLJ1rzc4qkIBhMo8iMVIbj8+1fytn/x1FaRV56svnUTYbXGPdW7X8kzD5189xaCjGS1ktQV7FB0FZRh/Mybraq3K6Mstz/h31x5JeiP3EU8oOPc45JBOw0qJ9UaPsOst+c/dL2e2A+7Wy09lt3/gxI6OoID3DbnuUB9snzrbbXlDgfd137HfYBf0ZVpn/Iuct5uYUOuthlXP+i1XWx+jLu1rm0DgNFn3HJVyerVWwf3dUvsOGQke4Y85wuai114myhvb3afv5Pm0WeVN83Z6FCJyoqPmV7wYE3yH/f518aJ/frvG58WzHZ31ZRMhedjdIHVqDHCBM1WxDWdjqq7f3+6RsV1lon8dlO+qV92Uje7zxnf5eC3WVl+7eo2yUe08=
*/