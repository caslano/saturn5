//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_8.hpp
pdBMmts9u+0jQr5acCvQSCEd+DpJeq64sJ8ZCLfZBafmzgnh6ajNfAzY+53Mt9nrhaD9u4JIwwPE2xSGOU342cv2tLEEqJiR0HZ3XFLILIFB3bzkOrHbF+EncfhzF0b90rvbKqthIDfFraCNRmVCUX/wBU1A4zq/jrL0M6a9xFpZbRE1Hojzs3/AgjXlfORVyiFSdf25ss5bJqioomHLe1cdxBUetMJABc17TY/lmkO/VWRVmyA/Unfip0ifZLoNoZRfAwM7YQWGAJnEy5mJbuHkGwcaPznH+Bkbu9lTDa0XPB9S+nM0a3XmTBgEBaBrWJXyO2v2aug0POFQO1ZtSDVXP5fqbS4Gv8yJqiLCxlh5ftuFPVg1Q2heQrOprvu3yqn0iF0OllZwXrXum6D1rHZnLgW3NRmZ95ljTUs6Jyk6BaXEiAdur/uRQBH86VjKCgEAaQtTOz1XDhgG3zIK3kIfwku3u/rMLYAdSWDhcZxS0atkYCdkxC5RfrSPa3JbIHJ/JSKT+tOzXOswnWPCjCUm3FMZUDQocjzMJJpWtYDBXX8KBDrrORRed3LZA0Ur27jP29mVUsgbgv9Q0H9rmNvMaP4o4Qwe+zzp2haJD1UTPtOQ1stcHrHl1tqwykz2R4C8Ts0sIAwW3gEH1Bf5yzc5aEYuF61P4wjgwhwCktIVWhyLa9E6tfwbH/H6Z0hdHpY+Zg99IX1sP+HUYF+FBDgBTxl4bRwHUFcwnJq5LiuoUiAuJieaNGtfhCVKID8+KKhQWLDgEVZ7qrloN2lOnyysQmmSxDQHd4QOytoAbZH5HS1ZfnccUbIW18cM1OVFG8eHNShhrCi5bYxEIMlKX24qbqK90pwrnJRPcRupXHM3HotVKa3kulkn9SCah4XzujHXvOayCLbneczkBjw33/Vio5k7nsVn+l8ESbHkR3GcduE40pJ3TBtOGHEoCDF7qpFTiVfx0meyZyogabenYy7KkoefxEjUlBAeIM2o9yZBc9vQ3jZMwV4DYzn9mDA/Q0eCn6RKSPegLSwPjtdVVseych9INJVONscmqAUNO/sEDxLpPc9dVyZzqJ7BaALmhrn/zRvJdFakRf0IKTzpgEQRnKvH7NAYFG+l7hGLwIKU4Jz4gn5x1dCzq+QqP7ULSDmZ6+peJ65YCuqr41RPdXciDW/qiYaBx6HTjx9X16iA0w/IkPB+Taea1VMzZV7Erq59vKxIo+BSRGiu51hjisoLFX6DAUBboomEZHXXe6lOU+E5ZrEiKFqgLVBsNnROKe5oixOBkqao10imvMAhkNbGsufshzaXhe9RAaJFUEQWILUUWRM+zTj35EWIfkBnwzRS+jcajdkLVUnVzIepsgWqyZbRDd7s0wTMNNa6U8ZfH07STUlIWyZJXS6kzffJNrz+ACsfK8HWzvUt00AKcQXxMieX+10XfdecLtKA2ARvxdHX5KtmcsgrOriblfjJ70VeK9crdhP0RsVGMzTrUnBAjBN2Ggn2YnQbjLD29UCHsgtDMW/GVAt5mKpAkhYbNWvxOrjZ6cBCgS0azUH78Oc8AjEoOpkzaCXZq59S+2fJe9qfWheHcw4pYjd84yGYCuSovCXsDKW9IMkVrmRvWDu/C1gKCCBpCk05N2DHIX2KHwTno9aZkPcpRmqWkbOa6QsaW9v/FJIXfs8hfxRJFTrcYopREUiZTHwSAeCPIBQgt7I9yM6A0ga7qIi5U9goE5KMTCViUCt69TyH/YbXHXfPFd0g5Drgi+fk5SoHQ4AyGnOLzmOCP6OCtHpBepJX00EwIipDOI2XVdR8Cpbc7OyVp0fgw2x9rIl9S+6fkX05b7XKgyIvGondK/Q8mEagAffyAg2NWniyXbRZ98kai9Ny12jL3Gbk5xwVLCIT2FJdffnBlww3YUjC1OZdWLc5uQeeKZddFO95G3iGS3f2hsspIsp6se+5FtIaZ61g0SUnk1TJlKpPf5ghm7LqcxIOZFfiVLZJm0jGGcY8QhVfEzXojA6HNZHsNHxNb6I8CrjZwQ/TZRTU4LVrDcvAxL4q59HEOs6vihYsjgHtp4IWUf1WybeJoc3GxpNgIEshAaQgQLloPFfVWKhjLu16SXTYQ/gwA3IwmqPQuD7JPbFAzo3IjJfAFHFwyqHjw8KYxiPd9jKggWH4R5GcURlAKcpp6irE4v1q7djQq6e4T4fRRCnkHviMtLWpqS0y4GeFq6yD5p9v2fisrgQowsGiwonmE+6kqTCvto/YMcubN+9Bt4RSos0okDYKq7mrQSjynQ9k+oLieAQozL+6xcxRh8dlOoUiGfKfQS7h5GMlpdMn2kxmSBfO7Z6TJncLjAlSBEPvmAeik+i7dUYcgfOdmWtXG26VJCSTqWnKKUmu6tNBe7wmLGHJNY+CG52FWTnBtC+2Eu+fVVawjU/q2fKh8XQ1LYUxJvJcZcwflcocrybN9iBpdhp/rrBlkrA1MA1IqDvEEW51/4dzTq/AIgE2eg2pCN/Ng7Y/VHiFvA05qwGemekGRrb9lgfCtgjtQLHolZspCPJG5+Nfie/4KCMpDr5Yt0ZGM3XU+SAvzRMUGo++xBPsqZTIi65L6T/EHhPVSkXVob4chukmSEPRMuKcFCzBv6JL1IsW/KB0O62U+88W0pVBGgnIjKS9RV7HO5NKVfc/5xCa1z5W0tsCCZHUdtAeNJRaIKUzavqnO44g04U4vU7DOgnhY02g/5J5wxW/FWypGsZRUz53OUX1mMJIBhyHbuEBEN7xaLiAFoeIE7zI9edKvyADNCgExfmANWHd5pkZNFCsq24V9FHZK9hb5+k+9pJWFQaJjE3CXPh115UnGAuKAl5H5fvME2d8vFFh6HNWfSWjJH5xYKARVn5/GCy1PxOunPSPV6J7xeApzb+Ruzyf8m0J2Ag0dlZTRETUFYO6tVhbvsBJ4Y+oCMisyh7rwnwhwUjSVlgNjkOL6jvozdBBojE2wXde+rT8Rb36sakwCNzvm2VFIfeH4/ZrrcNaobNoOUFEAe3JbYXEXTDilxaavrVSDOhe5zVTdfEKFQ8iJvj9Z9bo2jAFzicRYRs5V1jnWZBj2geXXG/kmiYVl3N66tDX3gKRisnMv5c9sz6qtfX4hElD6qEP/DAQy1z2DwDkMrzXQY/6fTfjYYzgLzEVkn93aA8MWsTjEmMTEi+X1Wv/LdASdhHLknUa1jcUBSXmGTmt4dnaZQegQjZdUu4D2s4cjVT2dyWsmLVr7/Pzi+XHXCdBQZnDekym3T0ybaemrLmbKmqL6fmbHUlDWRrlkCzK3DnIbnOIPPgZVRBgFY+1z3EfRRVZdpI3EoGfaEwc6qniYAKLyuJnPhu9sbsxS4Cry1GMgGecOxTNQ4aCvDlKJ6AgwUV8kHAo99c2JlcsQIRk0FUHToLJeJUR153FKu9fQf/082Z+sKT1bJdnyjuyp57Ba7HEx4eyfN9TJhg/xsLILhjb1lqOapKND/iQCKYKaWYp4u7z2DF0Bu8nTw8EQkT/8HzB6h2Hm8ylCP6XV7khTRmcvxAXJjwU5RE82C+Up4sgtZSmi4mDtJvcywczXp8CQQEZC7gLhg3motkoyl4of7XVg+DR6wE7JlIcZOP2lqDMM3qJBokiuhpkPoJE/AEaSCAfOKbJLEnD5k1rTZSYMowOLRzYFTVzw+s8UdG6AoNhLjZ0Gb7QnsLS7gPJGc9Xl7SxdjJIIPGKO0oLXtDhryQr22o4hg5cWIJZMVLW5xFUJFiJlluNfg83gzASSbt3ZmRsjk/aXguNk6JGqnfpJ3GHbNITHZM9M+4Nj7KjLsN6L48npAvIxYe+Qfbpt9RFSAStwLYEFuWI3mdllHgzZ/O4OiMEElQ9IOP+tSwKOf3rb9mVH3GRL2AXuAv7gY5YPn2IP/4IxW45XDQIGkauJ7eoq+OzpU7RIfLUV7chRH6sBbJuNGBHnZrzeN0U/XoSoBjGXwOhFO/a/YED8cqhqTjA7TJEGvdWcDpP/PhtcoQ11LiCmiNbimN0/loxgVo/YCZoHJzt5vxV2U9Yp4xkHa93xUCMo5Fj2N/mEgbPUMqnBTQPE/Rk/Pn2+Uj4goESGaNLWCQQVAnabnkvrp3aVuxQNmU+uIEFVz5WYfXM1wB9g2P3jMe9xwvls6MCRBznbNOv6PZd9K2o06u/G1H2MI192WgcUIrXw+/+IdbxNFeaelQz+wwgG6z5i5f3I47pfwYUGPpT8a0oFtm4fC2U2k7fgcN/hPiCH/ZyJlWJdR+9CGoZ2NYmsmJ8Ty8FEjGXSLpaJeWR2LMBQR3CiZYPSwc3cDw4aQ0sZf1tV020zip1P7m1BR+eU7V2O0dvAORP8MUaIRAwVA/6dBHXMf3ffguEmGWB/QoBoHvgh9GRC9KU7nOs9uB1/2vQZd7o3HIKeouKS5XCNNmDfl2SAJNrghs/7xrl7AS+rpEM/KVP+qSqy+LgVujuDettNjAia4X7VbdqqAcBKBp83ftlEqklDSEzvPGRJEkvDXGAelZnNG+FSX5l7N6XwjLqjSL9bUg8dD3ibdX7OnQTXnyJYLwRIMS7MAuKCx5L2PJsufe3QmX8PB6qegAALP/Tq3LbrRmZptBg7+spuI6mWlHKGTdcUiyvLwzfKySqd66dOJETaPFRAkZv9xk7LNV7wZzwcn1P/dQ7dP+B4QV0+VMFrENhzcN60ocpvX0il7+YpSE+5w20R9XUqTDwbT0Z366lnMwMvI+i4axRWFXqnSkG9WpSROMYM9EjNtVtfuHyMoKhP8LX8Y5obdcxQ55V9v2qRJkSmbEX4RfBoZRgWFZWUnw6Xtyxpxk8as2YPldyBv0Tnmgq9fW0mOVVuX2WIZYTX2+pNGY95inEqEZBcmd59RUgpsa1asVU/nWQ0gJfBNJE1FIRjymMf2wlmkQCMCVe3uhKwD8RYeFW4sEqrenHZD81dCDRBC665wB5Hpv/cmJYKWsFia7FhKPnzTCcFXoWI89PNEf4+Uh5wkfBOXlO9UkH+zc0TwfjBoDAxBkGWjI1BqGzClKRElHD/xMdSkmAlNlHP07igromajkLXbQRopIcyqLDKX3NdAMamWto/OoeaQZu8HrY4fkIprzlAd4ne7Y/9B+y6HH+BWJKrZmiDL0rzqdyucB4MsOHLbiJVvvAtUPFb/7aa4xia5C+SY1H6URSmjmZRjNXSaBmmdLfM/Soz6sjRDHZn2C8e0990zGsh2M6V1TyY+xCvymrRC2i9zn180Hs5iUpD7h/wmgKg52XYl9JJ2oSxTb+nHWkNvvaPYdBdhI8jledOeJ2DPXPDQQU0XXEcVD4OZBOjh5gu+Vlzr5N/jEjhGYSE/dqvoxIqOLIVejP2dfU7eQwuk2fALfTKk3LIfnwA6Yskas3M3jsORUuyqoFD9RSYoKXTZ7r80rQyilE/73b+awwvIPNnn3Toq+7BrJPhBIZzFwm+NFDFY40u6f9AdI3p5Q4V/ytyf3WxQcYiwQCZLKkRKqEgsY2Y64snlgYmRHaW0vSHagR0jU2Mcx5gYgDAJj2/Qa1VxAQsLdf1oMA/waPBdhahIfwu8mxW8h9wsd243+43y/5VGj0xz/j/8X87k9b2CXPjfPredSDJ/C9g0+peYPs8wMBDHpZxvcv2BAQqM5t/p3jzYOGh2oSZQ0DQDOWQFG4TzYNggD2KtB7dfZ6tdfakECmGzAEk+yjIUFpYPnCGBZ7G3Vts5LFxUIglnuv0o0dKuEEMoHx8SqgdresbBbN6wnkF05neelBbO73eJdraSnPU/NWrbG2112EGi8cwDdrY4Oki763x3+Js9jagjKRSnEmilw1ESieucdTWBvEHekX11KJKmw1fniB9ozTKpoQvPZN/1LmXehq6hpsHccOJABbhDLgMneV3CLCNHDJfPJxo4ysWdx6nHFp2P+3XOI4pPJikt9VJVQRzBeU6rV//d/42IfW+3gQD280lT98uixvRIGxdmQaOGeHdEoh6GLpNeMrju2pukGiS1NXmV1lCjgiDDRUdOKEHPsyzulzN/9Z8gwTzYLHfXaCKi8NqlZgndfGUOpasxcyJM7symbilYW415gNqAlx2tSQkGMCGPGMSbGiD3/KOtfGMmoNViNzffK5ZoIVVKWwruFbP5bYmsntJE+UCKk3H3qYHhjYVQh2KWLiY5uYyIrSCZzk9tb2wzX30DHLOtW66dVGwEOKg2O2YcvSY9HLv55JKAdgBuHTZZvCZM/IUmXGycyMzFG66XThVYMELfZytVns0Xar/lv0PQFoVvQ2Tc/lsIrYt4sv/XqYi+/Bhxfv151wSjo44VyV2haZjveHowp78mPWYUrmc4oSrfq2zp7GiiTCiMNYc+fOTCTm5PPT/G3dTh8HmemB+ucJvcSrqk6XRCYrXzK7WqV/ZiZHk7zJg32XFf9kfv1SvoEFAH70ftnBfzHuENLDCTggMPPjw+vKqRgRoH5aGSjG8BAOIihOEWrUFB1hDma1UKIYHw0xUmV3DeDhYaxAEuR5R5Pris9Ksfy0jD8Xf9kRkB7aYp7Bgz74hMW0Icx0WCBQSiuYseBMmLBsT3l2ln27aXPsBBCi6maPu2SY3Io73c9BnpYlfid1TXEis+S0d2eowpm4s6NqeIQSkL8evyW+42u/v1GeoXALFhSQNcN9fJTeayYQ+8UrHT3rqCtjs3dL60b5D8TgSruJ3/k5JbR/w65w24cusLH2YWpwW4tc/wN3IFhS1Li2e8GJRoqU5YFiLoCyzCe9jbS//5e+9bpN1jmA+qh7Q7bvDmhpfA7ZNRuSLvJgfor/HHCUVGWYtLpA/Cz9/NkdsRRQ+uxR+FVpXQki0CL05PTPS44XV7x0ZY6VsagoqCxNUYyGzEA6BQjvBPLsJoBlcei3MdjtaPgw0LchOdNHLgYfNs7WleITjQoFK0gEAFkkRAwHiaR7Q3/A7HuqGstDjg+G4V+0HFaAdEafZuUCy6j2oZzCu9uK5dRgT9CUwbG1Gl0rC4al8aYHKjvdP0tI/5eUFmM/xgwe/doC4xXmvVgHOzmSsOH7zpJ+RtWqb+O0kyTq79pMefUOaRhpcVZxA0kjSKF+kPXpGTY5/AKetjcLvz7Afn///n5Zfsd0xh8aJvog8Z0x1l8ZUneUDmFiH2/Q6pPx37WEGkr7TBw2vQjfSumyWjhHOVnaQO86bgdZ5SA8pmrZmDqmu8bXnEbOArwyUI96Y9waTUdIZ1SAWMxmn6rnzpu0px1MWjqWPWSfCPqE8nNWsrLQ9333vqHSFP+hSQOhoGt5xXe/2BTTithQoaWg43WKvVIs6hfxmCUvq0N+g6Vayw80V0waQ2W9XOFpXyZRytKjgbhUxU9UtCj7cP712kXK6UbZEbcoJzyMRsmT/Z0dC7c1BGaJmL81lJaVdAhd1qkfhKvw8bwRnlrhPiS989CCso2rAKk4eB41KVnkPzqzfxf6z0jyfhw3LvOOs+AhmJp9Dcop0TauqtKGT6A92VHrEizKOva/h/riww3gVYiJ88rlqQ1DVZztL8LZV3E+AhTqBA/i1L5+H71ZJ1IH0lIU5XpxLtifBU+mYjt9nN+J3BQ1EkL1FjPTv0ZlZ6QEniEXxfLNixZjq5oc0fEL0+Kp4z73M3Wa
*/