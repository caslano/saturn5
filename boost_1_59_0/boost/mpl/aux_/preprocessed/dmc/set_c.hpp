
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T, long C0 = LONG_MAX, long C1 = LONG_MAX, long C2 = LONG_MAX
    , long C3 = LONG_MAX, long C4 = LONG_MAX, long C5 = LONG_MAX
    , long C6 = LONG_MAX, long C7 = LONG_MAX, long C8 = LONG_MAX
    , long C9 = LONG_MAX, long C10 = LONG_MAX, long C11 = LONG_MAX
    , long C12 = LONG_MAX, long C13 = LONG_MAX, long C14 = LONG_MAX
    , long C15 = LONG_MAX, long C16 = LONG_MAX, long C17 = LONG_MAX
    , long C18 = LONG_MAX, long C19 = LONG_MAX
    >
struct set_c;

template<
      typename T
    >
struct set_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set0_c<T>
{
    typedef typename set0_c<T>::type type;
};

template<
      typename T, long C0
    >
struct set_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set1_c< T,C0 >
{
    typedef typename set1_c< T,C0 >::type type;
};

template<
      typename T, long C0, long C1
    >
struct set_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set2_c< T,C0,C1 >
{
    typedef typename set2_c< T,C0,C1 >::type type;
};

template<
      typename T, long C0, long C1, long C2
    >
struct set_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set3_c< T,C0,C1,C2 >
{
    typedef typename set3_c< T,C0,C1,C2 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3
    >
struct set_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set4_c< T,C0,C1,C2,C3 >
{
    typedef typename set4_c< T,C0,C1,C2,C3 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4
    >
struct set_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set5_c< T,C0,C1,C2,C3,C4 >
{
    typedef typename set5_c< T,C0,C1,C2,C3,C4 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set6_c< T,C0,C1,C2,C3,C4,C5 >
{
    typedef typename set6_c< T,C0,C1,C2,C3,C4,C5 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set7_c< T,C0,C1,C2,C3,C4,C5,C6 >
{
    typedef typename set7_c< T,C0,C1,C2,C3,C4,C5,C6 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
{
    typedef typename set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
{
    typedef typename set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : set10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
{
    typedef typename set10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >
{
    typedef typename set11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >
{
    typedef typename set12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >
{
    typedef typename set13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set14_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        >
{
    typedef typename set14_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set15_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        >
{
    typedef typename set15_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set16_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15
        >
{
    typedef typename set16_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set17_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16
        >
{
    typedef typename set17_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, LONG_MAX, LONG_MAX
        >
    : set18_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17
        >
{
    typedef typename set18_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, LONG_MAX
        >
    : set19_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18
        >
{
    typedef typename set19_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct set_c
    : set20_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, C19
        >
{
    typedef typename set20_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19 >::type type;
};

}}


/* set_c.hpp
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
*/