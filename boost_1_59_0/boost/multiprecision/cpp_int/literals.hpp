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
   using type = value_pack<first | value, ARGS...>;
};

template <char NextChar, char... CHARS>
struct pack_values
{
   static constexpr std::size_t chars_per_limb = sizeof(limb_type) * CHAR_BIT / 4;
   static constexpr std::size_t shift          = ((sizeof...(CHARS)) % chars_per_limb) * 4;
   static constexpr limb_type value_to_add  = shift ? hex_value<NextChar>::value << shift : hex_value<NextChar>::value;

   using recursive_packed_type = typename pack_values<CHARS...>::type                         ;
   using pack_type = typename std::conditional<shift == 0,
                                     typename recursive_packed_type::next_type,
                                     recursive_packed_type>::type;
   using type = typename combine_value_to_pack<pack_type, value_to_add>::type;
};
template <char NextChar>
struct pack_values<NextChar>
{
   static constexpr limb_type value_to_add = hex_value<NextChar>::value;

   using type = value_pack<value_to_add>;
};

template <class T>
struct strip_leading_zeros_from_pack;
template <limb_type... PACK>
struct strip_leading_zeros_from_pack<value_pack<PACK...> >
{
   using type = value_pack<PACK...>;
};
template <limb_type... PACK>
struct strip_leading_zeros_from_pack<value_pack<0u, PACK...> >
{
   using type = typename strip_leading_zeros_from_pack<value_pack<PACK...> >::type;
};

template <limb_type v, class PACK>
struct append_value_to_pack;
template <limb_type v, limb_type... PACK>
struct append_value_to_pack<v, value_pack<PACK...> >
{
   using type = value_pack<PACK..., v>;
};

template <class T>
struct reverse_value_pack;
template <limb_type v, limb_type... VALUES>
struct reverse_value_pack<value_pack<v, VALUES...> >
{
   using lead_values = typename reverse_value_pack<value_pack<VALUES...> >::type;
   using type = typename append_value_to_pack<v, lead_values>::type      ;
};
template <limb_type v>
struct reverse_value_pack<value_pack<v> >
{
   using type = value_pack<v>;
};
template <>
struct reverse_value_pack<value_pack<> >
{
   using type = value_pack<>;
};

template <char l1, char l2, char... STR>
struct make_packed_value_from_str
{
   static_assert(l1 == '0', "Multi-precision integer literals must be in hexadecimal notation.");
   static_assert((l2 == 'X') || (l2 == 'x'), "Multi-precision integer literals must be in hexadecimal notation.");
   using packed_type = typename pack_values<STR...>::type                       ;
   using stripped_type = typename strip_leading_zeros_from_pack<packed_type>::type;
   using type = typename reverse_value_pack<stripped_type>::type         ;
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
   using backend_type = boost::multiprecision::backends::cpp_int_backend<bits, bits, signed_magnitude, unchecked, void>;
   using number_type = number<backend_type, et_off>                                                                   ;
};

template <unsigned Digits>
struct unsigned_cpp_int_literal_result_type
{
   static constexpr unsigned                                                                                 bits = Digits * 4;
   using backend_type = boost::multiprecision::backends::cpp_int_backend<bits, bits, unsigned_magnitude, unchecked, void>;
   using number_type = number<backend_type, et_off>                                                                     ;
};

} // namespace detail

template <char... STR>
constexpr typename boost::multiprecision::literals::detail::signed_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::number_type operator"" _cppi()
{
   using pt = typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type;
   return boost::multiprecision::literals::detail::make_backend_from_pack<pt, typename boost::multiprecision::literals::detail::signed_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::backend_type>::value;
}

template <char... STR>
constexpr typename boost::multiprecision::literals::detail::unsigned_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::number_type operator"" _cppui()
{
   using pt = typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type;
   return boost::multiprecision::literals::detail::make_backend_from_pack<pt, typename boost::multiprecision::literals::detail::unsigned_cpp_int_literal_result_type<(sizeof...(STR)) - 2>::backend_type>::value;
}

#define BOOST_MP_DEFINE_SIZED_CPP_INT_LITERAL(Bits)                                                                                                                                                                                \
   template <char... STR>                                                                                                                                                                                                          \
   constexpr boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> > operator"" BOOST_JOIN(_cppi, Bits)()    \
   {                                                                                                                                                                                                                               \
      using pt = typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type;                                                                                                                       \
      return boost::multiprecision::literals::detail::make_backend_from_pack<                                                                                                                                                      \
          pt,                                                                                                                                                                                                                      \
          boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void> >::value;                                                                  \
   }                                                                                                                                                                                                                               \
   template <char... STR>                                                                                                                                                                                                          \
   constexpr boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<Bits, Bits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void> > operator"" BOOST_JOIN(_cppui, Bits)() \
   {                                                                                                                                                                                                                               \
      using pt = typename boost::multiprecision::literals::detail::make_packed_value_from_str<STR...>::type;                                                                                                                       \
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
template <std::size_t MinBits, cpp_int_check_type Checked>
constexpr number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>
operator-(const number<cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>, et_off>& a)
{
   return cpp_int_backend<MinBits, MinBits, signed_magnitude, Checked, void>(a.backend(), boost::multiprecision::literals::detail::make_negate_tag());
}
template <std::size_t MinBits, cpp_int_check_type Checked>
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