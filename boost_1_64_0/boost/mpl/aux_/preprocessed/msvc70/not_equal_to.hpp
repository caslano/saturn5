
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct not_equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct not_equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          not_equal_to_impl<
              typename not_equal_to_tag<N1>::type
            , typename not_equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
7AOL5Xm2GM6HZfBCWA4vgg54CbxI2ttqaW+Xw9vhL6R9WAGfhZfAl+BK+Fd4KfwSroJfw8ulHbgC9odXwoFwNZR902X8imelpEfdN32OPE/Ohz3hBTAR5srzfgEcBvPgKLgQzoIFMA8WwnxYBJfARfBaWAJvgovhergEboSl8CFYBp+HdrgTXgjfhBVwL6yEH8Eq+B28CHbA9othR7hCnpdbbDI2BZvl/sfBzZK+MTbyB46D8XAC7A1Ph6fCiXAqnATPhpNhKcyQdEyB18Mz5Lk9Dd4Fp8NH4Vnwj3AG3AZnwmfhz+ELcDZ8HWbDv8Fz4AfwXJf92CdjS3Cg2B8Jhyq+oyPgahgDr4ID4DXqd2pr1+97mnynXie/vx4mwBr5XTqSIr87z+T970YpF2vhyfAmeBq8Gc6Gt0CpfzKuQxpN6t+vJJ6Vsh/6r+GJ8FKYBi+DWXCVuk92G8++1tQn/fdfJ3WfbAkX6ydcVoDx2QMMVxNguLoAwqUg9OFb9jMMl/uXCvvAEUr8tijZF72F7+5iJF3COSRcezhfwt0q8d8GneMwUl82SD25HabCO6Se1MI58E5YDO+CFfBuRV+j6Ftkou9kaT9TYDwcDvvBETAVpsE0OBKOhaPgJDgaToVjYD4cCz0+1dtKPlj1K0g+10q4vib5PFjyYQhMgkPVfeCt4pf+iAR+WHxelG0lsg6pQ3Yg7v209vL/pvOi/if31WqbE2W6t1ZiTlTA+2ul5EQFtcdWVk7U/80+W/acKL97bdUQpg7ZiRxAoudE2YYimUgxsgbZhGxHGpGjSMLcKFsakoWUIquRjUg9shdpRhLmRdnGIDlINbIW2YLsQY4iifOjbOlIKbIK2YTsQBqRtudH2ZKQ8BE+wkf4CB/hI3yEj/ARPsJH+Pixjp9m/b9zbULlj7X+/146wLOd6/Od0eZqcz97y3r+AyO81x3L7YW5LJhz7wu4id/leH7n3DSwkk398vKXePcDmO/8uzbz2Plz53r+dV1snvUcjBM4j9NgRzgWPk28C/7mWQ8zc+KMKdr8bL/zGrso6zk0i/ivbk0HBsg17xpaWbvpmSf3zCDXnP0uypz9vNKSvEoJ0yxhysvszrWj0xtdYw9PDtLPA2X+g8xfcqXrQaT+JMZZGnXpksmg/n1YS9p06eimrDNQ5/mqdjCWw6H3oV2PrQ3v6+0oKM9lcrn/uaMGO5R5j78j3iJljXJEJHlXscgzf7ROmc88wX3/xb5tYt9TYl/SB2b2Ob0JM0/f/1qXUO1sws7HxE7d2h1Z07/GaRfjG31d50/LOXHq1inVy818TNL1CPIsYWI+1KeLBcR+1ykFWq59yrCUV2Xttaw1ynOWX5tpGVfLTqKsuy+WNBQgrJtgEFKfBhZQEEWgaydccce0kfEAqfdXw+exq8YnbubwE39BYXUA97yb5NPjxKMtB3K2SHI9Go7p5twTQi5zXe7/k+JrW/6grNcx5mOJ5H2TnIt7bU9dzCcub2uoz8/tkuYXJD+fRV7oT5o/1qe5onBp+bJCWct0nMrFAaUcaOV4yCdKO6asncmKMq4/ekm7T4THZqmWRWWBrH932/ug5JFaJ19w1zlsqftEqVPK2pMmsWW05N8ImUNdL7aoTUQuNzrY+dNlw3PFHjlPzfXc+z9pNg+XvHSfp+rXpqwURVPFvknIQ1qd32+0jyzzW18s80varAJlfvfLkn9qftnaGdeKvEI4O/a41op4m9fC0kJHMP7q7/VZI/Kgif5VJvrf0MqOif5ysiaYtTL3+qyPalDWR6nrZRJlnXwPsaE7spuwdRY2OE8zzp6YmRm8Le68eFN9vkjZ5vmiy5s17Y3rtt7Wnss=
*/