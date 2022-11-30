
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct set1_c
    : s_item<
          integral_c< T,C0 >
        , set0_c<T>
        >
{
    typedef set1_c type;
};

template<
      typename T
    , T C0, T C1
    >
struct set2_c
    : s_item<
          integral_c< T,C1 >
        , set1_c< T,C0 >
        >
{
    typedef set2_c type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct set3_c
    : s_item<
          integral_c< T,C2 >
        , set2_c< T,C0,C1 >
        >
{
    typedef set3_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct set4_c
    : s_item<
          integral_c< T,C3 >
        , set3_c< T,C0,C1,C2 >
        >
{
    typedef set4_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct set5_c
    : s_item<
          integral_c< T,C4 >
        , set4_c< T,C0,C1,C2,C3 >
        >
{
    typedef set5_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct set6_c
    : s_item<
          integral_c< T,C5 >
        , set5_c< T,C0,C1,C2,C3,C4 >
        >
{
    typedef set6_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct set7_c
    : s_item<
          integral_c< T,C6 >
        , set6_c< T,C0,C1,C2,C3,C4,C5 >
        >
{
    typedef set7_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct set8_c
    : s_item<
          integral_c< T,C7 >
        , set7_c< T,C0,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef set8_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct set9_c
    : s_item<
          integral_c< T,C8 >
        , set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef set9_c type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct set10_c
    : s_item<
          integral_c< T,C9 >
        , set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef set10_c type;
};

}}

/* set10_c.hpp
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
*/