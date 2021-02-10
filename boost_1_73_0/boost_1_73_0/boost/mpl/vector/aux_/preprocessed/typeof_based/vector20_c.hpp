
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector20_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    >
struct vector11_c
    : v_item<
          integral_c< T,C10 >
        , vector10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
        >
{
    typedef vector11_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11
    >
struct vector12_c
    : v_item<
          integral_c< T,C11 >
        , vector11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >
        >
{
    typedef vector12_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12
    >
struct vector13_c
    : v_item<
          integral_c< T,C12 >
        , vector12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >
        >
{
    typedef vector13_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13
    >
struct vector14_c
    : v_item<
          integral_c< T,C13 >
        , vector13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >
        >
{
    typedef vector14_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14
    >
struct vector15_c
    : v_item<
          integral_c< T,C14 >
        , vector14_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13 >
        >
{
    typedef vector15_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15
    >
struct vector16_c
    : v_item<
          integral_c< T,C15 >
        , vector15_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14 >
        >
{
    typedef vector16_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16
    >
struct vector17_c
    : v_item<
          integral_c< T,C16 >
        , vector16_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15 >
        >
{
    typedef vector17_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17
    >
struct vector18_c
    : v_item<
          integral_c< T,C17 >
        , vector17_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16 >
        >
{
    typedef vector18_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17, T C18
    >
struct vector19_c
    : v_item<
          integral_c< T,C18 >
        , vector18_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17 >
        >
{
    typedef vector19_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17, T C18, T C19
    >
struct vector20_c
    : v_item<
          integral_c< T,C19 >
        , vector19_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18 >
        >
{
    typedef vector20_c type;
    typedef T value_type;
};

}}

/* vector20_c.hpp
AAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTIxVVQFAAG2SCRg1VVLj9pIEL63xH+oTTSnDePMwCgKMmjL4AFHNmBjiNhL1NgNNhi3424PIb9+u81rRjvSnrcOdlf7q+dXBaZkQkZUsB4x03zN1WvHjgdexqJHZl44JTOcufUDcB6OYBy6Xq02nYAEz/3216c2MY2bkWmc/JCP5CPMWPnCyqZIY0bMkhXZUQFEfRnt4x65uQzsqbs8hWi12hBmgRcuxuEcsY9aNuo90If+cLOxMXp6wOVisDmOI7zKsI2rDR710f/sKTsf/YOlrGy0N9Yz2gec+VaIto2+1p99nOmP1gaXB2uL/TZSX72Hc/wbrQxHS3Q3VoUjlcUBhb5foVXgyMOlb6Vaj9Hi2u4/7WvpdhvnQl/VV1c1RFyqTLQsdT7fr0VZh7pqRAdH9YWjm8HwrSTcsXDg//a29oP32/mF78lg20pEq2ptP+823372S9f780vb2lM+Hg3WzrftKMiiVvAQPS6Oy9biuBomL1HL78Jj6wmwkgnLZRpRyWJF8isSTePMbE15P0sV7kx5VCtXzntE7GVxtVb3a0ZlVTI1N6fBUrP2x2w2dUjMVtVGIW8AMHO6Z6eprGcG6C2nlOdwSGUC
*/