
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct set_chooser;

}

namespace aux {

template<>
struct set_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef set0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_set_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_set_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct set_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_set_arg<T1>::value + is_set_arg<T2>::value 
        + is_set_arg<T3>::value + is_set_arg<T4>::value 
        + is_set_arg<T5>::value + is_set_arg<T6>::value 
        + is_set_arg<T7>::value + is_set_arg<T8>::value 
        + is_set_arg<T9>::value + is_set_arg<T10>::value 
        + is_set_arg<T11>::value + is_set_arg<T12>::value 
        + is_set_arg<T13>::value + is_set_arg<T14>::value 
        + is_set_arg<T15>::value + is_set_arg<T16>::value 
        + is_set_arg<T17>::value + is_set_arg<T18>::value 
        + is_set_arg<T19>::value + is_set_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct set_impl
{
    typedef aux::set_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::set_chooser< arg_num_::value >
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
struct set
    : aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* set.hpp
gM9iEK7H0fgchuMGnIgb0bRf4NO4GdfiFnwWt6Jp/8D9+AKexB2yv642yLUNbpF4q2C65Y9giXeOxDtX4n0CG+E89MD52AsXYD9chENxMQZjOobiEkzDpTgVl+FyfBLX43LciCtQ6lOuY7i+0anPCNlforEmxmBDHIvuOA59MA67YTwGYQImYSKmYjJOxxR8EtNwNU7EQzgZj+EUPIlT8SxOw/M43XocybUGJukcR49LvHMl3ick3vnYDBdgZ1yEAZiOsbgU43AZbi9dsP79A7aUNz07juvLc1CSbl//fiSeLfvj6jf1+/2n3+NZsgf6kZRnyqH9C/5cOae/+dlyEGmSPGNeh3sZwDuTtIvPOwfkf+Z8TZ47lxnI82NshOrnz30G2n8GvVPzHDobb5McuXjKIU/tOAKGjNKm59O+8ow6GFNJ6nEFDryZ/5n1TuZnkZRn17fQ3jgDjVj/XOW/5Vn2dZJjoPmZti//dgI9Au8+/kCfQNaJoTg30PK8GwPznnnvDaTMJMuz7+uBKM+/U8kn503zc/DAIXd/Fu48NO95eA+0PBPPwL2kCyT183HHYUUbvyBd+Q4pi5RDsjeegWsQ+WA6ZVCepweRZslz9aOaZ+sXgvKer98JYl8fnn+8g9bMu4zBOI20Up6778UskvL8fV0m7TBIl0m3SM5vOxhakwaQUkkrSXtJWW+XPJsvmUqmkqlkKkOK+nOf/yeOSS2ed/95qdr3p8qz94uk0qQLJCcuQHLDbNtVk7m0gS/4GHQ67aq1bd6ln7+Msyf3lWW8vPxtxnkO+EY4cSnfMWrav8t9nxdIleVv/YlGAwvqtn8nt3s/f7mf9uHMoywyDp85u3u2gbc8Q5Dy25TPKO37P5ft9BmpEuXL1i1f4pj73U5HCtj+XR27i2bb1dFsuyMR5m03SbZdPymb5aHjVSnbRyQHZdtF2paNlwCahkNMjkxJiYzgP3mJVmxCWGpkSkj3AK/4+yqv3n75bENiVW3LVNLkkPBY1N03P4iU99NoypdbRnOMSflcowpRvqT7257FUb7voyzlK9h7ygp7n7+w7ykrrvvz+s+J7D9P0X9+ZP85kf7ziMI/DyquPhaFfa5k7/nadtPzlLT0A8cf2nf5zOZWNepeb/PSIfvPfbh/wM1o+W3Bi9I3pbLse8o0ScYBnIK1cSp64jRsizOwC87EYTiL/43ExzEa52AazsVVmI57cBlewAy8gQsM8tsAL0gcTkg+pmmV3MdYjU3xGTTiGmytuY85GJ+VeNbjFHwOZ+EGfAo34hp8HjfhZtyCW9BSL9kSz+c69TJC6iVY6mUUeuJoqZdQqZcwiSMcR2MEjsVInIRRuA4T8Aim4GeYao1DzrtwVSeOThKHn8TxGHphV/TBbtgNA3AU9sAw7IXx2BunYh9ci/3xIA7CjzBQFYdrlP39pLbEUUfiqIueWF/qo4HUR0Opj0Y4Et0wGhtjGrrjKvTCPdgWL6B3yTiTf8oYk//p75gpzvEltf0azrzjYMglOZ92MHiTkk6X3D8pmUqm/4XpL7j+j0+LM90AuO/r/zaq638Pyzjbct3sRZpu5O+k7pZrE9PIA+aR/0MiuKYoePv/7fwgs6hNG+NYkvq69rLk/5Hkf5E0Q7mu1c0/Kjky8t7jC+jlf1uVv9Ke1qg84yR14fOgHrZtoRsaWS41JV9b7iC5x5ApsZ4gzeS7uT1MsaoDTYiceO960rles8awXfr9kz8xyjvzS+XfVt94kn9PS/4T+z0WEBITNiFSicTy5gD2m3u37dWJRdpgynaSdtZelckbW/B/7pTdr5dN3uRlLvcGWbm9NrxThlrb8OrXg+q6NRnV77tPGRM=
*/