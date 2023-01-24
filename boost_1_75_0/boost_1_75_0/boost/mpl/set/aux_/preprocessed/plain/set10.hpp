
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct set1
    : s_item<
          T0
        , typename set0<  >::item_
        >
{
    typedef set1 type;
};

template<
      typename T0, typename T1
    >
struct set2
    : s_item<
          T1
        , typename set1<T0>::item_
        >
{
    typedef set2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct set3
    : s_item<
          T2
        , typename set2< T0,T1 >::item_
        >
{
    typedef set3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set4
    : s_item<
          T3
        , typename set3< T0,T1,T2 >::item_
        >
{
    typedef set4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set5
    : s_item<
          T4
        , typename set4< T0,T1,T2,T3 >::item_
        >
{
    typedef set5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set6
    : s_item<
          T5
        , typename set5< T0,T1,T2,T3,T4 >::item_
        >
{
    typedef set6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set7
    : s_item<
          T6
        , typename set6< T0,T1,T2,T3,T4,T5 >::item_
        >
{
    typedef set7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set8
    : s_item<
          T7
        , typename set7< T0,T1,T2,T3,T4,T5,T6 >::item_
        >
{
    typedef set8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set9
    : s_item<
          T8
        , typename set8< T0,T1,T2,T3,T4,T5,T6,T7 >::item_
        >
{
    typedef set9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set10
    : s_item<
          T9
        , typename set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::item_
        >
{
    typedef set10 type;
};

}}

/* set10.hpp
c7Ir4M7NSZqRB50ytBWX4ZPKSycmrhbxXH7Me2Xmpln9TFMxNcq8YGTm2igOeCYjIDCeoyBLScQvurK75r0LEazxV2nMXkh1aSxa3MNRSxqzUa8Lt9ha43YUSt75m1b0eu6wdIdV6cwdoQH1C3M92LgN7VhijC3R1lsRhzglW6JbdlitxJ6JeqJf77j+ivHQSq/yVPauzSacGb/WIZWV6cegGvJT6dU5/EKuVsucjk4n2Fg3kPjCiMEcG5KOKPkBknmwcCo6G2fdyhbfym5hDfBhnG2FyhToWtkK+TJPA6s+LiolxGRLlup+hx7K4qdkOgPBdmr4ydUF88Vdsk06yHL6aGXM06chwEygV13jlU2kbhhx42zBTCt+FNMtf/nCfZtq5YQznzvNCNP3cRFLLOPy32rzyXvWHSTNyG5l1JvB5Wyz7XZwlQtPaMuKQ+6yFgivkGeGnLIri7XkEAR68yOG73oW/h3E9wrHwrh23QjEILkeL+/sQPBkL0zxB4XNBwYqjThVJa1SzgYr2U5mjaxSaY3CUtX5p2u5hv3aEqCEDX/i8dv1+fFoaI73h9W1yAf2Po4mUSzWPp1FqgHdEHbcq3lgPcp+k+lE8vADyQcSljxaqx3FVrmmtvQNcZRj8hVpsqNZBeDRothlLvYYpnDMV7rNwssp8JTHF2Fh+KhFhhCQUTDLX7fEFo1R8Lj+Truu33K/4EqTFLmk
*/