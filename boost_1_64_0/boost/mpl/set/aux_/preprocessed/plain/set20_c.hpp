
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set20_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    >
struct set11_c
    : s_item<
          integral_c< T,C10 >
        , set10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
        >
{
    typedef set11_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11
    >
struct set12_c
    : s_item<
          integral_c< T,C11 >
        , set11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >
        >
{
    typedef set12_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12
    >
struct set13_c
    : s_item<
          integral_c< T,C12 >
        , set12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >
        >
{
    typedef set13_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13
    >
struct set14_c
    : s_item<
          integral_c< T,C13 >
        , set13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >
        >
{
    typedef set14_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14
    >
struct set15_c
    : s_item<
          integral_c< T,C14 >
        , set14_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13 >
        >
{
    typedef set15_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15
    >
struct set16_c
    : s_item<
          integral_c< T,C15 >
        , set15_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14 >
        >
{
    typedef set16_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16
    >
struct set17_c
    : s_item<
          integral_c< T,C16 >
        , set16_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15 >
        >
{
    typedef set17_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17
    >
struct set18_c
    : s_item<
          integral_c< T,C17 >
        , set17_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16 >
        >
{
    typedef set18_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17, T C18
    >
struct set19_c
    : s_item<
          integral_c< T,C18 >
        , set18_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17 >
        >
{
    typedef set19_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9, T C10
    , T C11, T C12, T C13, T C14, T C15, T C16, T C17, T C18, T C19
    >
struct set20_c
    : s_item<
          integral_c< T,C19 >
        , set19_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18 >
        >
{
    typedef set20_c type;
};

}}

/* set20_c.hpp
/FfMWNZK315pWN8kxyoYK5S9ESrB5DuH6sby9pR27FTKyd6FdSj3Q8Sxs43Fmvh+o56xDNmD4gJj8R98zJvAZC7EZbA8Gf9Drnxb2hL9psr3v8Zy5vgYZaKL9E0djEXKpzrWxVi+PMf3QK7sm3Er9j7rWT/qyny4Aej3nj+3BhOj4T6vhtFeZfn+l7qSp2OoK88pjxyT6+0dbyxbrjOTjaXJWlzTqHuKt/cZyj3n8zmXci/4PJiHLrL22IvUlX1Ll6CLlFtKPGbI+n+Uy5X1/ygne62+ja/km6lNxFz2Ld2CzlW9zh8ai3aV/T9o75DPjc/JP5nPsAt7Ze/HPeSQxO3vyJD3oYXYJu0doJysbXgYXWTe0l/GCs72OZR6s/nlWt/vljKWnlLZsfLG0mTOxMnG4rLGbzVjeTI/ohbtyZzK02Epnp1Fewf8uX++sUKZ99/QWGSZj1Fjysl3s5cay17jWYaxaCkZ/zNWMETm/1F3iO/rboTJ+9r2yG3l/dIZnz7iy3U3FsuU739pT9719kU/8V9/ZFT1eXo35c7wfd29lJNniJHI2C3jf8ZyZF7zw8ZyH5TxP9qTOYE5+F76kqnETex4mnx5zNedDZM5s3ORK2NLC2hPvmdfTF7JGO2rxrJaexkr8f0ifx69Qd2Onr2FX2QewEZYZRn/I24feRlbkZEn6/9RV3T+jHLVfcwL8F9pr8tu4tHD59oP1H3M59A/KCdrEf5KHsgew7+ji3zjeZQcP+KvoSkdzX+yplNJY5Gf5ftfY2nFPDvJWEzmCVY1lit7yJxC3Xfl+19jGQ/J+J+xPHnXdh66nCbjf8YKN/vzrRG6yN5slxhL3yXr/yFDvjVqYSz6rJfbGrbP90M3YMcQr/NNtCfnRyd8IPes3dA5Xt2xXugseX87TMau78KOzr69QcbiMgdjKOXyZf0/5L7m68aMZcpe7GON5Qzy7DFjBfLd9iRkyHfqT2LvqT7/ZiDjXR+PZ7FN1it9DhmHfU7Oh8nz1iLskOfzV5C71uuygnjImhKrsU3WVFxLXkk+b0BuLfn+FxlyvxE3li/3B9upu8Dn1af4QMYPviKHZI23b7HtHa/LXsrJOgQ/U07WDd1vLFvezR4iN1rJ/L9jOpd1LLmTnYPyLW0JY7nzvYyyxjLHy/ifsbROPq+qGIuJ72say5f3KWnIeNLrcoaxLJkPdy4yDvlyDYzlNfb2XmQsvY6s/2csLvlyBTI2+Fg2N5az3fu+lbHIc973bYwVSt126JLlz5mO6CLXxlvQZaq3oycyZFz5NvwS3onUiDSumBQpa52QbX/UtmYkzVSvP6TPsCFWrUakScXjzP5rpY/9Urf/gMixesnUy64ZeWpjiUgGW4rcfWvPIT0T9VKTIscY9ZIj9Zu3a1+3U/Nm/jeO//qti/+tZPK/f2st9cqmnPCb1Ium/vu3TKlXqdgJv0m9asX//Vt7qXdKiRN+C/UKxxY79ltaSX47brmNyZ6oy8Ri//qt7uBhx4rw+9zj+kw64fcRI0bc2ut2J3dlTuL3Ib3rtm4mOq2e/O/fuogt+U/867f2Wm/dlH//drze9PDbpieP/TbsmD7DEr81aZh87Lesacd+63PcTuKfQvwz6kSG5Byrn18//FjF6uVa2zDKpkQSv8C3NbJz17j9Du81eHCirVTaKqgTGVE1tNXv37m0KfXfbaVG7Bf0s3b4bbwxfqPMv367IPFbpfBb+2In/Hahb7Pvib9dlPjNHlGO/ZZe+oTfGif0LIaekbqR4/6sn57e+7bbNec5y8IvwVfFqRetG3mpeKh39+C7e4dzLPuEesUjx36pm94w8dtlph+/UeZfv5l9tFmCNtM=
*/