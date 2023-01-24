
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list/list10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c< T,C0 >
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct list2_c
    : l_item<
          long_<2>
        , integral_c< T,C0 >
        , list1_c< T,C1 >
        >
{
    typedef list2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct list3_c
    : l_item<
          long_<3>
        , integral_c< T,C0 >
        , list2_c< T,C1,C2 >
        >
{
    typedef list3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct list4_c
    : l_item<
          long_<4>
        , integral_c< T,C0 >
        , list3_c< T,C1,C2,C3 >
        >
{
    typedef list4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct list5_c
    : l_item<
          long_<5>
        , integral_c< T,C0 >
        , list4_c< T,C1,C2,C3,C4 >
        >
{
    typedef list5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct list6_c
    : l_item<
          long_<6>
        , integral_c< T,C0 >
        , list5_c< T,C1,C2,C3,C4,C5 >
        >
{
    typedef list6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct list7_c
    : l_item<
          long_<7>
        , integral_c< T,C0 >
        , list6_c< T,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef list7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct list8_c
    : l_item<
          long_<8>
        , integral_c< T,C0 >
        , list7_c< T,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef list8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct list9_c
    : l_item<
          long_<9>
        , integral_c< T,C0 >
        , list8_c< T,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef list9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct list10_c
    : l_item<
          long_<10>
        , integral_c< T,C0 >
        , list9_c< T,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
        >
{
    typedef list10_c type;
    typedef T value_type;
};

}}

/* list10_c.hpp
F92fWufMnTam0+/zorbK7CBf/bJ6gh5ptz0ca/2TNkVOz1zJhJjeG33r0zLbkUxGbYd3eGB4HcHtiryF/qrcvtiOQ4iS7eS/eiDwjZs4a10AY2H/hkL7M66ABQmOazgHf0+l65k0UigDNMoFy/d78Z4lH5VT7y6i/spADwRQsacBnRt+tYKLX63GDBq5rxjpwi8WmwTyKdNCtpevAcuz5I+DbD2iu3dH3XoGYb73woqST3eCeeF+Bdwd43mdqUatb6iDE0n2WmbtqXViOa0B90XyKcKfFryK9qugHlQQr0f3q/CcMz6PkAdUoXPDUw+RLMo8v71Vtn1hugVudrm31L66fhjhW+EEODe73pvoGRapsoVC/9R0uDX70fLc6oMt5qOPlFiMvDae+Fle27zaQR7B5RPjk0Oo4TvfP36S9pC9fdpnEsfJSmWFzYsYOcHOwL3e9qFr3+0EDy6/x3i/va7XazypbuPk+P+Qm6/i4RXgEU4H8Qoz/Ij7U0g45BVcLp3s7w9le4VhwDD+hvH4yVo9jv+3Af/zf625A1q5uJo7/4vhfTw1ht2EXXQoaZDwP31t9dI3o+oLnGHeNb+Ov6dkOfz2/au7XPlPGQKnSWutdh8CbX6eqqFit1OmIU6ruUaDMk6rVe2YiwWr9aHYNZ6atWLF5/p5DqVTGhqrW0tbUB4Jd9+hh8Vlt+57WalK2I9eFpceF/B6BrvL
*/