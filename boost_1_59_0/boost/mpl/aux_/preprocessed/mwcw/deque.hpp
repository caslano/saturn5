
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/deque.hpp" header
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
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
*/