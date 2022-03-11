
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