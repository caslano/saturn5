///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INTEGER_HPP
#define BOOST_MP_INTEGER_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/detail/bitscan.hpp>

namespace boost {
namespace multiprecision {

template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
multiply(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) * static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
add(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) + static_cast<Integer>(b);
}
template <class Integer, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value && is_integral<I2>::value, Integer&>::type
subtract(Integer& result, const I2& a, const I2& b)
{
   return result = static_cast<Integer>(a) - static_cast<Integer>(b);
}

template <class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value>::type divide_qr(const Integer& x, const Integer& y, Integer& q, Integer& r)
{
   q = x / y;
   r = x % y;
}

template <class I1, class I2>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_integral<I2>::value, I2>::type integer_modulus(const I1& x, I2 val)
{
   return static_cast<I2>(x % val);
}

namespace detail {
//
// Figure out the kind of integer that has twice as many bits as some builtin
// integer type I.  Use a native type if we can (including types which may not
// be recognised by boost::int_t because they're larger than boost::long_long_type),
// otherwise synthesize a cpp_int to do the job.
//
template <class I>
struct double_integer
{
   static const unsigned int_t_digits =
       2 * sizeof(I) <= sizeof(boost::long_long_type) ? std::numeric_limits<I>::digits * 2 : 1;

   typedef typename mpl::if_c<
       2 * sizeof(I) <= sizeof(boost::long_long_type),
       typename mpl::if_c<
           is_signed<I>::value,
           typename boost::int_t<int_t_digits>::least,
           typename boost::uint_t<int_t_digits>::least>::type,
       typename mpl::if_c<
           2 * sizeof(I) <= sizeof(double_limb_type),
           typename mpl::if_c<
               is_signed<I>::value,
               signed_double_limb_type,
               double_limb_type>::type,
           number<cpp_int_backend<sizeof(I) * CHAR_BIT * 2, sizeof(I) * CHAR_BIT * 2, (is_signed<I>::value ? signed_magnitude : unsigned_magnitude), unchecked, void> > >::type>::type type;
};

} // namespace detail

template <class I1, class I2, class I3>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_unsigned<I2>::value && is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   typedef typename detail::double_integer<I1>::type double_type;

   I1          x(1), y(a);
   double_type result(0);

   while (b > 0)
   {
      if (b & 1)
      {
         multiply(result, x, y);
         x = integer_modulus(result, c);
      }
      multiply(result, y, y);
      y = integer_modulus(result, c);
      b >>= 1;
   }
   return x % c;
}

template <class I1, class I2, class I3>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I1>::value && is_signed<I2>::value && is_integral<I3>::value, I1>::type
powm(const I1& a, I2 b, I3 c)
{
   if (b < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   return powm(a, static_cast<typename make_unsigned<I2>::type>(b), c);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, unsigned>::type lsb(const Integer& val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_lsb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, unsigned>::type msb(Integer val)
{
   if (val <= 0)
   {
      if (val == 0)
      {
         BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
      }
      else
      {
         BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
      }
   }
   return detail::find_msb(val);
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, bool>::type bit_test(const Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return 0;
   if (index)
      mask <<= index;
   return val & mask ? true : false;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_set(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val |= mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_unset(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val &= ~mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer&>::type bit_flip(Integer& val, unsigned index)
{
   Integer mask = 1;
   if (index >= sizeof(Integer) * CHAR_BIT)
      return val;
   if (index)
      mask <<= index;
   val ^= mask;
   return val;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer>::type sqrt(const Integer& x, Integer& r)
{
   //
   // This is slow bit-by-bit integer square root, see for example
   // http://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Binary_numeral_system_.28base_2.29
   // There are better methods such as http://hal.inria.fr/docs/00/07/28/54/PDF/RR-3805.pdf
   // and http://hal.inria.fr/docs/00/07/21/13/PDF/RR-4475.pdf which should be implemented
   // at some point.
   //
   Integer s = 0;
   if (x == 0)
   {
      r = 0;
      return s;
   }
   int g = msb(x);
   if (g == 0)
   {
      r = 1;
      return s;
   }

   Integer t = 0;
   r         = x;
   g /= 2;
   bit_set(s, g);
   bit_set(t, 2 * g);
   r = x - t;
   --g;
   do
   {
      t = s;
      t <<= g + 1;
      bit_set(t, 2 * g);
      if (t <= r)
      {
         bit_set(s, g);
         r -= t;
      }
      --g;
   } while (g >= 0);
   return s;
}

template <class Integer>
BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<Integer>::value, Integer>::type sqrt(const Integer& x)
{
   Integer r(0);
   return sqrt(x, r);
}

}} // namespace boost::multiprecision

#endif

/* integer.hpp
FaP7v7ysY0BDKXgcOizoyrENz9bfNWBMMbf+bcCpOt6lD+gYNZbW3wwYVQ+89EGB4UcWVAQjHwNGje31/Id0DK5ftc+nhtFjiZ0+omLMscRuGHBq+4MP6xgt7zHB4MdA+qGPIN3o2/MypYMAouzURxltEwj8MFEpplG+qxqdnWkXVwbKfcYZwkFX6puYJgxu0UIfO6xiGETwGBqR6bJHhpiHlygGvTIw1oWRjuoWxH13SxMO+l8+U4+qON07A88KRiyqZsRb0VYjDpKiSOdzxKADGulT3Pe3mXC0T05tVzGkb5HXNR2H/Yt6wDEVo/UxYm9rWK2fcZ8d7NCwel/L+/1OFa/3N+5pzVie+5v30y7Ekb7GnEuEzshSvtHdSJP7Fsv+G+nYp8KnZw/StL5EPelexGh9iPcDxBj7DnlN70Oc1md4r9Yx0FdC93NvK30fd+xWlPi2xa9HgO7xx2RRZmibVCa10hZYBoZuYklRAbR37vFttJ7AD9MosK1SE7LcLTUSir8HvFlS+5jc9xxQ+gSW2X28Lj5c13ma1hkVKViCxG1LPiLyQr3aviCRy5zysyjxMs+1amdrzB1d458n+MK3wWIXrFGh10iT7Npmp0Pa5FmZG+dxG+yY8N4mLq+8sFX3x9dI2Qhsv9tp4CWx1ZS2pGIwXJf/vlI+LrI0LNLMMqczwfInattMUr5l+WDG2AIjgjKL5sJAPE5U5Tr1d7gllyusOMiKduGlFvXoozaTb5C6Mivw3MKN3VzJ2EndKisWyGNsO+Xh574fFa5n5sHnocLjiMKj1fLaURIXCg+acUTxFyq2036P3HarlSpN4bd7difgxe26/JpSPmzZnpvkIWXAr2fIQJR/kZQP2JiDJvyXtCuP0bOb4jPTaU0XFEVRFI0IDdN2WiMR7rNv91l0pnbGdOZtZ5jOjHnfYVDRiNjSP/whIVJbEIJErREhPkuC2GoviqKovRESsZ/7PPc59557n5eCtN/3ved3zl2eu557Ft+v+e1nHRyz7fd7r85fsioIqxLM9gW7iuTWcM3hWCFlesJG3+F+yBVTrfqExD/0u3/T6O/Cidwgj1LBR11kh3/3PxsyqszhZRr5tozh3/3ABLV/zAu3iNPYY8NDtEgJ6rs/lshImDBVyisva2SsrM0v4k1ZLIJoO9muFU8m/AHzy8JN/MAx+ZFXW2fWCa/PEuimNI5ixWsWq3hfaZTrupVTRmEoeM2UL225buvrR3hLGKsFj8tU9tuw1D90DHzWkFEGmVdUjv9vZAzM9eOm8f2465V5FRaWDPQ3lgK0nCQTO+kY9vIkSNMKReCrR8P5bPQjI3yOSGYSeKmbKcZm8MsCkW/K4Iuy0q3KLGDGHcfki3ea63LOPSeX64MoSmz8ONWe3X7npxM+nxV5FpR5kbItlRZU7iTo89aWOTDKhBYWfu7LsSlzkYkVTdqutXyvtNpYVG4Zx4Sv38O9z233LsLHYUw6Ac8Dydf5PG19z48b37NIYP8MywxlYF9R275vGnyuB5uIyzny4VpG+X5j9JEfZ7nvFfVaRp4HZU3b7zKyi86/JOW8yHOXoVpCqa8l6+Nb3v2E12eVx2MXFj+LV51NHt/28eQus4/zsoTRqngt9b2UoepeGXUPvNjx06RUMjCEnVX3JaPuheNkvEq4yaumgPLnuUB4K5alCU9KnhBeK+SdPefftYt+s4JXvpf6OTOfmeV+d7QdWzpfxTynqPwEpi61aKR2plcoT+rmVVEVEaPWfHRM3TDqF3glDKnYZ6b5rFG/P+t8JYugfjkvEiYiGSkbcVq/id3k/Jz5eRAGZcFOzwML+KbCmolWyjj+dtO5kniFV0aFZNo=
*/