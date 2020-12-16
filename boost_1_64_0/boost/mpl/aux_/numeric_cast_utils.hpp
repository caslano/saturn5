
#ifndef BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/numeric_cast.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
#else
    {
    typedef typename apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >::type type;
#endif
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >
    {
#else
    {
        typedef typename apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >::type type;
#endif
    };
};

}}}

#endif // BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast_utils.hpp
F+Ee7ncmrk14t/pNiF9LTYRoHj1dnuBb7sKn9OCPjfs0aPG+5UTF54Cc06tGbnCsGrPur2YnBnyrcHhjuctfnA7VM9/7smByYvYdsVvQDJ/jlTvFTz9bpsn4i3v8Os4VXF88w/zYhMJnI9Vui3LLUB29ulczH7zm2BurSypq8pgE2j77/fr1v0W57o/v1+8C9TVkR9jdtBMW9SuOrbJ9Rl3hGdX5yl3anox0eTcte6Jt2Ukzjk+afzd80PBfz3Qe2+NY+udNB9smyHM69ODPCOzmckV6N849v09oZJ2XQvMDq+s5d98d3S8mdYrTmPanyjm/WDpUM7rRxOsXPN3KXXXyTu54cKBljL35pFlXZr9957xeWOZN8rx93z/vVj6KPLhg0z1lzlP1tsY7B2XlL2g+r9KW5Z9bXu7quPGTXcUnX96sajDrr3faWY6y89/qNyeLqtKyi3L0Q+p1FXdvz48rD4YOX9I7KC7rY2HHfI/zfQ+OSy0KLdNz1LbsX1r0OVZ137ONh+eP2nW0b+bWm+/SPZZ09rDL54cMTm4n85/eKPTxsFXd+12sFjxpQN7lhJjKPsfWCQT1lt/PmDK7ZoY87Nmgv/Y7PL/WwqePK/eZ4/Bq91fep+m/Ct++S1+0bH9Am413B3RpUbvMg55Xbqe+Chhy/skzn7cNWzxK2zdjb/aZ8MsrQp2O+7u82eUeusp+aBmH1n4Ztfut2TffdrzTmfhLNTxvjY9628Tt+37HyDm9jpxRjpreuNLxxRuXCwfdrJtvTxdm/YVv4yDFTS2fqo+Z+irY+sT2pv0LXbe/ntey681yE7e/yxKnPhrd8ZRlveDb+14F3hmdG71tcuG9r1fSkvp7f51ahxfs362jd7Z77edtZ3VYsnZ2duR8YdHm55lnsidUqnHicTp1cFCje/tk8cPrNpSuv+43JnLzjtwJgyrbryu4Uv61bWyL7MnDRKcfbd8xYwO/TJ0WOeUbvx1iM+Z7pSfWcr+7NvHdzn/3GBFYK8pb3OrWuyVjN432Px3p5ba745xpOaFXzk6K8TjhYJ/VuVWmXecmeYPX1Kl7afinzP6W5V618glfWJhucyXPa1Klv1ooclbfjlqqqVxT+EX1vvW5bb6twj6GFdQ40+t9brZzpiKnYa165RwmHfQd5TLwuPXhX7Medcpyx0/0HekS9jCzU1bg5qnBMzqJvR0S21Rv+GpZZu0xRRXfbY0NbPpYOvuuzdQuobNzgxZTz6at2ZioPL5o0e7VZRWK8dvXt31ac9KEsdmPBEKrXtmverZpeb9wwOvlO8bvvYmXrX2TuIVrbOwDzNpqLGPzYw5vSNp8+15b/rGX3fu++bBg2apGNg5Nrjy/6+Ree9GeIMvE3q57R1w90n79mmGK/lNlJ44697gw1fNck93tcwYlTi+7pyi01cqRx5yL+JXXHnOdFrsnu/DCE8ffpmaX/ZyUJAypXzjsTPzUVdNfWIcdG3tLmThk+ppqEX1T3/f/5EblD0jb/+trUe6etykHH6cOT9gjTMu7urKa1/mk6UNr8ge7HVk06Kv1X+4Gp3ivEy4se+jZqHYvmsSOSRj3JNDuzHS/yIvHW3YMLLT/3UJy8Mx6/3YFe+5mPpguTpdu3TL7wcWjHuZl1i0dyWvyOq5DtVW5NnVufLx8q+rEjG3BF4OWNRmT2Tc8PIk3eEmtnGbrp/hV9Sy0udy0bxnP+ovy5iza73h3j+/EMnWuhzRXOCy8pPwe4z/Bf5ltuWd3Cs55qTK2JN+sUbNX+zLTlJur2saERwYcDB3auInwcWuHJ3Nepl2vtuX1hbDPc1csDeh1pkfkt7ELRpc51Cw3pHVCM/klnvBA6nk=
*/