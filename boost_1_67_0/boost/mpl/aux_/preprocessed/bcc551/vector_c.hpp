
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector_c.hpp" header
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
struct vector_c;

template<
      typename T
    >
struct vector_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector0_c<T>
{
    typedef typename vector0_c<T>::type type;
};

template<
      typename T, long C0
    >
struct vector_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector1_c< T, T(C0) >
{
    typedef typename vector1_c< T, T(C0) >::type type;
};

template<
      typename T, long C0, long C1
    >
struct vector_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector2_c< T, T(C0), T(C1) >
{
    typedef typename vector2_c< T, T(C0), T(C1) >::type type;
};

template<
      typename T, long C0, long C1, long C2
    >
struct vector_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector3_c< T, T(C0), T(C1), T(C2) >
{
    typedef typename vector3_c< T, T(C0), T(C1), T(C2) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3
    >
struct vector_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector4_c< T, T(C0), T(C1), T(C2), T(C3) >
{
    typedef typename vector4_c< T, T(C0), T(C1), T(C2), T(C3) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector5_c< T, T(C0), T(C1), T(C2), T(C3), T(C4) >
{
    typedef typename vector5_c< T, T(C0), T(C1), T(C2), T(C3), T(C4) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector6_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5) >
{
    typedef typename vector6_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector7_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6) >
{
    typedef typename vector7_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : vector8_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7) >
{
    typedef typename vector8_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : vector9_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8) >
{
    typedef typename vector9_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : vector10_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9) >
{
    typedef typename vector10_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector11_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10) >
{
    typedef typename vector11_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector12_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11) >
{
    typedef typename vector12_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector13_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12) >
{
    typedef typename vector13_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector14_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13) >
{
    typedef typename vector14_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector15_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14) >
{
    typedef typename vector15_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector16_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15) >
{
    typedef typename vector16_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : vector17_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16) >
{
    typedef typename vector17_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, LONG_MAX, LONG_MAX
        >
    : vector18_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17) >
{
    typedef typename vector18_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17) >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18
    >
struct vector_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, LONG_MAX
        >
    : vector19_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18) >
{
    typedef typename vector19_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18) >::type type;
};

/// primary template (not a specialization!)

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct vector_c
    : vector20_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18), T(C19) >
{
    typedef typename vector20_c< T, T(C0), T(C1), T(C2), T(C3), T(C4), T(C5), T(C6), T(C7), T(C8), T(C9), T(C10), T(C11), T(C12), T(C13), T(C14), T(C15), T(C16), T(C17), T(C18), T(C19) >::type type;
};

}}


/* vector_c.hpp
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
*/