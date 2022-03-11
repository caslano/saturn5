//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_18.hpp
kdHz3eS7CkHy+2LhJmav8X5qfoMOsijbhdkygOekcZ5/cJbkRCCRUBexgITg9R3dMI0btby/T+YeuxT8+OS6i2l6XfK14k4d+mURntonrljAYCDfzSEr7LjV+fpgjvOH9ecxuy/zjdye92020WEvE4vBRiRjQ8yJl6Pin24NCX4cLY7VSDwkVtn3o79rKa3tT+JRznFXBbN7n1ZS1xQyNMYpgYSOUZIyBGx6f7C+nU49WgwM/eR20Y4VI1trJnwSN2R/IX+yXzGG/84Cdkk4B4c9vT1JpUzb5Ovo6TUwmJDkr2ZTsZaiTMFztakIiwPTAIKQQSjuf8DdHESGzUUBEdrLrwXrBCARCiUd/WgEwYS8jyd0mBgYUwwdArUf6Br4vLh4ye+bqMosW27YxgzUKltehC2zlnwjn+OSV913F1jdU6cFCyHLBilA4ZYrRPB5hlsbu2aC6mu06C5pRsWQGTMER6/rATOFNcaLErsJVBf+ELqwUGZ0HNZhzsS+4aofB7UgpMmKyzCT39O2Hjz3DKdjXOqTZZWCRoV8MTr4qQVVGrxIUBIC4Eag/y2D0xG9XztjcjCchZfV75UBPfkpP1VAEjulqSLbt69ek9WWarZvCvYMxihG7vXQrOVdx4D/oaId96pgORB9PksWmED5EOlOSV4Z8IVldBJkK2C1TdBNDezWxW9wLnFEtERYJuxal/l9UkCEUsKzPx799R4c/OJoFii2xibLo8fQ43auIt4ELpsQflgbApke2UzGIe/fLmQGZDqZSzE9KxnnWwlBJsgn3CyWBl3T+wE8WKynv+mrcSRc5grESIdTvywprj578eQMoVV7HjFBWHlf7v1Ft3dSVpFf9OHZNheuM34lRQeAAIBDSwEAgP9/zqfKbvfwbYqYcV1KgMXM2kz4DD8xMDQ9aQ2G9Ip73zirbGWK7I4RqowM2Gpm4ZbtOo9r0whhbGJLlbomtvpE10N0IFgQQNHY7Nju2LZt27Zt2+rYtm3btm17spvF/afW9Rfv1AWKu4aKrj945Ynl8Km84MlZdcB01Sw47/v2GOWdEF5F9FzFuLgDX2hJjIDcfZYLM1ApfUiK0Ml7JrqNF0u37B2vShOev3ON3VP03rvsvrh9Jb6dbHMiVcI6pvY/jF3Z3Eo2gaxdSui0zVMJreaGQqArqOoXmoZ78aJpLCTx7f2zhsm6v1ib6ZlshvmC9QaYl0hAJf9ClOTv9eRl72KRamRE5UgE/QbNvE8x8FkMVm0JfIssrjtsST57KUerz+NrIfD1jEH/sLh9jDcLvdQbVIha+DQnKnK9WFzoaB+BvIUoaXrTxEz6LIxAkhEzXPspQPuHe0FU5iU95YSqWx01fllwRf5x5F4RDD6jtjRdy1aE52zA58zdXTN5x14LEZavr5zjwkQ4veAdN+R33I7wCZ8Tibj881RibwsU0ScX6qWVaVvgKjZPD2DylADxF1rr5q/tjnqslHl8DJcnY138RZeIVqwnIR4OJXiW6vIBO5Y7AVHVFQSDjPxk1KS0dy485c1e+vBNISiX63hOp/n2ep29aizwdJ6e3XWS/pEUiVdEsPOf3IJJo866+L+DkKE1QsP4TOE96kLiEUQKjOUXrG7WgGEGPe+PkG1l+5nh3mkmxajVHRUlCFVmU4KnHYhHTQOEANl4AX4265vWyG25VuNdXpDWozRo5XhwJ54CKl0LNzdAeqmqtCrqHoEU+kfAR+stLhaKmsWusKoSeGhdxMql3E4x39N359+mH9dGsPRWJLGfmu0krTpztxlpb7KqFzfjbe7XH4ZczoHYHfW4tcoc6ydV6udkQU/bDkFm16k5R9l+8ZhG0LPa0xdKOAF5jhO3Q1xQ0Hewn1i4AuBvPURABSWECl203sF92YkuwvNhQj1BFMPkiJIY2k8PvsBBIz11ItTiAe/Im/IJZUDE3HgZwKVMdL67bpi8/uCO+5o0ReiIu3is1YIk/84Nl666BBUM7JAWhIUv+aL8A1wMFv1Wh+H8+icJBOtEgjwaMAhAwlMVPM9syIWRya7AQmHieuCE9Uv0XggVA7HrsE16uNLhvi5/LhrBcMu4p5ux7lkoq5oSSIMDczqHfH1uqf40ltI0sHOBKDBtrsKuzs0Axfd+Wss9l5k02ZvWlLvRGY5FgMyWbeUsX9dcHuncvXq/HS+Dda+f6DbAhEYHy/h0qVGK9k8ke6C5fhZutOxV1JWZvVq+a+TLpmjsPaTUUwc+1z6GyvHXcFmi+L+guzAyeAiXMpqsQFB9RGt26tsyxbJTZHE9T75aOsPthHk9D/DGtpRMb1PgyAwhH1XoNHCZpbgScVY2w1F3/Dyin/xBsCbIK63p5gXzz1vDAuLsRpZEuzW+9ON4clubPn68CF17TVSPJaKtczDnypr3wutm5E5dsruf45S8ZXozQclEWqaE8QLvVhkxLhzGwq3Mv4YzPbnaG+zV3lwNw39E5Tn/BpAkhGWA50ElY68Z5uuFOjSTq4XG42v2klEBsgcHvcFl9g2NXYm6GsDqoo5KkXPjPDhJNXG81by0uCveceHuUv/Lo81T0ZnZAAFyNtHA6I3JAsOgFOfidPNyGNYk+AxuqT5eHp8hfQ0BGva1RbfMWTd/M40BgQ5BnxDUOp4Be7FxbwMFh8U27v46WAiPROQXHH6GKCxW7VnYHS9mV522/BGEvj7N8+Ar0AH/z99ehZqOLA2GXlv1PZ1cZAMYo8QXdG56T0H1heY4ljEhv+YYb7JgSoGqmH6TIf6Ug2poNshPr/xDqMV1fT+iOHkj/qKOBe8SFxj/E1H+I5qYJo9O3IEbi4F0PbFuZqDl31wIGd2EWnNSGLJCbjofoDS95Ssqrax3KlIEiTI+QXkWtETWh7O+5vTGR1Dx0OqTGdkW0PMD8fPegeEc7+3N/KManCkeSEuErb8bvgprRSv/CgCcvA6qFEevFVb8Yyc04in1xd3zYuxHp1mD94qxkPZo4VI8pUEUuL7PGiLVVwh0dXNZTWFZfPDOELzTH5GkMAQIAhiB148qTN0fmevdwoLKN+qHx3d66K9noUcYK3n7sFhiRve/qMymaLgV5+fk1Z1ozENxebfphr3iTCjB52eOBvIS/p+R35EbcYmA4doyUyLbxUHyLbaLlw8/xi+dVD3xRtHXNwxf3nZCmaHrgZjxoo5ufosCj9EQyBAwkDUTJ8NOfybvXavgUA5jafxP/em20Yhk1Azoe2uj/I3/dHUqeb5+GzfDEfmT5Ua/IFC8dIBSxqKJ4Tfxu4YOHYm6FivhfD4q9yFp9Ly4Xd2CMfZPnXgseJSj4fqMeGt78GUtBh7V1IFDK4JxOImytVlmtlHVkcWVrQ11JO2YKb1XpV0aMFwYbTzHVS1vxqX4gdFVr+Jq9TCR5mbdvmqDDka5tAFz0hbVIuWhmVWvGqxkZFh48D9gmA4TjwSpVsmeJ3bx+V1pbarR/8skHzxZ+fE50vfglW1v5tv/6xOT9XYm5aJmc0xKGV4q3+WUZDsBcBiOY4vInqpes41Rup41B5A8drBmbDDOuYTvEpLZPdWQasLlphGy05UTmqYgSU1QnyoHO5NBdSeg32EvljAj+Fz4colMRX4boDKpgJ1xLRJ/ALEgY1y3Op4m/fStwM4Ep5xutz7qACqtJkEXp0uaVZ8WdbKbOliByozEUoP0GZio/uWI1zduk4A7fky+cq3huT9Ft7UNvsHsTaTRWbEodgAcS10ublL8VH5d2wQg2q2wbPisbspARRPPQdM+rGcqXk23MlPdqX1ywv7aHvx5UQ438yJNBdLT67PMW169eLut6mgkwu4xZuFuicbA3oEgVQeCa4EOVzeRkFQjtodGM3Nxeujo+oOFzaw6NijVCYY95ey1aLNZQ1Gr6BXsHyBLYisVcmUY4SOUT9bupvWTXMBaDs7o0eMpktFtxsHcop6JP1Nn58WAVSE3HoniPG+z4is5/TFy56q50LAWLu3w4GlcsN8qQupqitDoIktEOkaI+500QaPFI1v9fA5qa0gGPhDZZKWbVhLqYd6hCxRSUUVV0jEqU7fDcr0Fa/Z99jDMqMMr0lKpSLca53rIZDJhAgLn6CFnbDRxMz204sy0eU59S4l0zXqo7IPqj5zP8vCJzBASRhIwkI2TKEyXM1BqyNFN3g52kX/SUBJMVQp99UDhrmcg4FZBGkWPRhU/KU+Sb/IYdPHT93NDcmsiQi2GiINy1ztxOvaEox0j+fm4frfrGUDnVgGRfm1+OZLi7f2+zQmNR2Kgg7LEUbyJ5xsTzUZPeuuyldaukf0kE+OfrahnaJIdapLasxa7Ans5A64mZyREOHqD+Q1X+KA6RJq+jaHaqxje/mYftxeRdzN/AyNdCBjLA2JrFhLR+ARTQlBPHCURxc4tm4V+y721YNCEkAmTUt5rOCwTt+3l6B51pmL+Iuw8Fk8laK3pUMti9FA4ZtGZehtMHTvUtMzMfjKwdZ1zNcr5c21wpkkeSJ9DEAEL3lxWMmKQOjHwUsW8b8EbMv3z4agzAKiM4azTlZurCljlywOVpS+/VkABNTwYw8oUJqAk6tNpMcz0vMwAOcY1kbcPB4sqGa8gruD9Y09wGmtUNLxxJadRGo57+PLClXpxXlnNlokrnweFUDnD4n2IOsbS413osfqBCjM7iLRyosFRvrUvcTIF580ShW0tWRISOBy6w/jlslHqFkh49OVkJ8palTjp0yanzj62Kr4eI7sQAulJeLOaItPXa2Q+gpvJxOkWPWZTykr+1xA7PI7OZzbqIxZLHp3QkfC9gcACAY/0n6CNTuLySFUBa386rA+2uvhNrZ6CcGCKV6HJAjnc1qNV5MU4+eprwwe4fAx3fhdRcXyfsETtt+Mq0MSFuk1CqZeEsWlTOb/3VGcakoUvvC1hTkJ/APGCW4+nb+UGxrjjdpY8oqAY25BUZlVCGMr32B916MbOcYiTSNC4zBB8a4GCZd+C+CVYR+TnvnwYmrm+Hg308kNqmbs6mDPcrmcwtX+V51Nmw16Pazzw0qb2q82QTWTCQ+Iow+RhnEo4M9tj0HedLNTWRsMfalxvADPODzG0SHZRanvdiQeH66QfR1Zu/pObnvOlnpHrrjoRqOPo7JOZP0Pa3sf6vGQv6nbY5tfm75XsClJTHsIBNdUDbEWWC8HdWd9siOWk4m4eHD2hRaLiA+OY6vQysRsj6z5nObKfKA2+hHy0Cx/kkjr+dS32hBNqvlOe9oS2445P3xWV6th/KHdf9arpX4Kfs3jf2RTuSLSVawKMUKn1N/XQZz8sUwUus9dsMyRN+owvevBP33HOpbWqM9A7L1FaH1m4l7/Hg6CzupM2jKOg6+PUYoSHBWvXYWpQ6oGeRLX5hxL6F1g+BMPlptRsGAPN8I2wxP88sV2i8Y/94+DZRc2CwE3q9hjFDYqdjnlPVQ02JiW6TNIPx7QGKYuvi//CKWXIo9JM3ptTVo6b0/fYjX8pQytEP3TvK8weVRYV+G3Hgfw0bAwFkFWbJT6y0kzDwo55OOIitRBnnAYF857va/+MGLSuPrKOvD8j091l5OTO1x22HyLZlc6KhhbJJ2dTVSIRKahjt9E/7ozvS2gl3Y2fXR9MfVq20+6GVz/2SEVpjtCglepAdPX8AuqMfywruMZhPAeyBSDlVfl3/tveF7ZYivwmTmI7JiG5nCuPevTuwwXDJdTOHbjtHuBHwP0qniSY4bv2NhlruL6+8XhfBfQAHeRU8bX+Mu+hYiuu+wh8xtyoVt1PFylkDcBMgVG5HcEJiRYgXkNlD9xON2lNvWf5+NSql6sFEq6Z5y07jrJMB/+evOjnDtAhjHBY0OPHtdGSCFGHvEdQFoNlriRM/fPGZUnRcP5ZINHcn+6nykyuimo8ZuZzBHe/KYsRDC44yAy+X8vfp8ZHNcacymKc5Si9YfhRUy392Lv0wpR21Z1JmkRs632KZ+QHqnpUt0UWQPIYIt6aSIgiAWNd6PIYJg1sfxj/HE1p5oWYZ9zD2Obcx7iSH0Sc1ojYYNXVeEcuKEip9gVbGTwopr0LeayareW932UTpK0uIbfY8u/JbH/kiM3nt54tT2qgjl525QE9AkQNXryrJ9DJcdAW0rosrYGiSj7QGXd7hw49wlqKvi5m06gN2lUUF0GGQjnVgaDyIsfu1PbY3uTaacKxwefilnl0L0ELOeKxLpH/wX+An1FdIdmzly6G+5e+JkSzGwJ+KNGJ845ze/CgQyjMTV4crIJOSvFKEdRuRC8AYCVHzen+HIJuSiA8w9sBu+/ufkPUoI00bBCuxnu5Y/px+akl59Sqdz9ZiZe9r6Mt85b7vlG2NRWezP62im0s3ffnuk6U1RV9MK1ls/RvNnG3uCZLt/6bnAT8XL9zhfXc0yB1Akxb6qNnVNIRcKKUk4FaqRzKjXsz7WAeD+mLjaMd8emgWh3Iaoo3OlXEWdVivirOv/Q/Vb7n71nNh74KjWXkymmbIegGexuaII6oAiloDssdh7TLOSNenZd06hkLiH/NhLxft997sXTKfxheUbMi++MMer8yDLBlG8zv824WzoSU3T1ZZPCQ7PqiJCScwj32psQNCElVvAWNfJDw0Ke19yLbeJF9p+eVllQfulYozOT4PevYdqSZBQOPIymHzjvogUauYY4KbpUZTeTZjwK1NZMVPbnJsNq9GoHY9hKFIz3n0ezXrs773ZnsSQSG1XSRvAzU9Rkp2wOEBYlfAU+dZnxr+CRQYNDCPWSEwdnzsNMbzvqLAZvBIwE/Dzt5geqB97unSfsUwSo6n7bshJSo8pXpyT7vkX967eLMWEDp4oaHzqprtqhQN+m8HvaRZrSYchoFYr9s2klTj99sdtf+GGxAhHVmYRTyJJ8nMiMljGjHMm+F6abTgYs3wEFAAvb6dPxsZNmj/ABGa2qo+qvveixb0aBKLEhK2QObr6OYji8hu/3b5DtBos3qMdM/PAa1e+ndriFIhtP6Y/2MbpuvvszSBvy5OY31mbDuVHtvqKPQ+iTDVaGoVxGYvhB5CYJma1deshGgYdxVnr4FBi+ZrMhbk4DE61hCE2Xsp8flYnINVQZp/uE9UDID7LNcbyACovhQHrWvkcNSV4iMOhKIaBUKeMdP9cREG5jAXz1Q14rqlc3DdL8YY54MFQzqI02gfoP2wd8GjWcfrzzbaxomhsJOyLb1Eh6SDnL0k+Ne+SLpCDcyIV7vfbj8RamfgtlEwuhF2wbrs1gtWIO47Kv899F5a/4K1PV6bLeYjJGj680Zh0NQ1bzYWJimJ6gt3wQJAWJTPLOLgf0Wgm0UIm6gvlr8XkcNJ/7pOETnK9mnlh9S2qEGmrLQ1WcDDKi5g9v/J11N1cGb5m/w8p5m7zX+a+RfrBet7UEpGOq96gsbUoAG6wqaVaxXyTp374bg+jOiBQm1cPqsDXAZ6U+RuAJcpBwcaedjHWpgDrAv6J51GvddmlB+cXjhP2NlOgbhkRrBKJMq6Eo9/bVUG+zTm6G0IWpy0HIcHMdUteUwzywCOt1iNNtIPzAfgAbCeOMHmdvi/Tat3qzYC6hxRcyqT6UIeILdBuaFvMrBWzeaxRBr+6u4SnPXhmu0yqNUrOemhC6Enn7tMW03ahHz0wP0FuKO9+TdqCHiuGdI2FqwkpY0wmq5uLcRWSajphaOl4+94M17GdwGuLaRZcnr6j6WdFebHwTgYuX3U4BCTgbbuGFsSSKRfc65qjTFIu43Ls3gFcorHteUCOQkSEU+jFLjbFN1ySn36BiB/U20eaz9BUfWXelw86yd10zfYwHPd6Yn+h8CuCDJOEierDc5PfSW8m8AaygZ8CyAzKCFWezijbb0uADw1kHwrtPMAVzSrX/L/aFhsFJJ1y6hvEYv10NrrnZccgJ9GBpCO/FlloIJSNw/UFxmQWJ99seggN1xqQ8TEUMBz4QPLukHuQOYcrTe9BDAm6K4S4G3BnGXvyBw1RmewnAdg+MO/K0BpDYCORbRdhRjUlrNiKzv7SGoyEIIOESG/p3A76/HVyJcZsabqMVq7oy+mxyCen2eaJX05i9oK+KVbH36M7S55MVAm1DMBWMe6ueVxn+K6fUy94F1uJ5KAephr7LQf+aNT+4Cy3cbFbmHcaBhIk8SxTX4w0AvKBhvLKCnQDa3IYr/LAzLNKxUJLuLJ7Bt100N5Q5VKnUwQSqVJnxFAE7eL3XJZYPcYlF0EEkMfjltLmUjL9E7b8ivGmpBSdbDWf4BJymMAKoazxeF9yVxwOQ+vw6EbtMSQXST95sPGoflMJ1yEMUpbdCHVvqYdJz99xk3sbnzCGCrnoKQcXFhebr97uLL27PNO1rUC7D1G+SryBAepLfMAzd/fNYbU4wkpe75IR9YhoJ3P2686JV/VXZU58sHf1KEsK3l9e6GP9OUQO6w+slRzygfERodDsnoNyo0ZqYdISuxaN9yIvb56LJV4EHkQFhMFtFH/xEuQs2b7nLjH9dZta8W5ydJhqCZjndwBTdCS7AZKWkC/hjEkfSCd6v78kI8Wktr14q8xfXRokSj1AzBvaH8iTQHA7IpTHG7U127N+bkRRBjh9qcaQUuUI8/xUED31ZdBUayHwJFYwdVTGrQApP3ibkPhH9boNOZH47Vm0lYAEoG0dp93KlWxOpd6q+84QTKD8n1sXjPyk27iQi6ldt/gBTVc4mSX4W4ujy0YQj9SQRetLqEZp1yfn+fful0XW1UmF8HyfcJP/mX0gIsoxBmlKBxYOeZ4ngR9+pGoe4vfSio5Pw3meIyQVONf8ywDth48w64SDCKlorVIHgNiIzFMpiq2dYy7bfb/X3mTt0SNoT5h7GCxBGVtJtUg0PGYaUl5UUrKZ4vOPqIO9olJB5g6Yzv1eIhZQUASBi7uweoYhczq695WvUASeZaqMhqM1B/ilIxNfMXhweYQDxsOddfEwL9Zp5ywgjkokxdVGgYVV+8YfcRNSden0Y3ZGxR1RySJLuO0uF1FnbjjwCK+CBdFpIUDZeO38DC+qT7wwP3yDEFETK1qp9i5NOZHZzo3Sh01tYpLnCVVlC1vB7VS9i7L8MTtzc5ghYsVwwKRlz86hLwuRZybulj5v3haY0sECgYo/jggnn1cKaYoVUSN/C6kDgVaFETCXVs4J9bkS/QIeKezGQ/MKNjF9Yf8sBlHFWbGBE=
*/