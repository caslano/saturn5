
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