
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set_c.hpp" header
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
struct set_c;

template<
      typename T
    >
struct set_c<
          T, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set0_c<T>
{
    typedef typename set0_c<T>::type type;
};

template<
      typename T, long C0
    >
struct set_c<
          T, C0, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set1_c< T,C0 >
{
    typedef typename set1_c< T,C0 >::type type;
};

template<
      typename T, long C0, long C1
    >
struct set_c<
          T, C0, C1, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set2_c< T,C0,C1 >
{
    typedef typename set2_c< T,C0,C1 >::type type;
};

template<
      typename T, long C0, long C1, long C2
    >
struct set_c<
          T, C0, C1, C2, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set3_c< T,C0,C1,C2 >
{
    typedef typename set3_c< T,C0,C1,C2 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3
    >
struct set_c<
          T, C0, C1, C2, C3, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set4_c< T,C0,C1,C2,C3 >
{
    typedef typename set4_c< T,C0,C1,C2,C3 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4
    >
struct set_c<
          T, C0, C1, C2, C3, C4, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set5_c< T,C0,C1,C2,C3,C4 >
{
    typedef typename set5_c< T,C0,C1,C2,C3,C4 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set6_c< T,C0,C1,C2,C3,C4,C5 >
{
    typedef typename set6_c< T,C0,C1,C2,C3,C4,C5 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set7_c< T,C0,C1,C2,C3,C4,C5,C6 >
{
    typedef typename set7_c< T,C0,C1,C2,C3,C4,C5,C6 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX
        >
    : set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
{
    typedef typename set8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
{
    typedef typename set9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        , LONG_MAX
        >
    : set10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
{
    typedef typename set10_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, LONG_MAX, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >
{
    typedef typename set11_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >
{
    typedef typename set12_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, LONG_MAX
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >
{
    typedef typename set13_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set14_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13
        >
{
    typedef typename set14_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set15_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        >
{
    typedef typename set15_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, LONG_MAX, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set16_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15
        >
{
    typedef typename set16_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, LONG_MAX, LONG_MAX, LONG_MAX
        >
    : set17_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16
        >
{
    typedef typename set17_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, LONG_MAX, LONG_MAX
        >
    : set18_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17
        >
{
    typedef typename set18_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17 >::type type;
};

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18
    >
struct set_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, LONG_MAX
        >
    : set19_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18
        >
{
    typedef typename set19_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T, long C0, long C1, long C2, long C3, long C4, long C5
    , long C6, long C7, long C8, long C9, long C10, long C11, long C12
    , long C13, long C14, long C15, long C16, long C17, long C18, long C19
    >
struct set_c
    : set20_c<
          T, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14
        , C15, C16, C17, C18, C19
        >
{
    typedef typename set20_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,C17,C18,C19 >::type type;
};

}}


/* set_c.hpp
Hm2F1nRrUaHrTI39DdytefV9bbH52lb3a4jN12S7X0NsvubY/Vrt5HO171tWNl896/wjg//xTO8nWueNyq6/Ndzma6bdr9XOs60JXh/wfqeR6W2TH+vxWUWPwsEXu1u77PuaY/saAZlLBNvIWRvqGoGPlLUElbWE+1BdiyHhzjEJ94ESrlrCtfKQXtAU93rfUcLF1hLubSVcaS32vaWusZgi9nlIz1KL3k9VvbWEO6KEK5/i3r5P1LUsBvuM6e1FqiQccyMIZw+zW8J9rqwNioZfwyHwBBwua4JS4LdwEfwHXCZrgtbKmqBb4A9wFzwJX4M/wgPwX/BdeAoehj/Dn+AvENGMLmncAMAgeBbsCBtCySfzGdz7LVnxR0kt4ZLUejfJvX8nqPVY0mvlIb2KWvS2VtcUuQ0H1XC12Beirj26QuyrNT3kCvd6+6lrj2oJ11cJl3aFe/t6q/eFwT7z9Epr0fuEel/UEu4xtZ2qxb5HVD8b7DNPL2C6e70rVD/XEm65ml4t7U+JWh7TxT4P6aXVojdTvT9qCZeh1vvp7u1LV8vDYJ95epUSLtJDOx+QIuE8tLextYQ7ovqllnBJav1zHw4qa4N14fRrGNvImrNwaHtPp8SrriVejMQ7X+J1UuvTDPd29VXXVs5wn/4ASX+gpH+JEq+klngJEm+oxBumlnstdj2mpF9VS/p7Jf2nJP2n/83e+cBXOe9xfNVSKVltrVWr1orWX5X+S21ZKWWtWpnudLbaqtX+nPanFl3NFULYJYQwlXSvMORe7g2jEMIQohAmIfeOm3tDuO/nnM85e845z2nnkPv3PC9f7z1Pvz/f3/f3+z3Pc57v748pXsRs//GeVrztirfD3F9c8RroL/ZjhJtr0qPyGHrMkx7zpUeuKV7NMeItVrwixSsxt3+bM16nBvrJAJ9w1v0k0yecdT+p8A1n/ZzzGw6a27vCdbQof2eVvwuMgV3N9Z7pP16C4vVSvN5me2RKrwb6SeYx0h+t9Mco/URzPzlGvAmKN1HxzjHfR330su4nNcdI/3Gl/4TSf9Js52PEe07xdire8+b36Szp1UA/SfQJZ91P7Fn+9ciTHvnSo8AUr+IY8ZYqXpniLTOvlaPnZ5biaa0cn7U32kHX2hsbYU94N+wHN8HR8B6YDDfDNPg7mA7vhRfALea1AKTvAeVrXgvgcuV7JYzz2pNwBLwGngevhbNhBcyHv4W/gdfDq+ENeo++Ed4Hb4IPwJvhn+Fa+Da8Bb4L18EP4e0wht+RfZ8ND0tF8pAKZCuyBzmMRD0XHjYKyUSM+c17YpuEHYpt0uCeiFb7aa/dHtobcQusKQs/5v6I2S2a/OQ9Eh/dzt9l4b/IXolhy8K137X/PRPX8O+uecZ7tge+d2JZiyYN7p94aDvnO/61+yiyd7zPnOKYZeE/eT/FhGXhQc8dXvkL7Km4iv68GdmJHESa76RekTSkDFmHVCO1SPPn+TckFbEjFUgVUoMcRmJeCA8bjmQgZcgaZAuyE6lFwl4MD4tFhiMZSDlSiexAapHwXdwrkGQkG1mFbEF2IXVIzEvcg5B0pAxZg1QhNUgdEsXYusFIOrIcWYdUI7VI+Cv0BSQVKUEqkCpkF3IQaV7DvyOTkTykAtmK1NSE5i+HjtAROkJH6PjPPcKRhb/Y/P8F7MKfXWxbmlvQ37kvw89aA6BLWPM2H+HMTE1LtZ2VNHny2KSzJtnGpcycOG1KSpjmsV9DSca65rpqX74u8vXGIpPj+d90h9/yrGnnp6ZNsaVNmDYuKZldq3KyCljy2RhiH8Cazy7/ZXy4c38DY7+wFo50WfMtynNMzT7p0Vf+0wTkXPQYYKkHpcU=
*/