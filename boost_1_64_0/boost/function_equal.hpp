//  Copyright Douglas Gregor 2004.
//  Copyright 2005 Peter Dimov

//  Use, modification and distribution is subject to
//  the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_EQUAL_HPP
#define BOOST_FUNCTION_EQUAL_HPP

namespace boost {

template<typename F, typename G>
  bool function_equal_impl(const F& f, const G& g, long)
  { return f == g; }

// function_equal_impl needs to be unqualified to pick
// user overloads on two-phase compilers

template<typename F, typename G>
  bool function_equal(const F& f, const G& g)
  { return function_equal_impl(f, g, 0); }

} // end namespace boost

#endif // BOOST_FUNCTION_EQUAL_HPP

/* function_equal.hpp
/ReZAgNrjLqa4kEuN8pXs3WFJk36onj6M4ccQPovx5rp1WJSuKN/gT3UwTjvqqQrXsaDw/bj0leifvwdZhnFwvQGrPaqDd/aGNbINXgZ+HGQGr/MIiCBX0HJYR4dWlY54cFTifsnIzf+3gtgkQkcv0qXr/D16jxQnfCU/fGdi0WleUfPmnvhdsZzV5o7QghWsp3SWtc93aSsZzDmHfuwt3Dvv6MUHdnFaHMlKQB23G72RMN/ntWpqRLwHy3l3uP6oojmr8ckNPIbIcf/iO10GdvLRTuFH5sVYotbnXwfiDRoE/2lvboPfya+RVSJegeibPW1YpfIkviEZfqoK6Tu0OZQgqh879gm9qfTnm69Xw1N/OawXKjqELsoAeeN7tcpv6WDNfHiMW4+V7zQMfC1T5NKOI6p6m8kgXC8JBCGI5z1/BMC96V6ir6uvMiUT/6VegHIpNrvMupPiOt3f/9bSScfRjr5twmiwtF+S787Xf8ea7UNCUejffTJjLXIcN2YdvaCtqhnHHoscf27UOVmp4VRfZ3ugiXcAjqnwC5kWaP6tYPf01w7N0gtVH0tiHV52Ib6R1r9i/Mtf6FXyaKKajDbODLCOx8J+mJ7uBPa0pV09e9kh/38eGsSDvPrnXg+GAVMFY785J31gl5ELDkRp+JKLoymhnsX43KnJA2rh17JTn6Wr+c8jhtR09D1G56m2HaAedy6RHoajcA+oi00VBhbeR7wc/wltTedvORKdbdqoTyxPYi0MqcpxjPJWfh3rldXZxIDmSGQMtd/Ji1cTDkEPbrheW6TLGCNVcCLsoB+VgE3GeeiAJFTUc0+ekPd/z81/qPV+DvQ+y1ATQ2LmsOr28LZCNiOADHMF0BmsAd8vHt0Aj7Gqv0GffMinbGucD92q3h+ZYn5ZUv8LmB+3a7fG377FYIn8j9GmfgN5Bam8j0KwduBCmyF4YcgYFob/853JI6bGD4COhr7hN+3jto7fo/8jcTvRcda+D109/hdeprA7yITv3n0JY6fisDu1UMnCZ9EArsfBMrcSA3uX6OT8rxJqAkE9GHl8UlLSAL9iI1EwaFLJikUvFCi4PPIQeZ3vbG6LDkjXrJgJkB2/x6wvVX4QcZcxf8aKTpZYGlQIG1fVLpc4WuvXyt8/W3PPeLr+yMS8GsoBHG8h/MUuu6YY/YLX7H/XPlE6/3o+aTvaUnfK5O+m5K+i59s/f1NUnwgMZ43GZUr4/h3Qm0XuwT+DxetFeivlWgFJsa76gT9xhlh8dn80X6FlTXT2mrPx8gca2x24sIj6Hd9vcZ/u0A9vMRM5X3tStz8aUA/eZ0b8LL2I7w6P7fevjHf1n7k3OCPfGIPg/xHQdW5wGiU5cRnv0KkJapgSq6ObMnW3PfUaJG6bK32O6dwyIYFM8tX1TYQW6pVD4Ka9lr4j+1k6qfCA2yt4dJ6ruxfldvBH/nIPu2TsuqMfLbtoCCdpf9zvmkhEiijLSHHkLb2ZnWGgzNYPsntFwu315awx9hfa/2obKwBEBmzTuLUEu5Xn5Tz6zSMn+kp7R3jytK4apA291tmHPbRzkSJt2/bmafLPMt512UlWYyHwQF6e3+sVitaqtVucXlzGgIlq2d85MO+XMaCnmMN5qMGzatRM0DB1VStKJmxv5E1eOaJeA36GNvOjtfAhw53ajvXCmPx3hJ/Qbgd03FDbOqHFcMbzRHItu8KTPv5p87/wyT9JKZ27yfUdN54CqZz6vwb/XjSfHs8mX8B/MbA+Yqw9G/UYFtjgnmfhsT4Ev6AlzS/xuusWcyPtU3iYz1/l3qd6wSE+Fjb5HViP2i2h+uJsS6gWnvNWQfvo/vaF6RPL1Nr0Njz4vQ=
*/