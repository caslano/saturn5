
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "vector_c.hpp" header
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