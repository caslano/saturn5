
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map/map20.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10
    >
struct map11
    : m_item<
          typename P10::first
        , typename P10::second
        , map10< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9 >
        >
{
    typedef map11 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11
    >
struct map12
    : m_item<
          typename P11::first
        , typename P11::second
        , map11< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10 >
        >
{
    typedef map12 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12
    >
struct map13
    : m_item<
          typename P12::first
        , typename P12::second
        , map12< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11 >
        >
{
    typedef map13 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13
    >
struct map14
    : m_item<
          typename P13::first
        , typename P13::second
        , map13< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12 >
        >
{
    typedef map14 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    >
struct map15
    : m_item<
          typename P14::first
        , typename P14::second
        , map14< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13 >
        >
{
    typedef map15 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15
    >
struct map16
    : m_item<
          typename P15::first
        , typename P15::second
        , map15< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14 >
        >
{
    typedef map16 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16
    >
struct map17
    : m_item<
          typename P16::first
        , typename P16::second
        , map16< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15 >
        >
{
    typedef map17 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17
    >
struct map18
    : m_item<
          typename P17::first
        , typename P17::second
        , map17< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16 >
        >
{
    typedef map18 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18
    >
struct map19
    : m_item<
          typename P18::first
        , typename P18::second
        , map18< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17 >
        >
{
    typedef map19 type;
};

template<
      typename P0, typename P1, typename P2, typename P3, typename P4
    , typename P5, typename P6, typename P7, typename P8, typename P9
    , typename P10, typename P11, typename P12, typename P13, typename P14
    , typename P15, typename P16, typename P17, typename P18, typename P19
    >
struct map20
    : m_item<
          typename P19::first
        , typename P19::second
        , map19< P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18 >
        >
{
    typedef map20 type;
};

}}

/* map20.hpp
27gCqyljnWMwPon1cC12wPXYFTfgKNyI8bgZJ+EWfAK34WrcjntxB76Ez+Ar+Cy+j3/Eb/A5vIV78Da+IGM770Vf3If++JJ5jpBScn+X+34DQl1j/bp1zNuKGIxVsDYGYR2sg/WwIT6MXbA+9sCGOBQbYSY2xhwMwWXYBFdic9yJLfAYtsTXsDWewTZ4BdviTQzDCqStHfpie6yKHbEedsJU7IIzsZucvwjcgN2xEB/F7dgbT2AfPI998TPsh5/jALyGA/EWDsKf8THUk493qB+ScYKl/sdp3c9/pt7n91LnU+FmmV9U7+NKnc+9rO9xVteTW87rTvU9nroeF+t6Yr/zZpByTx2MZ/Esri734vk/x5AcZnr6//XP/x8G6CzPomny+2O+zKE8B8d2NE1uwP8GR/UIU/oDJejc6Gd9obL0q3Yyb2ltMoyG7vLcqHpOlOdGtrc8BxbLnKXSMF7zHF0saVfmquI/5pEgHtJ+baI17focQ4I7/XiCy0jancwZbJuWmxh+D9rYO35m+P21jXf32e9uPTM7fvZzv+167UJlfbePgo+NWLvx6vH9B/rMLhr5ofvPwL+k7Xp0afncyefxRClTe9O+UkYXpHpGqIwPYXWsjcFYD5viw9gN6+MAbIBjsCGmYyPMwcb4OIbgOmyCe7EpnsRm+DY2x4+wBX6JLbEUaWuF92EoPoBtMALbYn8Mw2Rsh7PwEVyN7XEzdsDd2BH3Yycsws74DobjOeyGLcmDCOyA3TEKe2AmPooLsSduxl64C3vjPuyDf8G++B72w4+wP36Gg3CIF59JjMUozMXB+AQOwT/iUHwNo/FjHIZf4HC8iSNQ+TIYiYE4CmviaHwYE/AFTMRDmISnMRmv4hgsz3lPwXqYiuE4FqNxHMZhGqZgOmZiBo7HTMxFPc7E8TgHs5Dri+tJ7o1yz1Ret+Hfh1Anbei9cDqWwxnohzP5LxBnYTDOxoY4B5thHrbFudgF52NvzMdIXIDRuBBH27S1L8Al+CQuw424HLfi4/gsPoEv4goswpX4FT6Jt3GVlEGswSq4FmvgOqyD67EhbsDuuBHjsBCn4SZcjE/jU7gVt+A2fAa34wu4Aw/hTnwPn8FvcRcq87vtxub4LHbB57APPo8D8QUchi9iAu7FmbgP1+NL+DL+Cd/F/XgTD0jZwkEsj4eMnwPX5sdxPH6r6vn3zs++PPO69rxrHePV/pk2FKMI8gzr+PlV9ezqg9rnVBkTFp09l44k2M39gjJeLM+dSLjT82YBQZ4xtWPKdrE8S/IceednSHl+lGdH7bOi/XOis2dE58+ENx2PSSvPfvbPfGcIU+U5r5iwjme7vZ7nO8/iWTyLZ7kry715/k8wpCsFAHfh+f8jVf1/kfz224VVcT1mKmOWJFnrogdHdYvq1a87w+mNNT5HhznOhjn8ViQdjxif4QN0pY11068l29ZNS90zmp+xKxPMY6/4y78zk5OVEVIS4yZZx9zxs65nlBNT+cAZ4mroo62zPiFlCsowSTHZpniKWKfnROkl3tO8HvEQccnfT/I6R571LWOmyLO9TtLoJX1fnqZDX+wY+/xJSElKGOdGWcNVX9KN6nF0fKRtwB7p52acZ1J5QHIUH0OFcIaTYmSssCiXz4vE7+g8yOu9kq8GQ7rx9W7JUzLe+HqPvOYE8dp6HrJ5v+SfZky/DdLWYQ2+RL7Hptgdj2kMHsm/BnfKP66rT8baX1fpxB+vl+OR4yM5kj5JrxzfWXmdIq8vy+sx6Qbb8f807RXIL025FZenpdzKl/ipD9W0d+gnr8/L63Q53+bP327Jnwfl+qpByOZ87xlnnz9c+C5fW44/Y9prTXm21Mk=
*/