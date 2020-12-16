//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_7.hpp
pTQ//04FD+zOYnr27xz4UpvqTY9Yt72Lp8e22lH7kkhjwD8DT9c3Bb5QFRLt53cDtDA8xTS++h6BBmdS3eh+BMeIhVMjvpArUc975tD39/Z7U5Itb7vnHL4jn6CM59X3GvM8K0zys3bzfv/7k7FXuXjJ74OAOdLvrzWm+97j6TnP5WNzeDa3L1zI7L7t9QPPZphlHe6tPf3I36Tazfv6BxwP9Igf8/zz3fcZf8AF84EbJVrQGrR39GE9cCytT8JI0LWUNV/3+jHiLR/r1id9b584DrLx4ilgvGDIVNY1DVFXPV54tSjYk+X3pxbIY5/kVu2ad2DcPNqPtNVrJ1pIjafFcvr8dSBt1xPzMvj5dT09lsE1RxdOb00ue76c58XXz3m2JmGv/OB0GLMTz+YNIE/Qcdqry/vaW57IeIIRvpXk9FfcOKd7BTt+gZnR/3rTEX3/OYGe5tWQvuvn11kaX3TzQJ9XbDCfPx11hOHE04a9jbxehP5zdy/WmfcD2rMveJQAfdNc72ci9oxsBv8QUFc44tQJXFf66uvKhe1ubpFhfXaBN25lzR+dT9La4lrge+gNfd7085trZennfpgkO3vTCVr0pOi/+4qSh28fTA9DKKgnoHMZ36tLPjO5nNhSfn7oOomv76guD7QP57RLvq/d20j76Fl+PXRJCNbI2nIU1unnH9r9eYrI2d9VhTyen980D1hYeEJjzpxe442ha7RarZ7Q9SPzad139YA0b6LNY9fI6hM7Xdp/V67UBvvGzwFJv+8U62nIn5Lul5GeIWA+zev2r1H4WAhrxJpV9sTVVH8/ENrz0Jb9cxKBaTLb9vbpOnEzfU+fZ13ebE4urB/tHK5tPyvIBdqO13sC0NY9MaXp9/73FwbdQfHRbniQJmK/5Tpz6Wv7YRwd+pLrFzyBI2t/x29U0KOGbHy6SeCZ1ewc52D92SAfvjjo8e4ceT6YYf/+RnmbUoiwqjKtuur+NzQQ1M+Nj3ze7W10MBeGOvO8UDcIBuV05yx9XxrS1wuuhznS0CcfG9GHyXOcG7/+umOesMOytnF4Oe+bn3L9Md/mpLMi8rziBORJ+ZV4PnSzMc8F3/1Nt7Kx4hYjnr6HTLaL2415diep7HbuMKKHfgjUxQ/eecxzuH4xjt/H7+rpoUTWrvHdwjPWdqZb2xcO09j/5btB+uW9g0h7zz0G2uaed2+Bc4ZTA21nb+8Zflm6k+YZH7j3QNs9fG42zr+5qGd121aVYvJ/rWdh/fYmX6dcp88vQ9YWvafyrK693X+viQZ1LdTLd/vv3qOqr5cp/z4d8mDIPx/9oKx/6DqQnteZ+w3rvutfkWfNY545ndXBf95ozDvZhfruenIez3x9l29Z8o7r4v5tSp5xXfz07SBPWRe/ffsx/WDiG+J0ktrOHUqecX39/Z0gT1lfH3CXQPeEtYth7t+XbLZ3cyrSL4WeOdDzevmm+/T0YGFPDuX/kVD+12z05Q/Hia8M6fH7kqB847zwijyzVpPpWz1e8o7L94k3mscD9d1ryPcbZ7y+WA+LND5oqIM3+498UG/gv1XBH9MB9aLbjvnG6YX5+dVk28E8+19xDPKM63cqz9UbBN6eaTvsmGf7dDeENL9/EA4Ywd6bu1HPs3y2E79Xls6vxTTMxsWHxpSmfPr+sTFfsijZLY6XfJErrRVvEng88aDIvn7s/E6ooxuXwNj5Tf+NEH3FsfPrEXPcd73l2iV9XLePX/+KPOHHs4vBxrjPX/KOy3bn5Dye+fpWbwV5U7+UeP5865Jn3Ke8/rY5T+xTYh348+08PdSBs4thUy5+f8gd4vdQN0Ad/kbUFzqN8Tzh+9eFPHle3Cub234=
*/