//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_8_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_8_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_8.hpp
mO79H0EMHyui7NMEh1sPlL38UcTwcAVlL96LuHm4ge9bPoaY2ey784CjHzeYN+BMeznOobOjHCi/f257YwwHy4lpXWfjeFBe5PwoGuWE5X4kNhycFGyxMY5LMsIhb0hn+Ag+9tzquBjhmSIj50g6wjFFxvJMZIaDbsDJ2cwTo7hJA8+NHs2BA5eK+igXxpKVleT3vm83tVB42NaGk2EV/t7FivPu0Q+dJ3asScvTtsmZaINYaC+2/llGwQX43xDMuHyj3JcJV+SJzMsmZcQT6kn73fDzr5go21JVpU5YLpydo65MnczR89TfqsqymqcJA8c8gRTaOih/rSKjOqmbVDLfq3Bj97kz54OYvbxNGi5zy57jQhs9S7XQmsp4Pj5yX3a+yCsuclEy63PE8pUt14LPn1VlGjVVJdk5gVxm055WpK3KRoo6KmsWeos9bd9i+Wmf6VzZykx2vlPgI6HPWU7A/dtIPpdpn/AkVlnUNAyd99B8rtF8ijTTGWR+PqdIPlbuG1SujouklNyXmx0r9wiVa5pKt5bw5eaInNWb/BM05l4a8brNItY1n0y8qmFeLyq6t0nLXFaV4Gyc63K/r/y8zqR1nMdRo1jgtXwic28Z/DopVjVR3cSiYp+UXLTah9FY/9rKz6Noaz1yspjJiA6BYy7OiKJxRtqK84YRJ+WRrfdsUO+qbGJZxDEb654c2/jJ86SN6yiOeKqlzkUqp02M+61fKyJT8qhI4pYRP1ChzA2aDy+5UGnVMuqtndbpq0GdRJHnPKpKNtb1OerAs0Tf0iwXccZbT99Onhk7jp4i/RPLOIrrtGGBt3Q8B3jez+d0nRRKFHUN284+7qc8/ouEnxRRniRZxuDhK+HbvdPf6LyZN3VcRonsbFWNFyPjEwj+o7Ep7LHy//Hla5aoouV1Lrt98Rh5kz/KH1og8k3UiJo3stu63Uze9sPdvvwZpZq2Fqpy/WCEsStsvscX6Jl32SQqSblicaRvCLQnsQvnzsu2gXldLeR2i4d+8/lCcOYNfoDqrGJiZwf8P+kt3lzPnicEdwb3+7JzWaVbXMZDl0dzG2AHYd542rO7VZJXxvK4iNK8qNiqPT/RFxO6gS53R9PWjZD7j1n4r/A95kNBmhmXudSd9wrSXN9cw5eohZ13SHo1q2IheKQaZp7KdKfKl7r7Lt06g8twwBwEMDzmxjHVibjhscpq3UCnus7xv8877p5kgeixbtImlrWyMmPXJC/4MqeSpuU8LlotAgW7SuNBvEjLlFSSizIqGWhoLi5qPblQK9BQkA7ucKboHU7dZlmZRK0tG1kDWb0+coHOS0o0EEpfWCH8vtM6HSc2kHkUNXXCQQoKOqTWlvsBn3uiijmvddsyf5zVtg4z5E4pUxBLSXHQWXl18wubW1/adC6viC0UG96Fwl6KxHg9NkkxHVPoyrb/VmSvxtFnQH9gYohZv3MM9sRG9qTvY+ROwIgvobUt735n/lzo+yPJRZzf8v2wf8ceTXr2qENvNmgLjW9YQp6uL+LTe0McDiEQv3sqwO05AdorhvhVP/3n9lE89L37zP4Qh4erXSaOc/lAyBkObjxzgYqM54RvrJ4PeKEP30cOhjgkgPjx28fgM4g/cCjE4QjSs7cdixv/9ehj3XK6UxHQJbhy78Euy7M/ffFOx4Pv8mAMG/v5sON2pqfLn++t+PU6fMTiBlvs61e1nt/311kcbIXAWwbKfvf1BDNp4z79328EHM6IxlUIx9DLbwKetQWznYz43W8xOOSDOL5/fyvgu7ldwv3X4drf57RtXRRNknZbipFYqs+3Plepgss4He41DRf3ry/53FNFnYtI1S3sNYN4moqk2ZQ=
*/