
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