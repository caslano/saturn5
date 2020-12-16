
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set.hpp" header
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
struct set;

template<
     
    >
struct set<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set0<  >
{
    typedef set0<  >::type type;
};

template<
      typename T0
    >
struct set<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set1<T0>
{
    typedef typename set1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct set<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set2< T0,T1 >
{
    typedef typename set2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct set<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set3< T0,T1,T2 >
{
    typedef typename set3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set4< T0,T1,T2,T3 >
{
    typedef typename set4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set5< T0,T1,T2,T3,T4 >
{
    typedef typename set5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename set6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename set7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename set8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : set10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename set10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : set11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename set11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : set12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename set12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : set13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename set13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : set14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename set14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : set15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename set15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : set16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename set16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : set17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename set17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : set18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename set18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct set<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : set19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename set19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct set
    : set20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename set20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* set.hpp
l/PzeZ0PL2A8FmNvfBkH4auYhK/jcNyBjnF5crXddjpe1nF5RldhuzgeI3AyxuEU7ILn4iCcjub1BSdhChZiKl6FM/E2nIVPYjo+hRm4BefgazgX38L5uA+z8QTmYGXiy8U6eCE2wDxshPnYEguwNS7Q54C2lRz3UtiXriNGOcfqOnJ7ZV6Pd2FzvAc74L3YD+/HYfggTsKHMBcfxoX4KK7Bx/BhLMJXcTO+iU/jAdyC3+Cz+AM+j0acL2ACFmMSvoxZ+AoW4qu4Gl/DG/EN3Ilv4d9wFx7DEvwa38Gq5HEPNsS92BT3Yxs8gGfhQTwb38dzsVTn75Ew3UvB91Ufmui3OWOZrfKaq/LKUnllq7xyVV55Kq98zMUClddCvAsX4VZcgi/hxXgYL8EvcDnWYv+XYj1ciYPxChyFV+IcvArn4tW4Cq/FdbgGb8cb8Clci2/gjViC65VfrlG6R8I1TfXDOP8GqH5k6Lyag1GYic1wLrbBLOyE2dgXc3EIXogpmIcZWIgX4QJciQvxalyMd+ASvAeX4l/wYnwWl+NBvBS/xRV4Eq/Etkb+sROuwmF4DY7BazEDr8MsXIu34Dr8C96IT+MGfAFvwffxVvwEb8MyvBN/xo1Yk7K5C+vh3dgaN2FbvFfXE+qy7rVQZ1R/WvPvHirP1irPdhiBHTEGO2NL7IKDMB6TsBuOw+44HXviLOyNmdhH5doX/83eucBXOYYB/KiQhFFbt6mVrpO1atWq1da2RjW1NBnKrqeadjm2syyNQjJEQ+5hCCFMQmkYwhBCCGF+QghDyN3/nD3n7D3f+b6zc9Yql+/9/Z7+O6f3e5/nvXy387zv8y6Co+AFcDS8FsbAFXCMtG8sfBjGwXUwEb4Dx4v9SdLOE2A3bJ4Iw2AyHAknw1g4BZ4GU+AMOA1eAFPhYjgd3gRPgbfDU+E9cIa0/0z4FDwDvgXT4VaYKXbstoivBvaSdgx1PsfKD65y/1gCe8KLYTgsh4PhJXAUvAwmwMvhifAKOB0ugzNhBUyHV8I58CpYCG+El8Kb4JXwZngzvAXeAyvhGngb3ADvgM/DlfADeCf8DN4Fv4R3wz/gKngA9bkHBsN7YRd4H+wOV0Pqz31ZfDri60kT//hGqX+U1H8EDIbR8Bg4Eh4LR8ERcDQcA2NgIhwDp8Gx8FQYCzNgHMyC42AujIfnwQR4EUyEK+F4eC9Mgs/AE6TeE+EmOAluh8lwB5wMv4ZTpF6MOfHjUD+pV0e42vX+I/fbI2AIPBKGwqNgT9gBJsFgeDoMgdmwE8yDnaENdoGlsCtcBLvBS+DR8DLYAz4Ee8IXYC/4GjwGboW94XuwL9wG+8GG91/xy0C+93r/DRf7B8NgOAR2hVGwLxwOI+AIOBSOhKfCUbAQjoYLYQwsh2PgpXAsXApj4a0wDq6C8fBemACrYSJ8Do6Hr8AkqdfxUq8ToLw3ij/H4efxfm/sJe8lx8D2sDcMg33gANgXjoX9YDwcACfDcJgNB8Kz4HFwEYyA5TASLoeD3c+J4uNxjlnv58TOYkcXGAK7wggYCofA7jAa9nA/J4oPR/7WPieeJ/2zEPaC58NYeAEcDy+EE+FFMBkuge64VFLukd7xsDhPGvPVS75gn/nETyHlcR33yNdLjdcl+YKbyJfiZz6bD73HqHG9jMqTfJ0P8j8OF3G3WiTWlr2+lVG8rX9NrC1fa7/XLmttqV3Wusl4W5X1+y7m1qZ6/bhbO5e1bjL2lqWi9X6Nv0X8N58xuHZTN1ccrt7Y6jMWF/9PLDmvmFzEltvncbk2hbXVjc3V/zv9de32itYtHqOLeHruOF0nfNeqWbG6Vq/fP/G6ltIe6vp5YgI=
*/