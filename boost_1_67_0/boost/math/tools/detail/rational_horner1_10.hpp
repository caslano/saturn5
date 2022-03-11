//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_10_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_10_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_10.hpp
4w6AYcif+VeyLn8T2JjN3pOQe1XJwQ1VwH3sbmYi0EsslZJWMm5tG5uUaA5k0SXWOKbG1B2ClUW2L8gdhvM/Gj4jQZHCXt32KNYvOlPev3QBH0F8kantFCs5Xty96lei/Vtb/TXPtvXD3yfAQFgBRnBNV7GSnTli6lWeo/WSIuGyD36jVADUhjblt98QTjFe7UHLGEtPLFSaGFf/Jang1eqZsmwtyCkWFo9ZzAdofmM5ssH2j+6eEGQ1tyHyIMijdSzH2712nKC+oMnODov9T79/7L3hyebZxKPhtfAjvmsO7D3DX2nbakAI3gswRQ25qSjBMZUWMrxr5SAvzP6USVl0oZaNLjplj+OxlzL131CPkW4r3dAku8Vm29OwYfrRyFt45GrE6bVsZ9LNtmcrXxN/GgucJqptvCPpGmqA9WGyyry5ULyu6+1+CaMQXy8lkt54dmbcjFVbwUtui/V5Yo0Xna1X0aia00Xb9EoRLNPNeJgQq/KHZLArnaDSBkJYseII4yeQhzuReNKClHoROjT3iqd8nMkgIuwyQKiXjS30v3bvhfrebz7RAAw1HznbDHp0PVPyBjOyXtaSNoZAJjoZZbUGWxpvqa1J9y1oecRYwl/74tCP+gFnp1ITBBLInHqSyO7sDiv3/Uec8+FEK5oAgRkctZ6gw046NNlNjzrkWmjPmAVauOrIicK2w4HHLMVJrjk91mSCRh0OFl4LJdE0ag5+DV20VUae8Jw89yJGoFUdmktYrICgT+oAfC5H4a7V+NX1a/ZRIclyksNrAqxSotXacoXw2EJUZSGMasKCmfciInMqQvhWZbMfTEQtSdBq4US5Dm35/R94bgvK7d+NI/7R7wXK2CLHwo/p+xy+PksJMZTEbrjL4GRZJ4HqOyXUjYVRttekIxCwvN/l25mvyBpgaHCYKAeWllZ9wwy2aa0SjUCU4LDNzR0OgoOVmLR+Rz/QANt1r6FOybrXFMgGDK6pGwX9tVBnzr36twzjWx8jAxAoZiHTxNrClG21r/nwO13QSs8Lt7Lp++eCst6lUxGAFl8Bna2lLuIE2ZcAinKZTIOBZU+ZpLdZxQMTSxlkPW82Re/RIoreH+GJlTZjWB9P4/82p8Pj39c5rjjkzt9t4ZyR1igDEvhqOKMlEhE36OZFe+P76q6lrB0PjsS+WBn8U2MpmuNfy+z6e64VNNGrMauVIFPrnJultArzQUJJnGTYTz2SwEaNVsbvuhFi5aJpFgk72xL2dgmPrY8/ECQ0m3DnXefG1QqfJubR3UvjS9nmaDceASogbNofj26WOV4q5Ph1cpd2XpMvsznO/VO/gcLfs00EWuU96qk7inmPD5kgk3V4ntVfXgK9/JcqcfR+JljebI+KMtZJXCL/84R/3ONvY/vSN4F8osV8GcUGOLH/oAzdY8eyF5jwVAybE0fC6YNRF/A9F+tgbI8kjuYCXf4CwUaMq9EcamndRQay7ju9zWQqi0ksVfAvamz1NHYxiF1b22mWoVMEtbU/C3pchVbWJ6I4kQQco1Hl/vfd2YlwPbOSGuAzT+cjyucIshdcbT6iSS+Yqh1uodk08XGmjsArgFbeFf0QBryzuftLmVUvf+m7aHma0X3uOrfQrvtD8iRRreBgi8+q5gF67UCbt9mTfcYYigDX1i0FAp3EWHVNfi+Z+fJauyxjNcweG6AyG+EKvntgD5vlsB5DVbYljgi8mUPuU+Teszsf1ZDFVpMKtjOPUtJpqhqp3bxK7bLb33HYLK7+wpp+b7zPM+SkuPJEQuey7q43ghTrYqs0JxmRdwMQNn265qLhfBBgvpwhk8tc1ghA+dPlf94828kEydMOmYHOdBwE+89Z6OmMEXdWbyPm7Xxmt9AReVSorxs/mBUDaQhR0GnlnUS62OZZuatKoTjjJasPA8OLmvKLHD2CHsb4/GkT4tIBQiF1dsAf90NMcSAnTYosrEhEhW4R+JDI3WUll0TYD+K8tPVy6G4plDaZO2SJ6FuZ8vVqVUaC1xUrUmcZHaefCHeYiXmrI7sXWIumxnaKFuwqxJkJRQcCu0Yj8b0BDGOrtJoJ5PZcNoX0sk2oRvfo+TnAzO6eTR82PlHRTYtyH7rb1zDY/h/XOiynaT16WcWH1jzB2FN2/WYMGgpkOs1AnH6I1IpVAnAMBEJjMcPcZzkBxyvFoWK0iIPIchpfZCJDcBA33gb/9CKFVtOhsKe1DC/eMuzXcn+oOgSyohDSyzDXdj+ZOFLnKZCrK2GXCo7rl5J4W3Zws0T5lGGk/eIvFP30qkIji5C9dHs/wdWHEnMAxz4Y/23MVlBVvbadFG8BeHJR/BHb2An7deMev5ebOtxoAexYqiWZSuMz2a6tlHWX2tJcjyCdIK/F1+b4jWoB7tY5imfs5Lj706g0+/raMnj3ifKee7W6FgMcB5YhwNh/3VZZa5rT3jiV0H52Mzdm6FOrx8WyyJMqbFeM4/m5CuVQN5Asa7GP5KPDx2CjC7bGHhKHWbidp7biV5OA8GYMN2WUB17et+dyId0+QQd5cuvNAUenKRUqKgV70VN3dTPlRDZqjdJ39M5NjGY+fW32lip2uGoIxKQt9VJKFUPI24O0SGXrsZQ1s/w7y/OWEXj4EMlekAJynxCjWJkGkIv+tOcQtGFt9I9RGzPtRmp52y4wObW2Nd0HQAMpPYUluD7HzxUybjuf4Ki5PsU81aT85ifcrQSwj83pKBYLqoWnOtjdPSFbvgJ8rGmF/2Eg3q/hHxxATTk5HYgEEJ3zEC94FWbqQl99MB5LdaJvMzz2kJZXzB1tSWClj+j0/ZI0LKCpj+53aHQzNwZTETrFipJRruTUH3plXVYPdcSHTdqO50kIUQU50ifpunmGEA/8e2wjxF5luPD97j3hUkcOzIhu02WnN6PBua8OzoUQ3xhE7npTwyQpgw7O16HuP4938zhTjqtjPUV++RSFyL7nm9/uRmNqcG9c7eHeq1Qgjqp02xObQfsophXz6iyujPuqdjtLdHE5fuATWEHMvelNt6qr9J+0IlcuS0OA1wB1T6W8f5fA+Vw+763c5hiHrBRLziV52PX6xOP77v+vt/usxSyH1Z7/qh9xpyPNZed05c3uFdrSkv/f9uTpg3juVKiZbAdXQBC4+KBKPLHIEfawuNH+sqGG3RaENYyp/iA6e9Q2UN5Y6XZUjQCC8QP7g2xA+gGDl7J+1GuZ7+QMG/l/Lj3QKdLPVzOTG9VBeDM93KKJjmzR7XO8Mn6asbOR6F4un+XBne2zBZW9nOMou75TCHwVHSGhiCCbhKXjZ3tfDdd+cmXrzrSeyW+PGLd8rzXuJCw9k2XZgc3zvLgOlm6konfrXJcmCzyviHIea2aHn1kPQJLgxeWe567KgU7Zq6IFOleXM16y1vSnQilsOP2JhtSCp/YZiwP6JzBG/55M57Gd7TPYn74q4LQMOJ5ea8bK1nXjYjfVafNDXxFe9ZlCl8pVKG/wq9kuqyj7LLtpvV87pKRYj+Y0bK+n8Het8mI+uRMXD65Tr2XXXwJhYPvUbve9LDaJvjOe2EqTYLI/0g12PD7TwZfMhEO+/S4VjIe1x/jCcg4QxjTNF4rBd8+8hNBmw9az30zu3sGQDKlL0dcTy6fYuIH9Q3nbD1L8rWAuN3WdYAJX3HYuTGixqFt9LmOLQPzkqTo9X90CD5X6WNa8ZlVHXA6h2aPXPrEjKqKGSzh7JvxI/xvi7jHQkN8WyNjVZtooz3zC3yaN5Yuqn2SC3vVxPgNrFPkpORFhnj/bRXAqaykzKmXh5M4KAtev1FDtnlXCw3Ldv76Fx1WJb8p9DGbONfRY4aq09jASowkYrdCv7upu1WWjAZvJKW++rLqAG0pzwWAkylpDvJq1vuBPKi8UfX7mX2e9cbvbqu/Pfz1WocRAXiusRQdL6NuejLDIvtyh5o+ViXHhsTTt9Dlx3cm0cFW4ljeQsSC/vg7o035kPF3dV+R5IDS+pxgAQnLjClWJ/e5qYa7m0lvR99pYx64yXbsO851qfSsHnVkJ0JY6po80TRP28+/tcUrJ/XfqU2MZ5To+faskJ0IWKcQxFNlS5NW4EKpjXEetvnC6VB2uLy3oXcq5VO2VJiR/dqOYFvN9H3cC9m+el/uRsEGI/u6fXq+QsA23Jn4jTvsZtfqlWy2dsTcLSr3GP08WGuse2iYAXRDXEvSBIqn5A35cThntTaledWHou5mvudPZENuLAN6VpX4yQUg4vA0/rCAAuK0XJXpEACrpGAOsvRa6FRyahESOeSyql0ZraxBLw4qI8KersOsVXzL+sSYxIsQh+Gc3AgrUBDe2mqvjbq2XIoTOijCMhSAs1GwyOKMgT21KmrPYj66GaqiJC0wzsv6Dv3ITgnkXlWsMDAkmsCofZdOwARRYDpEkaHA4n4pMJMgcarz8RcfTHm+obJelynYbdacn7KHSeDsgRDHBkkBokHCErNatKZwTpjVX/UIUiWsBkICiNarb3I2Gr6VGunIZzfGJuP3IAXGT02YFyC+xkEESLqz+fH72eHy4odwIwHLo3m75wQtjRtju2gaPg0MDUOYbp+hG8H5cXfuTlZIo47qTrVt/3MBnsqH+2JA6efbfxZpwPAOLcm1jD6eVv67nyYEPCk2yT0566yF5j7PNKq0OaNfTjKQhpC9ZAIHsRbP/JdmzokpehUZVNQ6zJBbhMNwwf+faNQ58AmLUiGZ9a+VgI3bFA24I1/OzzOrejeN34sLG5cDkqQOXujVuL+luHyrCbCI5tfxTRgdxajoAfACgCSAA0B/gPyB/QP+A/QH/A/EH8g/UH+g/MH9g/8D9gf+D8AfxD9If5D8of1D/oP1B/4PxB/MP1h/sPzh/cP/g/cH/Q/CH8A/RH+I/JH9I/5D9If9D8YfyD9Uf6j///tD8of1D94f+D8Mfxj9Mf5j/sPxh/cP2h/0Pxx/OP1x/uP/w/OH9w/eH/4/AH8E/Qn+E/4j8Ef0j9kf8j8QfyT9Sf6T/yPyR/SP3R/6Pwh/FP0p/lP+o/FH9o/ZH/Y/GH80/Wn+0/+j80f2j90f/j8Efwz9Gf4z/mPwx/WP2x/yPxR/LP1Z/rP/898fmj+0fuz/2fxz+OP5x+uP8x+WP6x+3P+5/PP54/vH64/3H54/vH/8/uuBo1UhWVX4XK5lkD42qhNVFlEopwVbq+NYmB6j28xyDLM/IA/JMGthyVX4fMulrCYD7+iw1ukmCuKmbF7cmhV6OuG9tNTHFT6lAkWznwFCLJXP6KdWYUufSbf0ZCxccIVKfjLtsnVV40OokOBdI33Y5eE8NajnUrvSKLTVyt6rOWTO7iwGzF40ByZr4fpWUAF4832uCiEsw5Ssrexs77xjhiTDQUqsS5pz7GTvIm721gnqt9S6pZwXqYmRWE0DLW1KYFCSB+zCDz/z0lhDHKhgBPX6MM8CzMLtG8zgM5jFSBBluxADJeiSDvOHl88ZOca4DryQ5zrKlRN6YYHt9+49UnCZ6NM4fr6VcpwAALP/THVuZaiQ6+zbB7ii2oeWV7mO1ig/W9IV7rcxZ32bi4CQgqKlXxMkT3um/lLsUEtKd2rGZwhOo3UBu34vpch5TDSzM3EjIrmkCa46PobxUVJigCIWtvqPF2/p7sRJJ58y1rRM/SWP1K+j6Sjr0DqLG3ArapJ1PyVsE3o8pSUDQwMyIHCd+ooERTzugKRuDsUBuvaj7Fa9NfCpmxZK2W1rRoAdcL5xyzpVqc56aB0PMadY5Mm8mbFf0xFqnX6Xtjg0XUstC3CoOYkVAakADbvfaSDUXFZDYPtbe5eiqLWuiyZUPpK9UP2mm0KZfqzjM4aVLsDmHM9QtbWffwm1oiykAK7A3pSYRsk2gHy/+LshXT/un/8miFfNH3O82rkwurIYnZQZ3GjHZqwwgPTTdLjhpGD0RA4uYa905Git+6OEZk4EB7S8tLETBezV77ejRqBla6ueVz/0uUB3tNrLtcdY9P5loXAqzLvNym23U2RJbatnpDqK6he+B+cLyhlzF83zvqj+XMLEiIKwYv73ketYbvn6d9l94//aqqZxuLeUljPI283G1J62jI2hgjlV+q2Xzkox5UCkcMG0yRuwt7Hb3aXd+UCsCEAYc6+juQW7+2gw+19hX5v3z8lUi/UwZ1O1tX+bf8ALU6rzfEV0baT8Wfgx8Iil529EUGvFe/RF71KvD8OepfSFNYrqkWZ5pKYLHLhjq6F7uvrnP/8nRvbU/P7qcLQNExjJNnOHTBBUMsWL8TwjMsaPPqEnkoxtqf9YBxc19vT7lLRUi6OChTPIL8A6ZYlEFgW4otreG+hA8eqK3V6MhSKoxdopFrpduyviUBpIPIJX9gwb1OJeaSQU80V3oWBF58TuITnE2v/Jumz2uT1YYvr8WsoYOv41SiGA/bd55Sfisd3uTlyLCpdV3K4SUiunuNkaJvWxgiYTC5fzC47dTYuQMxMCcnyNIqhM/5ZnwZCC8JtR6rrfooaO5yF7FlbXBTGGjih17rhBksxfJU2StvtlDLeTCaHNmkBBp16gfwcojE3No68jN7lunqKd7jO5+m7nfXM1X4h+3PwCwHWeikFhil4K7/Qk8WZ03DjD60fx54dyjr5j9jzhTGvd9me+B7NwKLqlu5jNyRkJ6MF+2Jkxd/6gmd6OfhYO2CK25auFbW6Jik1ZPwfW7pHt1HwTAeVLQ6CO4Yeji9POVfCxsdHpfxv2CMd2S25YFjwfaRZzlrOe0TMKJ52K3LnLtOqRDVchb+gtyTzV2i1XxFngx+A3izCaFwESa3Oi56czYvzzqH+TXy3WNtXFylLXr0Q4Op/ahzBnxfupceoS99Pj13maDDgUpYI7sNYgpx5/m8x7vYXn3w+Oc60MtD03z/PNEqSlGpN28UTytaiwJT01Bg+CfYwawuY2gw2wTLJ5eqs2S8616hecKbT08BhoXitO8SvFJ5/ui1lcmuqF4ym+yDFJP/iTILfC3Qr9bfyf/NHS3WA6tAQCdfKERpe/WF0i12kqtGwZUq5ev+cSU+RG82d5uufxgC9kvKK3qMX7hc/DoOh6NJTd6b0UVs4/1edM7+MrwRC7I72/cOtjebq9A6wTfrrc7HaeH0HzxCkbyXBNFPgWbw7VUdvVT/fv48Zt2o906x9aoFS1iV85xn04X2xMufLi1ypd3yuxcWEpLAB6+pTFrs26ezyRUVV8Xmm4WPb4u12dFkQ3VVXnyg0qTiETg86FPSuH00QfyK1pBz9wO4NWKKLOUISCzfMOqRx+nQ31DCy6Xu0ZoYfgVuf5mOiIC1Q9+mmFn0MfUgKN0aNeNubsxjlp6wSAVG6uY0UhvyjcCjG+qpw8LYFV6pTNqJ+veJY83V6aqau95iq7cgd62dRwY7Y/zh5DuYRpNBElE550zSksus+5V7s9dG4iIrmn8iZlTlgQbQv3k4j4yI+Y7q+j2Lxpvbz2JzmNgnYz5M76ilfVdA+5yrCu2x/fdCZdwQGXxj1C4wyayVz6WIJfPnl0yOatqC8ZBuHLwuNwci4XFxc5eM5a2HGzm8pEZ8/NG/+jhEGeumN7GNJmNjqL/Fqk5wKGboz72qk3s+Mp9LCzhD5q8fvcsxg2sqwL1m5qWjMmt8fMaHb4Dp1Mu3s0cjCah5kgu2cGNkaiK5RMCPqAo0OYoQOOCj9HRDJOIcahL5uoH04AOMkS4wX8Wv/5DHKV9fDcwxw7Swx/yF3bkdkE4FQO9p/f/p95mk+0C0B8UP5FzgGE7BxvC7lIAyCs8v/aIgFQDnw/BSKr+/U8xy+kcjCXuXrf7TUmUE4ypwYBPmvLfZ2pFv54h2E27mEwWy9eEHoxLdZNQt66pJU9avgKeUZMLhRAktIwAJygumodGRU8iTmlWyWSCoeCs0tV1aK2QnxszzG/yA24bfhfEAFWUXjtxBYmJsQPWDn06fKjqMStUGkqdOlAh6AAyQ1ngpbGFkq42jGVsT14JFfVNehw4btGjSRyMqJdg2DmFlrODDlWJ+m3vh4x0sR4lcPIEVvGzZAEXVGb67Boc2AGSfdXirx8CesHnm/3Ks0xAhDG+oYbOAkInkCmtf4ixkiKEwbFj8I6C+/bRD8bwAwGMc4Wio5zChT09SewL8HoNtGV1+5n4g15qvo0ma/hDLqBbrutnXpOQfLzvf9S4oXsO8Ivd146sDr1D2pAdMlxxrS84nbMT08oZl2vZPf477oAOW0VgVwuL/bWfpjJi5SefPT63hgheYZwHvfyHxdHvxiNDrIN7RCL23QKaCKbtKgqhnDXxMmOEbM1F1iZrKKmxIRm+vOpML47V6UyxnSOarS/pyFflWUO7slZpr+EYCtfDfAnKvbJRNjCNINnN58orZumKslFAnF5aN5MQM1O0FjaiNBKpaY23F7VMzodIW3O4UddN2nPuKRYdKNeNXHdP/4UqdAUfP94KugN+7FQ8zAgSTD9PEEr8Bw8C0VO3gU2TTGkMTsllmLPjvQxrkJitvfqeqW03RYyxhCcERRWST2wWZ/dcUXart3S+gOt5qo78bevTRsFCpQ5rQ7GqLMAC5ywTdxKt3Gv0rF3V2pExtRXIlwsavggqNepXr1LDdtTgJxtYE+csVSZdvKJRv7SvkN4ZyI5INvQA15FQLOg6IQxyZVSf5cN6PJ7pUPNfQCslt68763Y4x7cv+hWXX+lQMzSS8HozkI5Onolmpp/UbeyayMmv7wyeoZb1C6JJ9LAZtVSMkaEADOInbOM/FVTmIY5HNqyKMriQTli2AAfSMY0BDcYXwKCCeibHpxFdP9AJM0xGqVADTYzU97Y+ZhohanccUuDgAp9RFvOksQBDMXxlApAcaJZTwl0CkHn7eqbIQHxeH2biTvE6srp+uA3HKb0XLHLMRsm6uXN1M+PMyTjo1JTTFyOmx/uuS9reG4ZGs1dMQUz41w4nALs1wU4UMhV0NOpouebyO+oYXSi4n4o6RfAO+CwRCOWx4ZYQaZdA91FkegndVmkxzu1YafDqazfZ0e/9j+LEhtAODD1Dw22zKMiSRz8H++Z8VkBXXbUfjEkZaZ8+Ns19bixhmsmv5G+hOp2h9ct5xhm5afwevsQ25cYhQShg6u8xdU/S4GXgZAEYe9QDLB2v2rCTjYZc14LIX46v9UYnb6sNGWxfR9WMIrgQIzojkR0=
*/