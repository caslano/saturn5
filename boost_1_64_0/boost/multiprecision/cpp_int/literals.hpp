///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_LITERALS_HPP
#define BOOST_MP_CPP_INT_LITERALS_HPP

#include <boost/multiprecision/cpp_int/cpp_int_config.hpp>

namespace boost { namespace multiprecision {

namespace literals {
namespace detail {

template <char>
struct hex_value;
template <>
struct hex_value<'0'>
{
   static constexpr limb_type value = 0;
};
template <>
struct hex_value<'1'>
{
   static constexpr limb_type value = 1;
};
template <>
struct hex_value<'2'>
{
   static constexpr limb_type value = 2;
};
template <>
struct hex_value<'3'>
{
   static constexpr limb_type value = 3;
};
template <>
struct hex_value<'4'>
{
   static constexpr limb_type value = 4;
};
template <>
struct hex_value<'5'>
{
   static constexpr limb_type value = 5;
};
template <>
struct hex_value<'6'>
{
   static constexpr limb_type value = 6;
};
template <>
struct hex_value<'7'>
{
   static constexpr limb_type value = 7;
};
template <>
struct hex_value<'8'>
{
   static constexpr limb_type value = 8;
};
template <>
struct hex_value<'9'>
{
   static constexpr limb_type value = 9;
};
template <>
struct hex_value<'a'>
{
   static constexpr limb_type value = 10;
};
template <>
struct hex_value<'b'>
{
   static constexpr limb_type value = 11;
};
template <>
struct hex_value<'c'>
{
   static constexpr limb_type value = 12;
};
template <>
struct hex_value<'d'>
{
   static constexpr limb_type value = 13;
};
template <>
struct hex_value<'e'>
{
   static constexpr limb_type value = 14;
};
template <>
struct hex_value<'f'>
{
   static constexpr limb_type value = 15;
};
template <>
struct hex_value<'A'>
{
   static constexpr limb_type value = 10;
};
template <>
struct hex_value<'B'>
{
   static constexpr limb_type value = 11;
};
template <>
struct hex_value<'C'>
{
   static constexpr limb_type value = 12;
};
template <>
struct hex_value<'D'>
{
   static constexpr limb_type value = 13;
};
template <>
struct hex_value<'E'>
{
   static constexpr limb_type value = 14;
};
template <>
struct hex_value<'F'>
{
   static constexpr limb_type value = 15;
};

template <class Pack, limb_type value>
struct combine_value_to_pack;
template <limb_type first, limb_type... ARGS, limb_type value>
struct combine_value_to_pack<value_pack<first, ARGS...>, value>
{
   typedef value_pack<first | value, ARGS...> type;
};

template <char NextChar, char... CHARS>
struct pack_values
{
   static constexpr unsigned chars_per_limb = sizeof(limb_type) * CHAR_BIT / 4;
   static constexpr unsigned shift          = ((sizeof...(CHARS)) % chars_per_limb) * 4;
   static constexpr limb_type value_to_add  = shift ? hex_value<NextChar>::value << shift : hex_value<NextChar>::value;

   typedef typename pack_values<CHARS...>::type                          recursive_packed_type;
   typedef typename boost::mpl::if_c<shift == 0,
                                     typename recursive_packed_type::next_type,
                                     recursive_packed_type>::type        pack_type;
   typedef typename combine_value_to_pack<pack_type, value_to_add>::type type;
};
template <char NextChar>
struct pack_values<NextChar>
{
   static constexpr limb_type value_to_add = hex_value<NextChar>::value;

   typedef value_pack<value_to_add> type;
};

template <class T>
struct strip_leading_zeros_from_pack;
template <limb_type... PACK>
struct strip_leading_zeros_from_pack<value_pack<PACK...> >
{
   typedef value_pack<PACK...> type;
};
template <limb_type... PACK>
struct strip_leading_zeros_from_pack<value_pack<0u, PACK...> >
{
   typedef typename strip_leading_zeros_from_pack<value_pack<PACK...> >::type type;
};

template <limb_type v, class PACK>
struct append_value_to_pack;
template <limb_type v, limb_type... PACK>
struct append_value_to_pack<v, value_pack<PACK...> >
{
   typedef value_pack<PACK..., v> type;
};

template <class T>
struct reverse_value_pack;
template <limb_type v, limb_type... VALUES>
struct reverse_value_pack<value_pack<v, VALUES...> >
{
   typedef typename reverse_value_pack<value_pack<VALUES...> >::type lead_values;
   typedef typename append_value_to_pack<v, lead_values>::type       type;
};
template <limb_type v>
struct reverse_value_pack<value_pack<v> >
{
   typedef value_pack<v> type;
};
template <>
struct reverse_value_pack<value_pack<> >
{
   typedef value_pack<> type;
};

template <char l1, char l2, char... STR>
struct make_packed_value_from_str
{
   BOOST_STATIC_ASSERT_MSG(l1 == '0', "Multi-precision integer literals must be in hexadecimal notation.");
   BOOST_STATIC_ASSERT_MSG((l2 == 'X') || (l2 == 'x'), "Multi-precision integer literals must be in hexadecimal notation.");
   typedef typename pack_values<STR...>::type                        packed_type;
   typedef typename strip_leading_zeros_from_pack<packed_type>::type stripped_type;
   typedef typename reverse_value_pack<stripped_type>::type          type;
};

template <class Pack, class B>
struct make_backend_from_pack
{
   static constexpr Pack p  = {};
   static constexpr B value = p;
};

template <class Pack, class B>
constexpr B make_backend_from_pack<Pack, B>::value;

template <unsigned Digits>
struct signed_cpp_int_literal_result_type
{
   static constexpr unsigned                                                                               bits = Digits * 4;
   typedef boost::multiprecision::backends::cpp_int_backend<bits, bits, signed_magnitude, unchecked, void> backend_type;
   typedef number<backend_type, et_off>                                                                    number_type;
};

template <unsigned Digits>
struct unsigned_cpp_int_literal_result_type
{
   static constexpr unsigned                                                                                 bits = Digits * 4;
   typedef boost::multiprecision::backends::cpp_int_backend<bits, bits, unsigned_magnitude, unchecked, void> backend_type;
   typedef number<backend_type, et_off>                                                                      number_type;
};

} // namespace detail

template <char... STR>
constexpr typename boost::multiprecision::literals::detail::signed_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::number_type operator"" _cppi()
{
   typedef typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type pt;
   return boost::multiprecision::literals::detail::make_backend_from_pack<pt, typename boost::multiprecision::literals::detail::signed_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::backend_type>::value;
}

template <char... STR>
constexpr typename boost::multiprecision::literals::detail::unsigned_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::number_type operator"" _cppui()
{
   typedef typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type pt;
   return boost::multiprecision::literals::detail::make_backend_from_pack<pt, typename boost::multiprecision::literals::detail::unsigned_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::backend_type>::value;
}

#define BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(Bits)                                                                                                                                                                                \
   template <char... STR>                                                                                                                                                                                                          \
   constexpr boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> > operator"" BOOST_JOIN(_cppi, Bits)()    \
   {                                                                                                                                                                                                                               \
      typedef typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type pt;                                                                                                                       \
      return boost::multiprecision::literals::detail::make_backend_from_pack<                                                                                                                                                      \
          pt,                                                                                                                                                                                                                      \
          boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> >::value;                                                                  \
   }                                                                                                                                                                                                                               \
   template <char... STR>                                                                                                                                                                                                          \
   constexpr boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void> > operator"" BOOST_JOIN(_cppui, Bits)() \
   {                                                                                                                                                                                                                               \
      typedef typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type pt;                                                                                                                       \
      return boost::multiprecision::literals::detail::make_backend_from_pack<                                                                                                                                                      \
          pt,                                                                                                                                                                                                                      \
          boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void> >::value;                                                                \
   }

BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(128)
BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(256)
BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(512)
BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(1024)

} // namespace literals

//
// Overload unary minus operator for constexpr use:
//
template <unsigned MinBits, cpp_int_check_type Checked>
constexpr number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>
operator-(const number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>& a)
{
   return cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>(a.backend(), boost::multiprecision::literals::detail::make_negate_tag());
}
template <unsigned MinBits, cpp_int_check_type Checked>
constexpr number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>
operator-(number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>&& a)
{
   return cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>(static_cast<const number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>&>(a).backend(), boost::multiprecision::literals::detail::make_negate_tag());
}

}} // namespace boost::multiprecision

#endif // BOOST_MP_CPP_INT_CORE_HPP

/* literals.hpp
dG1MuoBw54KFvUAfc4IEMs4v3x+Nw5HrYmdnAHuDc9G3RmPNqLVjOr4N4vAaFmMCUBoWCfcKtyX03nr/DkrXWSPtwO2ANuZN4jmk4btDlL9z3vhJ8jjMYnXT+0V3Lb8+YZX1rVc5J/bPJNKpMt8bg58ae14aIm52EnCuLEYn6hJ8D5t5Dc8ZP/Bw0KpgRbm8eusaghG7OvVfsGYyBCy+9xmLNZMivjXyseDQbHFVV34ZMek0YuzZ5SRtm795GJKn087nd3e4o90w39av4Cccv8obL3ftdFORBTwPEtZT9GO8v2zS4h8VBnGUJ7zSmkBqh37OTffRUVHJpECNfgsNOuwFFzsfK6m4drW07Bg9B13+M4uubXdVyExFZRvsltrBE1xYyDTOioKtoN7YsRu89HKqV5W1imQqU+YdfHyb5fe7fIrVQZhUqhQmxujc+tYIP0ifdXlqlsFKpR1rdzw7MDpd+3DM6zsv9/TUIo3ysiZ8vi+xn9K8Ki5SVQve8QyXhysj8/otrVdY1qEKYrxDg5F4ome//jeXp2RxFaRFLLIuLxA9vK9laB/6ClI+kYE0xRXyDM8gFy3fQZdPsVKoJA0ktrsrt+iH7bDLc4yHSVCGsuhYMJcAfRXRsnEeiTquI+/6jsqcfAWReZ7VdS4YcSIYdnVfeAWVORUlocwEpxnYhu74zhC+kIVZHWZJgnf0wZMXUs3bMd7L2Fn+7SWaz4C8+H/1S5Fmhb0D6Xnd2Dl+rMHpZRstZdHu8nNw9v+5SQelBC1mrW3m/c/7GGq/qfNZbjC6G0fkZexydxoMbSyTHdqyHnpZH4N1N3mdG4E5McLG87rB0UZGYKMTeQC0gVMza98J68mnR/FOODF/DIa0nabjOuPRze4Ebap6dPom9Pc9OrUNTKeRbmXAi5X41ZEYnQ/1n93H0LwuGwxpc0wH94mA6fcvsRsagfFtN/88AuPabq7u7dNNcW3sEAdj0kc7rbkZS4N0rU7d+e6n9y9Nc3T1bj9duA3SbF9hnfX+EOm0jd13Z4ih9XLLMHs7wKDOn5bhY4TWL8OhfUgfW4ZriPHLgOce8F9Pzz2yCEVeyZu+v3HPt58xbY5HtiEsIs7eSU5aTN+giOqTEEdtH2x+iKGGN66MxrsQ4xvYEJ0/YnxLCyetP/VwmCOmdctuiqE52ra/RNo+Z0rlUZLwG9f9Dc6SGNKfbf6c0jL3lMJcMKEt8CTSbKBQNzb3VJ/u31F9BzE2mOh9sY0pzbCjjuuLSF/Wymf8Pr27+745hLaxvqL3NN8hyMfJNs67M0/HezWtjYUNQayADokuOjHMZnr0TZf+89to+vIAKgrKs+e3wbadvL9624a+3jbj+jIQkbaxz6GdGSxCKliXndsbGlTHTa++g/1u2hTLcu6Ohqar2iXotM8z9xv6yhHy5nz1Tva7SRN5Zu+saUDQhXT67093cb63TNj/Pz+ANL//sY+fdlfEjOzjnzf0xrvN6uDUmtVj3s35vvwCiKlly/r7htZ6vIFORJ7f3h2/t4m5fXAPpHUJYnr/sjTd6agX/9sLvfdfaRZJ7ed54fiTTyxwiKYZ8eMLmciiYIEbm0ZXl/O5xs+ProN5Jfzkp9mxM0no0CR9zN8Q05QNAUBy3j1TDCREcGjPsUXPBiLLuX4+6tfAv6v6PK2DfVsxSWiQLaX/Cem27O7csTpF6JiAu8487SVevIYqrjm/iYfqONfZ+nyhyfMEvM5tvXPgPDjp0lrPHPfFNcWloft060/+m3fW/uAhOxNsf7gNcVp3cO9/9Zx3ZkjjKMszFpRPh1isx7On6Mafh1tGz374By6fYkkRlFWVM8Lh25x89pznI1aKWhY=
*/