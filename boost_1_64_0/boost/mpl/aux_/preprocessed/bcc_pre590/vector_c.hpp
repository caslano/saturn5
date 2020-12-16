
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
MR4qEcuYMP0U7W+UHm0I7xI3aoavHqR2FPKN53dmXt6k9FzVn/4tb5LTJtB2DhbrM59vrv6lY8At+Th0in957uQi0Tcfrn5f5Xx4xwBrG5t7qn8be5+4DrN89YPg9kT2OpxqOiOblJzta4kzfZ5FDXzO/jzN3+5jKXHiXe833kZVxTHDePbgE8luzLDoUSw9mkiPxoR7SCjKV48qjhOV6GFjj2q1l50uCVl6VmQQPjDGBVedpaVnpeenJxszsuDzDrc+PWRT59bHeHalkYRnnidbWN7lrfM8bGYMu9R1lNeUKFc//FJ128D0HGQaQmr+9tvl9TVnP0FzdrjLsOO62ZWXHCMfznlIaOe1X3oL9wU891P5s3neRdnMVWICzFX2m555WTp7tcI7D/bMZ+J0b1p6rsVfgPFvOWPzneVWgOA1/Ntgw+7qZpP9t+53RHjPvL9Of9/IIGFcr9D1R7Gu64+815Yy7iwb+Tt09tkc+Alxym7xlrHGl2P6PuE3pzCXsdKKNbdz+7mg/buHtcw9due+9WWUS+RfXOVSrnIaputPdb3J57rjrdZyvlzXzzWylus+leuV6ofDCZ8bGZrlLFeO2E3PzRybnJqX3TbkuZq3LAKXa4Oapran8kpAI+Zfamfmtme1m3TE2I+vDte45mwE5qH1WI1pZl8FNRvaj62JPjpoWD0m8m3GVEu55DcMYKs969ex1abB2ttqzzr+ttoFjQLYas/6dW21e0h+lJ+tPkSnMsnXed+8/PQePLTfkMFVKQ+eb5byGNagEttm6TNN/fp6wh5jjuvSx1jWzkgfOyGZcQynIIxHYbwj74419W/1XaNNOjRWnTkbGcY40tB13UPXJzWy+iSaLvv6LdKxVDoWzrbqqEEo5PHHrF8j0zsf6ej9zl7vrT56R86xXrfmWvmwlPUa2dA79PzPgnuNfMxRPtw5MJ5RfHygL4c0D3j1NpNvHNPYSiqW8UF5rXQOYJf/WNO4bMTbp2eRV0uvvxB0so7XmgcwB9BagWduZT9+yya5JKBNcmDbY3tb38A2yfY2xoFtle1tbgPZMIdvq2xvMxy+TXK4trjh2iTb2+gGtj22t2EObHtsb3Mevk3yq04b43r/WN1/z5apkYuWr117fZ2p/whk+31sbYw7R+g7m9ZOE0ijJmylzvutbEi+g6fDCtgBfq89+30J5bq/m+6vDS912zDq/uEwRrZZTWWbdbZssy6RbZb04dtTYH0OKL0fpc9P0udn81mvuv8m3W+2WUzW/SmwGRwj256x8I8wTbar6XAwHCcb1vFwHMyA18NM2RBe69WbbzKB9f5ccr+Q3nuk95emcnRMC1yO/XR/f5XjAJXjQJXjIJXjYNPZsKVK72OlZz4b9kKl1x6eAzvA1rAjHAY7wfGws2x3L5aNUBe4GF4C1xj6wafgn+AW2BWWwW7wHZgAP4DdveXE94TA5bRBem1UOW1SOW02t48bA9+/Rfe/pPtf1v1bTeVcoPtTbMr5Kdko/U02SX+HCbLN6wXXw1GGnh4baa15ay08wcdG+hyld75snS6AbWErOAS2htfDCw21YBtYBONly9QOPg0vgm79KyRvio3+F0vepZL3J8nrCkfCBJgPuys9/s217guzlZ7njGLZjEXCaeon02E3eJNsMAvgEDgDXisbsizZkCl9reHyLLVJP0fpO2CcbIG7wlz1w3w4CE6CE2TTNhFeb6rPYqXfzqY87lT68+CJsBCeJBu/xnC+bEoXmNpXhdKLtWlfu5TeR2pnH8NG8BPdnxih9U7YVvfXgb10/+O6/wl4MiyW7fyTsAV8SuPQWtnSr/PqxfpjYL0eUrqes6yl1yPm8WVG4HI=
*/