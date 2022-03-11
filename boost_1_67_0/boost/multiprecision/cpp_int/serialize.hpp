///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_SERIALIZE_HPP
#define BOOST_MP_CPP_INT_SERIALIZE_HPP

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
struct is_binary_archive : public mpl::false_
{};
template <>
struct is_binary_archive<boost::archive::binary_oarchive> : public mpl::true_
{};
template <>
struct is_binary_archive<boost::archive::binary_iarchive> : public mpl::true_
{};

//
// We have 8 serialization methods to fill out (and test), they are all permutations of:
// Load vs Store.
// Trivial or non-trivial cpp_int type.
// Binary or not archive.
//
template <class Archive, class Int>
void do_serialize(Archive& ar, Int& val, mpl::false_ const&, mpl::false_ const&, mpl::false_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::true_ const&, mpl::false_ const&, mpl::false_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::false_ const&, mpl::true_ const&, mpl::false_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::true_ const&, mpl::true_ const&, mpl::false_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::false_ const&, mpl::false_ const&, mpl::true_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::true_ const&, mpl::false_ const&, mpl::true_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::false_ const&, mpl::true_ const&, mpl::true_ const&)
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
void do_serialize(Archive& ar, Int& val, mpl::true_ const&, mpl::true_ const&, mpl::true_ const&)
{
   // Store.
   // Trivial.
   // Binary.
   bool s = val.sign();
   ar&  s;
   ar.save_binary(val.limbs(), sizeof(*val.limbs()));
}

} // namespace cpp_int_detail

template <class Archive, unsigned MinBits, unsigned MaxBits, mp::cpp_integer_type SignType, mp::cpp_int_check_type Checked, class Allocator>
void serialize(Archive& ar, mp::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>& val, const unsigned int /*version*/)
{
   typedef typename Archive::is_saving                                                                                               save_tag;
   typedef mpl::bool_<mp::backends::is_trivial_cpp_int<mp::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> >::value> trivial_tag;
   typedef typename cpp_int_detail::is_binary_archive<Archive>::type                                                                 binary_tag;

   // Just dispatch to the correct method:
   cpp_int_detail::do_serialize(ar, val, save_tag(), trivial_tag(), binary_tag());
}

} // namespace serialization
} // namespace boost

#endif // BOOST_MP_CPP_INT_SERIALIZE_HPP

/* serialize.hpp
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
*/