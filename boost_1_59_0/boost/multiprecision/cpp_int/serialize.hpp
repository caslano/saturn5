///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_SERIALIZE_HPP
#define BOOST_MP_CPP_INT_SERIALIZE_HPP

#ifndef BOOST_MP_STANDALONE

namespace boost {

namespace archive {

class binary_oarchive;
class binary_iarchive;

} // namespace archive

namespace serialization {

namespace mp = boost::multiprecision;

namespace cpp_int_detail {

using namespace boost::multiprecision;
using namespace boost::multiprecision::backends;

template <class T>
struct is_binary_archive : public std::integral_constant<bool, false>
{};
template <>
struct is_binary_archive<boost::archive::binary_oarchive> : public std::integral_constant<bool, true>
{};
template <>
struct is_binary_archive<boost::archive::binary_iarchive> : public std::integral_constant<bool, true>
{};

//
// We have 8 serialization methods to fill out (and test), they are all permutations of:
// Load vs Store.
// Trivial or non-trivial cpp_int type.
// Binary or not archive.
//
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, false> const&, std::integral_constant<bool, false> const&, std::integral_constant<bool, false> const&)
{
   // Load.
   // Non-trivial.
   // Non binary.

   using boost::make_nvp;
   bool        s;
   ar&         make_nvp("sign", s);
   std::size_t limb_count;
   std::size_t byte_count;
   ar&         make_nvp("byte-count", byte_count);
   limb_count = byte_count / sizeof(limb_type) + ((byte_count % sizeof(limb_type)) ? 1 : 0);
   val.resize(limb_count, limb_count);
   limb_type* pl = val.limbs();
   for (std::size_t i = 0; i < limb_count; ++i)
   {
      pl[i] = 0;
      for (std::size_t j = 0; (j < sizeof(limb_type)) && byte_count; ++j)
      {
         unsigned char byte;
         ar&           make_nvp("byte", byte);
         pl[i] |= static_cast<limb_type>(byte) << (j * CHAR_BIT);
         --byte_count;
      }
   }
   if (s != val.sign())
      val.negate();
   val.normalize();
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, true> const&, std::integral_constant<bool, false> const&, std::integral_constant<bool, false> const&)
{
   // Store.
   // Non-trivial.
   // Non binary.

   using boost::make_nvp;
   bool        s = val.sign();
   ar&         make_nvp("sign", s);
   limb_type*  pl         = val.limbs();
   std::size_t limb_count = val.size();
   std::size_t byte_count = limb_count * sizeof(limb_type);
   ar&         make_nvp("byte-count", byte_count);

   for (std::size_t i = 0; i < limb_count; ++i)
   {
      limb_type l = pl[i];
      for (std::size_t j = 0; j < sizeof(limb_type); ++j)
      {
         unsigned char byte = static_cast<unsigned char>((l >> (j * CHAR_BIT)) & ((1u << CHAR_BIT) - 1));
         ar&           make_nvp("byte", byte);
      }
   }
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, false> const&, std::integral_constant<bool, true> const&, std::integral_constant<bool, false> const&)
{
   // Load.
   // Trivial.
   // Non binary.
   using boost::make_nvp;
   bool                          s;
   typename Int::local_limb_type l = 0;
   ar&                           make_nvp("sign", s);
   std::size_t                   byte_count;
   ar&                           make_nvp("byte-count", byte_count);
   for (std::size_t i = 0; i < byte_count; ++i)
   {
      unsigned char b;
      ar&           make_nvp("byte", b);
      l |= static_cast<typename Int::local_limb_type>(b) << (i * CHAR_BIT);
   }
   *val.limbs() = l;
   if (s != val.sign())
      val.negate();
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, true> const&, std::integral_constant<bool, true> const&, std::integral_constant<bool, false> const&)
{
   // Store.
   // Trivial.
   // Non binary.
   using boost::make_nvp;
   bool                          s = val.sign();
   typename Int::local_limb_type l = *val.limbs();
   ar&                           make_nvp("sign", s);
   std::size_t                   limb_count = sizeof(l);
   ar&                           make_nvp("byte-count", limb_count);
   for (std::size_t i = 0; i < limb_count; ++i)
   {
      unsigned char b = static_cast<unsigned char>(static_cast<typename Int::local_limb_type>(l >> (i * CHAR_BIT)) & static_cast<typename Int::local_limb_type>((1u << CHAR_BIT) - 1));
      ar&           make_nvp("byte", b);
   }
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, false> const&, std::integral_constant<bool, false> const&, std::integral_constant<bool, true> const&)
{
   // Load.
   // Non-trivial.
   // Binary.
   bool        s;
   std::size_t c;
   ar&         s;
   ar&         c;
   val.resize(c, c);
   ar.load_binary(val.limbs(), c * sizeof(limb_type));
   if (s != val.sign())
      val.negate();
   val.normalize();
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, true> const&, std::integral_constant<bool, false> const&, std::integral_constant<bool, true> const&)
{
   // Store.
   // Non-trivial.
   // Binary.
   bool        s = val.sign();
   std::size_t c = val.size();
   ar&         s;
   ar&         c;
   ar.save_binary(val.limbs(), c * sizeof(limb_type));
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, false> const&, std::integral_constant<bool, true> const&, std::integral_constant<bool, true> const&)
{
   // Load.
   // Trivial.
   // Binary.
   bool s;
   ar&  s;
   ar.load_binary(val.limbs(), sizeof(*val.limbs()));
   if (s != val.sign())
      val.negate();
}
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, std::integral_constant<bool, true> const&, std::integral_constant<bool, true> const&, std::integral_constant<bool, true> const&)
{
   // Store.
   // Trivial.
   // Binary.
   bool s = val.sign();
   ar&  s;
   ar.save_binary(val.limbs(), sizeof(*val.limbs()));
}

} // namespace cpp_int_detail

template <class Archive, std::size_t MinBits, std::size_t MaxBits, mp::cpp_integer_type SignType, mp::cpp_int_check_type Checked, class Allocator>
void serialize(Archive& ar, mp::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& val, const unsigned int /*version*/)
{
   using archive_save_tag = typename Archive::is_saving                                ;
   using save_tag = std::integral_constant<bool, archive_save_tag::value>      ;
   using trivial_tag = std::integral_constant<bool, mp::backends::is_trivial_cpp_int<mp::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value>;
   using binary_tag = typename cpp_int_detail::is_binary_archive<Archive>::type  ;

   // Just dispatch to the correct method:
   cpp_int_detail::do_serialize(ar, val, save_tag(), trivial_tag(), binary_tag());
}

} // namespace serialization
} // namespace boost

#endif // BOOST_MP_STANDALONE

#endif // BOOST_MP_CPP_INT_SERIALIZE_HPP

/* serialize.hpp
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
*/