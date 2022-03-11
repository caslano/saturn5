
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