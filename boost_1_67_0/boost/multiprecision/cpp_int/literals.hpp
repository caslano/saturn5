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
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
*/