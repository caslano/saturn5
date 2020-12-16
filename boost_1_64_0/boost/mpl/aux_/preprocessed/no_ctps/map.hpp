
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct map_chooser;

}

namespace aux {

template<>
struct map_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef map0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_map_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_map_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct map_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_map_arg<T1>::value + is_map_arg<T2>::value 
        + is_map_arg<T3>::value + is_map_arg<T4>::value 
        + is_map_arg<T5>::value + is_map_arg<T6>::value 
        + is_map_arg<T7>::value + is_map_arg<T8>::value 
        + is_map_arg<T9>::value + is_map_arg<T10>::value 
        + is_map_arg<T11>::value + is_map_arg<T12>::value 
        + is_map_arg<T13>::value + is_map_arg<T14>::value 
        + is_map_arg<T15>::value + is_map_arg<T16>::value 
        + is_map_arg<T17>::value + is_map_arg<T18>::value 
        + is_map_arg<T19>::value + is_map_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct map_impl
{
    typedef aux::map_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::map_chooser< arg_num_::value >
        ::template result_< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

} // namespace aux

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct map
    : aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* map.hpp
10pAey35PqmOyr6x/huNbR5HdHFYeDRN0OHjx4ZvHdvmmvuM9jHCso3l/NNS/3L+qXkMUR83G8qgr21lv2tNukL+3pc01tlYqHs7j1Gvk/r7YmP5vOcx15X32s2/YOcx5Ks+j5F9Ku95jG8Fm/MYqYfsi/bKUfDzGNs66Ct5X/UyvTlBjjWj0Y0CBO+wmzff2dL41D92dI7cv+BWZtlux9rhvfzOsXdur26XgzmLV53DMy/HKsvfm6qPK8z7yfUMmVf9LrA9T+qw0/p7cKXN/DGb+YW7rOevyXwvmW+923p+tmpe3Y5jK+Y97/mF+vO1234Kdt5jr+20rSTXqyTfYFIhX/zVbr5JWm3HkXvtCnrMYtuq2wrz2m1FWZ8esj5HZH3qyvrUJt1k2brLd12f5ATL6cD9Ww/1cTK7imkB38l1waNYh3r2/s5euZLUXxEO7ZdTsx37rZFC4tEvlrj2WpTDlKX2dcLTGueUX/B3rphEhQ2+852hLDdG4zf3YPu/qdW/14330R1j+zWsIvGpJ1gf1e91Y91KvSr70ovHTX8Pkn3L93vrfe1b5tX7pusP1vOJzKvf/6bN/CTyV79/I/Pqv5+2mffKtp7vwbyUz+raVGw1nXG6IOcJ5/C2sq9rtdEkx65NlcinbbjnOnbMvpf9kHm716au5vPbVNnmp9ne9amTzUp818+U09ynIJ8dbDpB1utU2/7AZett48fn1PO7mFe3jUuqv8s9EYzBVPB7B7TvESh4rH5BY++179Gwf2+C9r0ABY/J175nxN69IQUfG0v7nhF794YU/N4KO/eMsJcpr79T9nbtfrfbnxnn8fKhbZ7eMXbvxZB7EKRPW/q6b7hYxSrSZiVWEd2xh8R0HnOVfmnpr+Zzxv3pkPRhRxQyxWKOQE+MwSo4GmtjLAZgHPbDeIzBBByPBnwRE3EZJuE6TMbNOAZ34FN4EFPxc0zDYzgOT+N4vIITUIlZnohlMB29cRL64GRsh1OwF07FEHwGQ3E2huMLmIoZOB7n4Dx8ERfiS/gKzsdt+DLuxgV4EhfiWczEorTPJVgCX8FGuBT9cAW2wdexL67EgfgGxuObmIRrMBXX4kv4Fi7CdUr++DbuxneV/HGDkj9uVPJnW23CErgV6+M2bITbsTvuwCDcg8PwA4zHvfg07lPyxf2YiR/hcjyAr+EnuBEP4k48hPvwU/wEv8Cz+CVewCNYtDDHWyyB32J1/A6b4XFsjd9je/wBu+EJDMNsjMKTmICn8Fn8EZ/H0zgLz+A7eBbfwxw8iufxOF7As/gzKsHKueiGv2AN/BXr4BXsiFexK17DaLyOo/EWPou/K/njbXwD/8C16OJKPWAhPIyueAkL46/ohh7sX0WwLBbFxuiOvvgQBmAxDMXiOBhL4pNYCpOwDD6NnpiO5XEmVsAF6IWLsSIq+7dHIenfl35/Zf9ur6NcheQ+1sKm/bsBemIjrII+6IO+OASbYgL6Yxo2x+exBR7F1ngG2+AVfAxvYjssquSp5IMBWB47YU0MRF/sjO2xCwZhV3wCu2EkdseR2BefxBCcjf1wLvbHjTgA38eBuAtDcQ8Owk9wMH6JQzAXh+I1fAIrUCfDsAqGYU0cjrUxHBtiFAagHrtiNPbEGOyPo3AMjsaxGIuZGIfLMQFfQwOuxSdxEybi15iExzAZb2IK/o5P4R+YirQh3VisjOOwJo7H2jgJG+BUbI7PYEd8Fjvjc0i7oN1Jv7/EAyjtYpjqeZpVXU3toiZ6Ym2sgnXRBx/GAKyHPbA+9sNHMQIbogEbYRr64ET0xVnYBOeiHy7CZrgSm+MmbIF7sSV+ia3wFLbGHGyDlzAQb2Fn9FLaD1Y=
*/