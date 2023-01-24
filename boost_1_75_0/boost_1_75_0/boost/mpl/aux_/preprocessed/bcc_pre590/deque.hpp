
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "deque.hpp" header
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
struct deque;

template<
     
    >
struct deque<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector0<  >
{
    typedef vector0<  >::type type;
};

template<
      typename T0
    >
struct deque<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector1<T0>
{
    typedef typename vector1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct deque<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector2< T0,T1 >
{
    typedef typename vector2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct deque<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector3< T0,T1,T2 >
{
    typedef typename vector3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct deque<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector4< T0,T1,T2,T3 >
{
    typedef typename vector4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct deque<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector5< T0,T1,T2,T3,T4 >
{
    typedef typename vector5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct deque<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename vector6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename vector7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename vector8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : vector11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename vector11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : vector12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename vector12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : vector13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename vector13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : vector14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename vector14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : vector15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename vector15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : vector16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename vector16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : vector17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename vector17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : vector18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename vector18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct deque<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : vector19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename vector19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct deque
    : vector20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename vector20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* deque.hpp
dJHNk1WInFEZBvW+7Nf4XkfcqMR1P1sXCe0enHX0uq9caCHQUz+Duj5Um3GmWUHkyVc2I3oE4kS5fKOGsZQZFY+2h0Tc73JKob6Ejf30T4TAKv8Sb30Tf4+/WdhkD17pMTa/T6sSV4Fl1oK7Tv0auD14ux3glglg3KtO7pfz83EXEejROUB6Pc00tMzyaDtcQMOwBHyq5zN4DUU5k9zTUlpS+xUQWosonR0Za+2LCa4uvOs76wFjOzFXk9i7PjeTLKcWGptPCgIc4aehCeF1YTPhEwvTOjdcv0FrpfnTzm6oQhPj4RObiJXL3kg4iG2XeEhoqDZy/W2+RI3cbBMYxZVRSnIjzEZyY2ooqx1tLnp1zMaRu5XMlWNXbAgeyRZZq5zD6Ujqj8c8EHFJv4a3jkcVqTqEM8SIZxiZG2kYG7j+cTnuSBJKhxz5J93XAkv57GWUyIrFmz9H/N/64z29fcJDewuPjHiLhsc57k8KeZUpFn3FOTQYCYkkaNoYgXx6NIs17Qn2IcRL74aQLgRmyCiPcRFACAeYk9pSGowpVnBtpV2Bxm7vqFakw4nV4qmzsmZDx338RPDmtQbLOE3JxmUuPoqGjg9FSkZlvPjoqWGdwq3cpPhrK4tH40npl3U+88uO1hhNcMUVNpeW4xxb10bW6dpq0YiYxB+VJZJik76ZysGIPx5MQE2yRmv2IW+JU3tH4DdA/ptXbgGS
*/