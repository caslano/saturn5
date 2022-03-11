
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