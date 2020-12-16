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
N2qM/riHQ5lBzNadfQzKDWLucRfAWP05njjdtnhHD7ODoId06RzwMLQh7Bzex2HlsNx37WF6+f2ZYnoCh/J2tx5utJ3t3X0cFgvnoJ9SzFhBw9iC96B4I2RI/wWlY4Z41/Ifyq4kxo6eCAcIECDs+76FTUIohAQyEgK7vbTdbbdNJuzrZOYlMzAb82YgIA4cOPwHDhyQ4MCBA4ccOHBAAsS+I8EBJDYhhEDiwIF936H8Xne1y/2GRZD/z/9cn8t2lZd2laseTctL5cK58hhCRxUrz983oZuO/dXHEhpUKlIPpRmVKvd1etxqGhi0l+d0n6J05LYmp2OPn9KhHmZz8kur6E4Ztw89YSXtRA7PfOJKugnvD0/pSr1E2stPWkW7eu142JMntEQ/Lw3zdEp3qo7iOveUEoOLIdLcmdIgc4zh/dQpDdXXkfbchSltqbO4D6+kncroYU+b0o26O9K9f0qX6y+28XFPn9JRHR59iz60oD1cvvY/pj7vF59BymabhV/Sl2j5UcLindic5r2xbaVN1Sx8LeFPO4dXjS892h09CLJ7pZ9TrHfCV0Eqgu1O9lZi/z6n+UKqJnglHcFeh1xNPZj4tp4/pjbS4HhV1eJ/zkd8AE5G+TcPoz7V1gTbdY0e22IXuXn6plDf1phjL3daNe3iFcfzEbyEpFg+nwA5BHgfnSI0v8wK5YJYvFv79PD7wqdELn776vBb6BSow+K3LyPdNWclyBd+++Tw2zX1stAq2ZvIF/w+hvxsVzuoZj0ufv9izm/9Or/+0vVF/V/HuoDSyqRfeO7/5MI3Lo3c6/cP9jdJfI7ju0F58i8j5TSWUCo/ej14fcDnJ8kNh2UL7MbmyfHBzZtjObsHKQet6GNNDXWfxfIl74V9cCy/g+WkbWhPjfck5eCz8hZ4lAsPwzMel++VaEY8vnEbYriU5f17M4xBsiifw/jRNmIco3tDebLpciHU+vrrpVoX12y8bkNH4racPXc6XZkb7ptvpvmAfYyVNfb/niNJX36U60VyU+p//8H4+0tyvfvWqHd1B9p1TS1//y7SL92lBvqfDL9XfN2KxIT6D35qWQo31Tubfdyf8Rx3dyw/mr35BCI59hSZjP98j0STetQ7XWzNdme3YMvYGmW0fbag2dma5zK8eM+yfLEmYPmD7oXlEM8Sc/xiG364shxex2Xt/Oi9kWZv43hzu+cBCj/SPOg+SAP9JbxQn36caJKeFJM/KROJ53Hf1XS9MuH8/X6iQ5+DlO1gLGP3y8tobJ07eVnPHMfrPJatjMvzXizHuDwkbziWFbE0PlDovRYySiP+Z/+ZXO/v/sxM70O3rvrf/5nPh+qVkECJ6uun81V0KUrik0LL5ynY3tv6d2hId/Hup9AVMSY+1dPh/IBAE2UsQHmPVTRwu3p8Micxvs5SuoViZeUfvCeW72wtgoHQ3NFb98JyuJsD9exptrJ+fRtpcL7uzJcaTHx3zL1LuqHOzYOT/ePRH35Cl/PO3oGey+jmcHc4n/WhcbI8zYkm6VW28fZqizTgmzah6VWQ5PJHGjL/MAAOzkF239W0vcrjfPlSTzeNgYW5/rG8jD1zFykjcwkmE5TRuYS+Ix/eI/eVzghjQ2zY/GRzczaf3zwp4l18ao/a44QNQcpFnOPdmwdHe7OtXkSF/8g396gfsfc8Ol2xRZRpMBWPppQxd9yPc8xVFSvug9Ts+OhtuxuAmtgxf75Hz3iidlxzwUDzUqN2jmZbE8zfc0zHdGcqq2vd5yuEYMFvRxDGUjm/n58HpWx4ctJhtw4Otia5L83Lz+T+LFbzuvI1Riamsdb3qU21a9squSBscgFX4UcHYAealffpH98=
*/