
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct list;

template<
     
    >
struct list<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list0<  >
{
    typedef list0<  >::type type;
};

template<
      typename T0
    >
struct list<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list1<T0>
{
    typedef typename list1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct list<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list2< T0,T1 >
{
    typedef typename list2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct list<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list3< T0,T1,T2 >
{
    typedef typename list3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct list<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list4< T0,T1,T2,T3 >
{
    typedef typename list4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct list<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list5< T0,T1,T2,T3,T4 >
{
    typedef typename list5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct list<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename list6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename list7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename list8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : list9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename list9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : list10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename list10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : list11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename list11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : list12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename list12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : list13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename list13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : list14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename list14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : list15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename list15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : list16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename list16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : list17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename list17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : list18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename list18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct list<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : list19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename list19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct list
    : list20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename list20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* list.hpp
f4h86WT5/EOt9YOBevY+uPT6+fVorejtJr3dpdfbWpcXqGcfK5DenkHr/t9gfH7j83fiukT/FX+/js/R67RPaE3G3zdixIgRI11IOsD/L8mfPixi/v+GGI//7zHZ4v+fYJmfH+fg/yda/f/pbc8TDpgX6pDvb1odPd//e4d8f+3qyPj+8xzy/Q2r/z++v/HxO9fHf8zr45ftv+3PC0++ffB1O6btNv/ba2dF38e3j/m07fsnWnzqP7qFnu/3fk/Afl690PP9tdKL9+qFnu9vkB420Ws7318Y4trEPVfGGN+/Hb5/7Tkxxv/vwv7/+nNiohYDSOQzk0qbSMtdaWIARowYMWKka0gH1P+X5I+IzBqAvvr/Rc0xAJltiQNMttQBDHSIA9SstsQBRoS+Vp/PL+8tv3mj1pJbrbXkRr8euJbctA5eS+577FXxRk7Kv27cEo4tT+KYx7BlH8EBAwLXl9vYyvpyi3W+x9N2po1X7GP9a5bYRzv2JwuMfWjvsIDxBl73WK3hl65xpPnWYmMcioeEPQabPgPOvV59TlGfJ/jW4HrNEiNpx7mHGiNxGJ/iJs7xAns/Ofx4gb0f7hR/Cd//t4/LOMdH7OM1Tv58+Dl++7iPcxzKPu4QfjzIPm7lHPexj+M4x2Xs42tO8azw40GN3jhO47YXXDFy1lfJ2eetO/+UksJRvriJvnP1XVwVVItwpeIR1YqbXOXfa0rfqfqurQraa2q41poaCfeGh8MD4Cg4BB4JU2AaTIdjYAZMh5kwAxbC8bAMToIXwhPgjTATLoaTYT2cAp+BJ8H1cCr8AGbDH+Ap8Dd4uvZYOwPuBHPhQJgHB8N8eAScAU+EM+FJsAieDc+CZbAYVsESWA3L4L3QDR+EFfAZOAeuhHPhaqg1llgLS9/R8Hhd9+3gKF33wdqrK0lxpyEwGR5sWaNrPOSY7CGyl25jby/ZS5C9vWES7Ce7+8A0mGixlyt7U2zsDZC9gbK3n8a1P0yFB8AT4CBYrPjVvJUxbcawohG/SlIMazTMPSG8tZS2lhhWe+NXuXNjtjiG5Ylf7WRiWJ1Sw3IDn6l62graRtr3JoZlxMh/Rjok/z/C4/pv2dx/X/5/mt/3x2uU358VQv6/aZXV7287rx1K/r9hVcfn/92ropv/r1ll8v/h5v8jNd/f1AU0xwX2OMlz/IqZn806N7XykdMPO/vrMYV33Br9uoA28v/6DlFNfTjz/aXXjxYbznx/6cXTYsOZ7y+9/rTYMOf7d19lav//S76Tyf93nu+UwGcphTaONm2V8ZuMGDFixEjXkQ7x/1Mi5/8nyv9Psfj/U0Pw/3Ot/n8Ie1GF4v8nd4L/37gyuv6/y/j/xv/vZP9/rNf/f+L62nXLF07a5rR3B//9+p+rX+p8/z+3nf5/cjv9/8aV7fP/XVvg/1cY/7/L+P/G9+8Y3z9lXkxU/P9qPktLaMtoa43/b8SIESNGupB0iP8/bMv9f4+fn727y+szxkbQZ7T3DcP3AcP19f5vPl2012Rf1C20Ocx2e2Mupa2naR/MYL/D72/U0gL3u2x9r0v8Bq+/EEsL8g20n6XzXpbVtCW0pbRW9qxsc7/KBJrvN3k2bSFNv7mDfmvb7Tlpt99k6HtM+vaXNGLEiBEjRowYMWLESNeQqM//p+W4zy6ojMD+f54YwKmWPf6qlCNPg33hULjSk+t/xZ/rz5yQPiV1WOaEsczPDGte/m6uHr0uedWbRysoLy8rd1ly3f3pzJ3aMsf+OEaTVzyzrCi/ZY79iRzznLYv/13HsXf6uFxchRzm2GNrZK80r33SdUnefLj/vJLkMv2peee/0V7jPU2vtpwXZzTMe3IhzD8=
*/