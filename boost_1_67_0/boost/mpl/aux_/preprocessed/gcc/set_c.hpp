
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