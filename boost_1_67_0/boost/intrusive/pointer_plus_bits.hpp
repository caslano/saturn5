/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP
#define BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/mpl.hpp> //ls_zeros
#include <boost/intrusive/detail/assert.hpp> //BOOST_INTRUSIVE_INVARIANT_ASSERT

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif


//GCC reports uninitialized values when an uninitialized pointer plus bits type
//is asigned some bits or some pointer value, but that's ok, because we don't want
//to default initialize parts that are not being updated.
#if defined(BOOST_GCC)
#  if (BOOST_GCC >= 40600)
#     pragma GCC diagnostic push
#     pragma GCC diagnostic ignored "-Wuninitialized"
#     if (BOOST_GCC >= 40700)
#        pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#     endif
#  endif
#endif

namespace boost {
namespace intrusive {

//!This trait class is used to know if a pointer
//!can embed extra bits of information if
//!it's going to be used to point to objects
//!with an alignment of "Alignment" bytes.
template<class VoidPointer, std::size_t Alignment>
struct max_pointer_plus_bits
{
   static const std::size_t value = 0;
};

//!This is a specialization for raw pointers.
//!Raw pointers can embed extra bits in the lower bits
//!if the alignment is multiple of 2pow(NumBits).
template<std::size_t Alignment>
struct max_pointer_plus_bits<void*, Alignment>
{
   static const std::size_t value = detail::ls_zeros<Alignment>::value;
};

//!This is class that is supposed to have static methods
//!to embed extra bits of information in a pointer.
//!This is a declaration and there is no default implementation,
//!because operations to embed the bits change with every pointer type.
//!
//!An implementation that detects that a pointer type whose
//!has_pointer_plus_bits<>::value is non-zero can make use of these
//!operations to embed the bits in the pointer.
template<class Pointer, std::size_t NumBits>
struct pointer_plus_bits
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   {}
   #endif
;

//!This is the specialization to embed extra bits of information
//!in a raw pointer. The extra bits are stored in the lower bits of the pointer.
template<class T, std::size_t NumBits>
struct pointer_plus_bits<T*, NumBits>
{
   static const uintptr_t Mask = uintptr_t((uintptr_t(1u) << NumBits) - 1);
   typedef T*        pointer;

   BOOST_INTRUSIVE_FORCEINLINE static pointer get_pointer(pointer n)
   {  return pointer(uintptr_t(n) & uintptr_t(~Mask));  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_pointer(pointer &n, pointer p)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0 == (uintptr_t(p) & Mask));
      n = pointer(uintptr_t(p) | (uintptr_t(n) & Mask));
   }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_bits(pointer n)
   {  return std::size_t(uintptr_t(n) & Mask);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_bits(pointer &n, std::size_t c)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(uintptr_t(c) <= Mask);
      n = pointer(uintptr_t((get_pointer)(n)) | uintptr_t(c));
   }
};

} //namespace intrusive
} //namespace boost

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#  pragma GCC diagnostic pop
#endif

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_POINTER_PLUS_BITS_HPP

/* pointer_plus_bits.hpp
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
*/