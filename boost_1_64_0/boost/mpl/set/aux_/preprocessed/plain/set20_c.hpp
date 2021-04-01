
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
prbx44jXDgwjeXsWC+SNINhW4Kz6JuzyXLRDOrGAxaZ++8M6Iv/o813XD4hpbPKDzbZvnInne3gN7dPVUJ31ckhUqz+6gVnxUNbNcV3pxyRJBp02gHDjWsZ2EQ/voMhmWn38ugRTaPAszDPQJsKOcUaVWLtyCfvkLopt3A8IG4UuZmjZl4sOyZ1R5Qe86wvOuub/8CYobVu023Ktp6dwD4ebgLq6hSbi6ZUkFY8X19/9Y03B0VK4eU2C664YDPJg3+XfafrWOy/7RVpx3MutoM7gorbtXiPb0RQSFgfdmaZ9Owtl0XUdWY99DwhaqwwDtgUY6Hxpu5mKBVvS7c77ZS5DGM4GTLp1MzLNJ44wVoDs2/t7cn1rIqy2WiPed+SiV9NXFxtwZciDuYbvg51W8nXJfzbznUL++zKXP+VL9zQsARTMfpnXiLJBGLNaRxGQfztErHv1dmlfN95A26HEF07ghH8S6I5X0nZ6ofQQ9arlxZRk9RNHGmBGLwNqyR/oUF+61mcR919yIBDf/NKa0vq/Sd3mNtV9ucu2P90aVhRAoR7s6AH8w0QP4g==
*/